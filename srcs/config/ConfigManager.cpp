/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:03:49 by egumus            #+#    #+#             */
/*   Updated: 2024/07/20 16:27:20 by egumus           ###   ########.fr       */
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

bool ConfigManager::parseConfigFile(const std::string &filename)
{
	std::fstream file;

	file.open(filename, std::ios::in);

	if (file.is_open())
	{
		try
		{
			std::string line;
			bool isServerBlock = false;
			bool isInLocationBlock = false;
			// Read data from the file object and put it into a string.
			while (getline(file, line))
			{
				// if the depth is negative or above 3, throw an exception.
				// if (depth < 0 || depth > 3)
				// 	throw std::runtime_error("Invalid depth");
				// Trim the line.
				trim(line);

				// If the line is empty, skip it.
				if (line.empty() || line[0] == COMMENT_CHAR)
					continue;

				std::cout << "Line: " << line << std::endl;

				// If the line is empty, skip it.
				if (line.empty())
					continue;

				std::vector<std::string> tokens = split(line, " ");

				size_t i = 0;
				while (i < tokens.size())
				{
					std::string token = tokens[i];
					if (!isServerBlock)
					{
						if (tokens.size() != 2)
							throw std::runtime_error("Invalid server block [R1]");

						if (!isServerBlock && i == 0 && token != "server")
							throw std::runtime_error("Invalid server block [R2]");

						if (!isServerBlock && i == 1 && token.find("{") == std::string::npos)
							throw std::runtime_error("Invalid server block [R3]");

						isServerBlock = true;
						break;
					}
					else
					{
                        if (!isInLocationBlock && tokens[0] == SSERVER_CONFIG_KEY__LOCATION)
                        {
                            if (tokens.size() != 3)
                                throw std::runtime_error("Invalid location block [R4]");

                            if (tokens.size() == 3 && tokens[2].find("{") == std::string::npos)
                                throw std::runtime_error("Invalid location block [R5]");

                            isInLocationBlock = true;
                        }

                        if (isInLocationBlock && tokens[0] == "}" && tokens.size() == 1)
                        {
                            isInLocationBlock = false;
                            break ;
                        }

						if (!isInLocationBlock && tokens[0] == "}" && tokens.size() == 1)
						{
    					    isServerBlock = false;
						}

						if (isServerBlock)
						{
							ServerParser parser;

							parser.parseServer(line);
							break;
						}
					}
					i++;
				}
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
