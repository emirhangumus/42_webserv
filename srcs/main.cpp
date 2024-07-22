#include <iostream>
#include <string>
#include "Cluster.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " <config_file>" << std::endl;
		return 1;
	}

	std::string config_file = av[1];


	Cluster cluster(config_file);

	if (!cluster.initCluster())
		return 1;

	// cluster.runCluster();

	cluster.test();

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

	

	return 0;
}