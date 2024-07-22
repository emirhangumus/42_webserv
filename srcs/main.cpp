#include <iostream>
#include "ConfigManager.hpp"
#include "Config.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " <config_file>" << std::endl;
		return 1;
	}

	std::string config_file = av[1];


	// Config config;

	// t_location loc;

	// loc.location = "/";
	// loc.root = "/var/www/html";
	// loc.index = "index.html";
	// loc.try_files.push_back("index.html");
	// loc.try_files.push_back("index.htm");
	// loc.client_max_body_size = "1m";
	// loc.allow_methods.push_back("GET");
	// loc.allow_methods.push_back("POST");

	// config.setLocation("/", loc);

	ConfigManager configManager;

	bool okay = configManager.parseConfigFile(config_file);

	if (!okay)
		return 1;

	for (size_t i = 0; i < configManager.getServers().size(); i++)
	{
		Config config = configManager.getServers()["127.0.0.1:8081"];

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
			std::cout << "Root: " << it->second.root << std::endl;
			std::cout << "Index: " << it->second.index << std::endl;
			std::cout << "Try files: ";
			std::vector<std::string> try_files = it->second.try_files;
			for (size_t j = 0; j < try_files.size(); j++)
				std::cout << try_files[j] << " ";
			std::cout << std::endl;
			std::cout << "Client max body size: " << it->second.client_max_body_size << std::endl;
			std::cout << "Allow methods: ";
			std::vector<std::string> allow_methods = it->second.allow_methods;
			for (size_t j = 0; j < allow_methods.size(); j++)
				std::cout << allow_methods[j] << " ";
			std::cout << std::endl;
			it++;
		}
	}
}