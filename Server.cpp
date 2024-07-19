/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:44:12 by egumus            #+#    #+#             */
/*   Updated: 2024/07/20 02:44:11 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Utils.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

Server::Server() {}

Server::~Server() {}

Server::Server(const Server &copy)
{
	*this = copy;
}

Server &Server::operator=(const Server &copy)
{
	if (this == &copy)
		return *this;
	_host = copy._host;
	_port = copy._port;
	_server_names = copy._server_names;
	_root = copy._root;
	_index = copy._index;
	_try_files = copy._try_files;
	_client_max_body_size = copy._client_max_body_size;
	_allow_methods = copy._allow_methods;
	return *this;
}

void Server::parseBaseBlock(std::string line, int &depth)
{
	// If the line is empty, skip it.
	if (line.empty())
		return;
		
	std::vector<std::string> tokens = split(line, " ");

	if (tokens.size() != 2)
		throw std::runtime_error("Invalid server block");


	size_t i = 0;
	while (i < tokens.size())
	{
		std::string token = tokens[i];
		
		if (i == 0 && token != "server")
			throw std::runtime_error("Invalid server block");
		
		if (i == 1 && token.find("{") == std::string::npos)
			throw std::runtime_error("Invalid server block");
		i++;
	}
	depth++;
}

void Server::parseServerBlock(std::string line, int &depth)
{
	(void)depth;
	// If the line is empty, skip it.
	if (line.empty())
		return;

	std::vector<std::string> tokens = split(line, " ");
	ServerConfigKey key;

	// size_t i = 0;
	key = isValidConfigKey(tokens[0]);
	
	/**
	 * If the first token is not valid but its "}" then decrease the depth and return.
	*/
	if (key == SERVER_CONFIG_KEY__INVALID && tokens[0] == "}")
	{
		depth--;
		return;
	}
		
	/**
	 * If the key is invalid, throw an exception.
	*/
	if (key == SERVER_CONFIG_KEY__INVALID)
		throw std::runtime_error("Invalid server config key " + tokens[0]);
		
	/**
	 * If the key is not the location key and the value does not end with a semicolon, throw an exception.
	*/
	// if (key != SERVER_CONFIG_KEY__LOCATION && ends_with(tokens[tokens.size() - 1], ";") == false)
	// {
	// 	std::cout << "Invalid server config value" << std::endl;
	// 	throw std::runtime_error("Invalid server config value");
	// }
	std::vector<std::string> listen_tokens;

	switch (key)
	{
		case SERVER_CONFIG_KEY__LISTEN:
			// Parse the listen directive.
			listen_tokens = split(tokens[1], ":");
			if (listen_tokens.size() != 2)
				throw std::runtime_error("Invalid listen directive");
			_host = listen_tokens[0];
			_port = std::stoi(listen_tokens[1]);
			break;
		case SERVER_CONFIG_KEY__SERVER_NAME:
			// Parse the server_name directive.
			if (tokens.size() < 2)
				throw std::runtime_error("Invalid server_name directive");

			for (size_t i = 1; i < tokens.size(); i++)
				_server_names.push_back(tokens[i]);

			break;
		case SERVER_CONFIG_KEY__LOCATION:
			// Parse the location directive.
			
			// if tokens size not equal 3, throw an exception.
			if (tokens.size() != 3)
				throw std::runtime_error("Invalid location directive");

			// If the location directive does not end with a bracket, increase the depth.
			if (tokens[tokens.size() - 1] == "{")
				depth++;
			
			break;
		case SERVER_CONFIG_KEY__ROOT:
			// Parse the root directive.
			if (tokens.size() != 2)
				throw std::runtime_error("Invalid root directive");
			
			_root = tokens[1];
			
			break;
		case SERVER_CONFIG_KEY__INDEX:
			// Parse the index directive.
			if (tokens.size() != 2)
				throw std::runtime_error("Invalid index directive");
				
			_index = tokens[1];

			break;
		case SERVER_CONFIG_KEY__TRY_FILES:
			// Parse the try_files directive.
			if (tokens.size() < 2)
				throw std::runtime_error("Invalid try_files directive");

			for (size_t i = 1; i < tokens.size(); i++)
				_try_files.push_back(tokens[i]);

			break;
		case SERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE:
			// Parse the client_max_body_size directive.
			if (tokens.size() != 2)
				throw std::runtime_error("Invalid client_max_body_size directive");

			_client_max_body_size = tokens[1];

			break;
		case SERVER_CONFIG_KEY__ALLOW_METHODS:
			// Parse the allow_methods directive.
			if (tokens.size() < 2)
				throw std::runtime_error("Invalid allow_methods directive");
				
			for (size_t i = 1; i < tokens.size(); i++)
				_allow_methods.push_back(tokens[i]);
				
			break;
		default:
			break;
	}
}

ServerConfigKey	Server::isValidConfigKey(std::string key)
{
	if (key == SSERVER_CONFIG_KEY__LISTEN)
		return SERVER_CONFIG_KEY__LISTEN;
	if (key == SSERVER_CONFIG_KEY__SERVER_NAME)
		return SERVER_CONFIG_KEY__SERVER_NAME;
	if (key == SSERVER_CONFIG_KEY__LOCATION)
		return SERVER_CONFIG_KEY__LOCATION;
	if (key == SSERVER_CONFIG_KEY__ROOT)
		return SERVER_CONFIG_KEY__ROOT;
	if (key == SSERVER_CONFIG_KEY__INDEX)
		return SERVER_CONFIG_KEY__INDEX;
	if (key == SSERVER_CONFIG_KEY__TRY_FILES)
		return SERVER_CONFIG_KEY__TRY_FILES;
	if (key == SSERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE)
		return SERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE;
	if (key == SSERVER_CONFIG_KEY__ALLOW_METHODS)
		return SERVER_CONFIG_KEY__ALLOW_METHODS;
	if (key == SSERVER_CONFIG_KEY__RETURN)
		return SERVER_CONFIG_KEY__RETURN;
	if (key == SSERVER_CONFIG_KEY__AUTOINDEX)
		return SERVER_CONFIG_KEY__AUTOINDEX;
	if (key == SSERVER_CONFIG_KEY__LIMIT_EXCEPT)
		return SERVER_CONFIG_KEY__LIMIT_EXCEPT;
	return SERVER_CONFIG_KEY__INVALID;
}

bool Server::parseConfig(std::string file_path)
{
	std::fstream file;

	file.open(file_path, std::ios::in);

	// get the line
	// std::string line = NULL;
	int depth = 0;

	if (file.is_open())
	{
		try
		{
			std::string line;
			// Read data from the file object and put it into a string.
			while (getline(file, line))
			{
				// if the depth is negative or above 3, throw an exception.
				if (depth < 0 || depth > 3)
					throw std::runtime_error("Invalid depth");
				// Trim the line.
				trim(line);

				// If the line is empty, skip it.
				if (line.empty() || line[0] == '#')
					continue;
				
				std::cout << "Line: " << line << " Depth: \x1B[31m" << depth << "\033[0m" << std::endl;

				// Parse the line based on the depth.
				switch (depth)
				{
					case 0:
						parseBaseBlock(line, depth);
						break;
					default:
						parseServerBlock(line, depth);
						break;
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