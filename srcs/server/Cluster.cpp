#include "Cluster.hpp"
#include "ConfigManager.hpp"
#include "Request.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <poll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/wait.h>

static bool    exec_cgı(int new_socket, std::string path)
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        std::cerr << "Error: pipe() failed" << std::endl;
        return false;
    }
    int pid = fork();
    if (pid == -1)
    {
        std::cerr << "Error: fork() failed" << std::endl;
        return false;
    }
    if (pid == 0) // Child process
    {
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]);

        char *args[] = { (char *)"garbage", (char *)path.c_str(), NULL };
        if (path.find(".py") != std::string::npos)
            execve("/usr/bin/python3", args, NULL);                            
        else
            execve("/usr/bin/php", args, NULL);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else // Parent process
    {
        close(pipefd[1]); // Close unused write end

        // Read the output from the PHP script
        char buffer[4096];
        std::string content;
        int bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0)
            content.append(buffer, bytesRead);
        close(pipefd[0]);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            // send the response
            std::string response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: text/html\r\n";
            response += "Content-Length: " + std::to_string(content.size()) + "\r\n";
            response += "\r\n";
            response += content;
            send(new_socket, response.c_str(), response.size(), 0);
        }
        else
        {
            std::string response = "HTTP/1.1 500 Internal Server Error\r\n";
            response += "Content-Type: text/html\r\n";
            response += "Content-Length: 0\r\n";
            response += "\r\n";
            send(new_socket, response.c_str(), response.size(), 0);
        }
        close(new_socket);
    }
    return true;
}

Cluster::Cluster() {
    this->_cookie = Cookie();
    this->_config_file = "";
}

Cluster::Cluster(std::string config_file) {
    this->_cookie = Cookie();
    this->_config_file = config_file;
}

Cluster::~Cluster() {
    delete this->_configManager;
}

void    Cluster::parseCookie(std::string cookie)
{
    this->_cookie.setCookie(cookie);
    this->_cookie.printCookies();
}

bool Cluster::initCluster()
{
    this->_configManager = new ConfigManager();

    bool okay = this->_configManager->parseConfigFile(this->_config_file);

    if (!okay)
        return false;
    return true;
}

