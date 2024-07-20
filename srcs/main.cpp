#include <iostream>
#include "ConfigManager.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " <config_file>" << std::endl;
		return 1;
	}

	std::string config_file = av[1];

	ConfigManager configManager;

	bool okay = configManager.parseConfigFile(config_file);

	if (!okay)
		return 1;

	// std::cout << "Host: " << configManager.getHost() << std::endl;
	// std::cout << "Port: " << configManager.getPort() << std::endl;
	// std::cout << "ConfigNames: " << std::endl;
	// for (size_t i = 0; i < configManager.getConfigNames().size(); i++)
	// 	std::cout << "  " << configManager.getConfigNames()[i] << std::endl;
	// std::cout << "Root: " << configManager.getRoot() << std::endl;
	// std::cout << "Index: " << configManager.getIndex() << std::endl;
	// std::cout << "TryFiles: " << std::endl;
	// for (size_t i = 0; i < configManager.getTryFiles().size(); i++)
	// 	std::cout << "  " << configManager.getTryFiles()[i] << std::endl;
	// std::cout << "ClientMaxBodySize: " << configManager.getClientMaxBodySize() << std::endl;
	// std::cout << "AllowMethods: " << std::endl;
	// for (size_t i = 0; i < configManager.getAllowMethods().size(); i++)
	// 	std::cout << "  " << configManager.getAllowMethods()[i] << std::endl;
}