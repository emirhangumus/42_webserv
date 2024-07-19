#include <iostream>
#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " <config_file>" << std::endl;
		return 1;
	}

	std::string config_file = av[1];

	Server server;

	bool okay = server.parseConfig(config_file);

	if (!okay)
		return 1;

	std::cout << "Host: " << server.getHost() << std::endl;
	std::cout << "Port: " << server.getPort() << std::endl;
	std::cout << "ServerNames: " << std::endl;
	for (size_t i = 0; i < server.getServerNames().size(); i++)
		std::cout << "  " << server.getServerNames()[i] << std::endl;
	std::cout << "Root: " << server.getRoot() << std::endl;
	std::cout << "Index: " << server.getIndex() << std::endl;
	std::cout << "TryFiles: " << std::endl;
	for (size_t i = 0; i < server.getTryFiles().size(); i++)
		std::cout << "  " << server.getTryFiles()[i] << std::endl;
	std::cout << "ClientMaxBodySize: " << server.getClientMaxBodySize() << std::endl;
	std::cout << "AllowMethods: " << std::endl;
	for (size_t i = 0; i < server.getAllowMethods().size(); i++)
		std::cout << "  " << server.getAllowMethods()[i] << std::endl;
}