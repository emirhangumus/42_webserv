/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 03:20:00 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 20:13:30 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"
#include "ConfigManager.hpp"

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
	std::cout << "Running clusters..." << std::endl;
	return true;
}

void	Cluster::test()
{
	for (size_t i = 0; i < this->_configManager->getServers().size(); i++)
	{
		Config config = this->_configManager->getServers()["127.0.0.1:8080"];

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
}