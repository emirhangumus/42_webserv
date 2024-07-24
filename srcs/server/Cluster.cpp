/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 03:20:00 by egumus            #+#    #+#             */
/*   Updated: 2024/07/24 09:40:16 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"
#include "ConfigManager.hpp"
#include "Request.hpp"
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

Cluster::Cluster() {
	this->_config_file = "";
}

Cluster::Cluster(std::string config_file) {
	this->_config_file = config_file;
}

Cluster::~Cluster() {
	delete this->_configManager;
}

bool	Cluster::initCluster()
{
	this->_configManager = new ConfigManager();

	bool okay = this->_configManager->parseConfigFile(this->_config_file);

	if (!okay)
		return false;
	return true;
}

bool	Cluster::runCluster()
{
	// create a socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		std::cerr << "Error: socket() failed" << std::endl;
		return false;
	}

	// bind the socket
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		std::cerr << "Error: bind() failed" << std::endl;
		return false;
	}

	// listen
	if (listen(server_fd, 10) == -1)
	{
		std::cerr << "Error: listen() failed" << std::endl;
		return false;
	}

	// add the server_fd to the poll
	struct pollfd poll_fd_struct;
	poll_fd_struct.fd = server_fd;
	poll_fd_struct.events = POLLIN;
	
	while (true)
	{
		// poll
		int ret = poll(&poll_fd_struct, 1, -1);
		if (ret == -1)
		{
			std::cerr << "Error: poll() failed" << std::endl;
			return false;
		}

		// accept
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
		if (client_fd == -1)
		{
			std::cerr << "Error: accept() failed" << std::endl;
			return false;
		}

		// read
		char buffer[4096];
		int read_bytes = read(client_fd, buffer, sizeof(buffer));
		if (read_bytes == -1)
		{
			std::cerr << "Error: read() failed" << std::endl;
			return false;
		}

		// print the request
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << buffer << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		// parse the request
		Request request(buffer);

		// find the server
		Config config = this->_configManager->getServer("localhost:8080");

		// find the location
		t_location location = config.getLocation(request.getUri());

		// open the html file that in ./www/example.com/index.html
		std::string file_path = "./www/example.com/index.html";
		std::ifstream file(file_path);
		if (!file.is_open())
		{
			std::cerr << "Error: file not found" << std::endl;
			return false;
		}

		// read the file
		std::string file_content;
		std::string line;
		while (std::getline(file, line))
			file_content += line + "\n";
		file.close();

		// send the response
		std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(file_content.size()) + "\r\n\r\n" + file_content;
		write(client_fd, response.c_str(), response.size());

		// close the client_fd
		close(client_fd);
	}

	return true;	
}

void	Cluster::test(std::string key)
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