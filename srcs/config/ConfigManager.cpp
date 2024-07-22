/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:03:49 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 03:16:53 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigManager.hpp"
#include "ServerParser.hpp"
#include "../utils/Utils.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

ConfigManager::ConfigManager() {}

ConfigManager::~ConfigManager() {}

std::vector<std::vector<int> > ConfigManager::serverBlockCount(const std::string &filename)
{
	std::fstream file;
	std::string line;
	std::vector<std::vector<int> > serverBlocks;

	file.open(filename, std::ios::in);

	int i = 0;
	int j = 0;
	int depth = 0;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			trim(line);

			i++;
			if (line.empty() || line[0] == COMMENT_CHAR)
				continue;

			std::vector<std::string> tokens = split(line, " ");
			
			if (depth == 0 && tokens[0] == "server" && tokens[tokens.size() - 1] == "{")
			{
				serverBlocks.push_back(std::vector<int>());
				serverBlocks[j].push_back(i);
				depth++;
			}
			else if (tokens[tokens.size() - 1] == "{")
				depth++;
			else if (tokens[0] == "}")
			{
				depth--;
				if (depth == 0)
				{
					serverBlocks[j].push_back(i);
					j++;
				}
			}
		}
		file.close();
	}
	else
		throw std::runtime_error("Unable to open the file");
	return serverBlocks;

}

bool ConfigManager::parseConfigFile(const std::string &filename)
{
	std::fstream file;
	ServerParser sp;
	Config *config;

	file.open(filename, std::ios::in);

	if (file.is_open())
	{
		try
		{
			std::vector<std::vector<int> > serverBlocks = serverBlockCount(filename);
			size_t i = 0;

			while (i < serverBlocks.size())
			{
				int j = 0;
				std::string line;
				std::vector<std::string> serverBlock;
				int start = serverBlocks[i][0];
				int end = serverBlocks[i][1];
				while (start < end - 1)
				{
					file.seekg(0, std::ios::beg);
					j = 0;
					while (j < start)
					{
						std::getline(file, line);
						j++;
					}
					std::getline(file, line);
					trim(line);
					if (line.empty() || line[0] == COMMENT_CHAR)
					{
						start++;
						continue;
					}
					serverBlock.push_back(line);
					start++;
				}

				// std::cout << std::endl;
				// std::cout << std::endl;
				// std::cout << std::endl;
				// std::cout << std::endl;
				// std::cout << std::endl;
				// for (size_t i = 0; i < serverBlock.size(); i++)
				// 	std::cout << serverBlock[i] << std::endl;

				config = sp.parseServer(serverBlock);

				if (config != NULL)
					_servers[config->getHost() + ":" + std::to_string(config->getPort())] = Config(*config);
				
				delete config;

				i++;
			}

			// Close the file object.
			file.close();
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			file.close();
			return false;
		}
	}
	else
	{
		std::cerr << "Error: Unable to open the file" << std::endl;
		return false;
	}
	return true;
}