bool Cluster::runCluster()
{
    // create a socket
    std::map<std::string, Config> servers = this->_configManager->getServers();
    std::map<std::string, int> server_fds;

    // Create a vector of pollfd structs
    std::vector<struct pollfd> poll_fds;

    for (std::map<std::string, Config>::iterator it = servers.begin(); it != servers.end(); it++)
    {
        Config config = it->second;
        std::string host = config.getHost();
        int port = config.getPort();

        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1)
        {
            std::cerr << "Error: socket() failed" << std::endl;
            return false;
        }

        std::cout << "Server: " << host << ":" << port << std::endl;
        std::string key = host + ":" + std::to_string(port);
        server_fds[key] = server_fd;

        int opt = 1;

        // Forcefully attaching socket to the port
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        // bind the socket to an IP / port
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(host.c_str());
        address.sin_port = htons(port);
        std::cout << "Binding to " << host << ":" << port << std::endl;
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
        {
            // print the error using errno
            std::cerr << "Error: bind() failed" << std::endl;
            return false;
        }

        // specify the socket to be a server socket and listen for at most 10 concurrent clients
        if (listen(server_fd, 10) == -1)
        {
            std::cerr << "Error: listen() failed" << std::endl;
            return false;
        }

        // Add the socket to the poll_fds vector
        struct pollfd pfd;
        pfd.fd = server_fd;
        pfd.events = POLLIN;
        poll_fds.push_back(pfd);
    }

    // accept incoming connections
    while (1)
    {
        int poll_count = poll(poll_fds.data(), poll_fds.size(), -1);
        if (poll_count == -1)
        {
            std::cerr << "Error: poll() failed" << std::endl;
            return false;
        }

        for (size_t i = 0; i < poll_fds.size(); ++i)
        {
            if (poll_fds[i].revents & POLLIN)
            {
                struct sockaddr_in address;
                socklen_t addrlen = sizeof(address);
                int new_socket = accept(poll_fds[i].fd, (struct sockaddr *)&address, &addrlen);
                if (new_socket == -1)
                {
                    std::cerr << "Error: accept() failed" << std::endl;
                    return false;
                }

                // read the request
                char buffer[30000] = {0};
                int valread = read(new_socket, buffer, 30000);
                if (valread == -1)
                {
                    std::cerr << "Error: read() failed" << std::endl;
                    return false;
                }

                std::cout << buffer << std::endl;

                // parse the request
                Request request(buffer);
                std::string host = request.getHeaders()["Host"];
                std::string cookie = request.getHeaders()["Cookie"];
                this->parseCookie(cookie);
                trim(host); // remove leading and trailing whitespaces
                std::string uri = request.getUri();
                std::string method = request.getMethod();
                std::string body = request.getBody();
                std::map<std::string, std::string> headers = request.getHeaders();

                // find the server
                std::map<std::string, Config> servers = this->_configManager->getServers();
                Config config;
                for (std::map<std::string, Config>::iterator it = servers.begin(); it != servers.end(); it++)
                {
                    if (it->second.getHost() == host)
                    {
                        config = it->second;
                        break;
                    }
                }

                // find the location
                std::map<std::string, t_location> locations = config.getLocations();
                t_location location;
                for (std::map<std::string, t_location>::iterator it = locations.begin(); it != locations.end(); it++)
                {
                    if (uri.find(it->first) == 0)
                    {
                        location = it->second;
                        break;
                    }
                }
                Request req(buffer);
                // check if the file exists
                std::cout << "Host: " << host << std::endl;
                std::map<std::string, Config> confs = this->_configManager->getServers();

                // print all the servers
                for (std::map<std::string, Config>::iterator it = confs.begin(); it != confs.end(); it++)
                {
                    std::cout << "Server: " << it->first << std::endl;
                    // print the server root
                    std::cout << "Root: " << it->second.getRoot() << std::endl;
                }

                // print the server configuration
                Config conf = confs[host];

                std::cout << "Root: " << conf.getRoot() << std::endl;
                std::string path = conf.getRoot() + uri;
                if (path[path.size() - 1] == '/')
                    path += "index.html";
                std::cout << "Path: " << path << std::endl;

                if (path.find(".php") != std::string::npos || path.find(".py") != std::string::npos)
                    exec_cgı(new_socket, path);
                else
                {
                    std::ifstream file(path);
                    // if the file does not exist, send a 404 response
                    if (!file.good())
                    {
                        std::string response = "HTTP/1.1 404 Not Found\r\n";
                        response += "Content-Type: text/html\r\n";
                        response += "Content-Length: 0\r\n";
                        response += "\r\n";
                        send(new_socket, response.c_str(), response.size(), 0);
                        close(new_socket);
                        continue;
                    }

                    // if the file exists, send the file
                    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                    std::string response = "HTTP/1.1 200 OK\r\n";
                    response += "Content-Type: text/html\r\n";
                    response += "Content-Length: " + std::to_string(content.size()) + "\r\n";
                    response += "\r\n";
                    response += content;

                    send(new_socket, response.c_str(), response.size(), 0);

                    close(new_socket);
                }
            }
        }
    }


    return true;
}

void Cluster::test(std::string key)
{
    Config config = this->_configManager->getServers()[key];

    std::cout << "Host: " << config.getHost() << std::endl;
    std::cout << "Port: " << config.getPort() << std::endl;
    std::cout << "Server names: ";
    std::vector<std::string> server_names = config.getConfigNames();
    for (size_t j = 0; j < server_names.size(); j++)
        std::cout << server_names[j] << " ";
    std::cout << std::endl;
    std::cout << "Root: " << config.getRoot() << std::endl;
    std::cout << "Index: " << config.getIndex() << std::endl;
    std::cout << "Try files: ";
    std::vector<std::string> try_files = config.getTryFiles();
    for (size_t j = 0; j < try_files.size(); j++)
        std::cout << try_files[j] << " ";
    std::cout << std::endl;
    std::cout << "Client max body size: " << config.getClientMaxBodySize() << std::endl;
    std::cout << "Allow methods: ";
    std::vector<std::string> allow_methods = config.getAllowMethods();
    for (size_t j = 0; j < allow_methods.size(); j++)
        std::cout << allow_methods[j] << " ";
    std::cout << std::endl;
    std::map<std::string, t_location> locations = config.getLocations();
    std::map<std::string, t_location>::iterator it = locations.begin();
    while (it != locations.end())
    {
        std::cout << "Location: " << it->first << std::endl;
        std::cout << "Root: " << it->second._root << std::endl;
        std::cout << "Index: " << it->second._index << std::endl;
        std::cout << "Try files: ";
        std::vector<std::string> try_files = it->second._try_files;
        for (size_t j = 0; j < try_files.size(); j++)
            std::cout << try_files[j] << " ";
        std::cout << std::endl;
        std::cout << "Client max body size: " << it->second._client_max_body_size << std::endl;
        std::cout << "Allow methods: ";
        std::vector<std::string> limit_except = it->second._limit_except;
        for (size_t j = 0; j < limit_except.size(); j++)
            std::cout << limit_except[j] << " ";
        std::cout << std::endl;
        it++;
    }
}
