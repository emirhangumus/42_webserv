/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:44:12 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 09:03:41 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"
#include "Config.hpp"
#include "../utils/Utils.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>

ServerParser::ServerParser() {
	_host = "";
	_port = 0;
	_server_names.clear();
	_root = "";
	_index = "";
	_try_files.clear();
	_client_max_body_size = "";
	_allow_methods.clear();
	_locations.clear();
}

ServerParser::~ServerParser() {
	_host = "";
	_port = 0;
	_server_names.clear();
	_root = "";
	_index = "";
	_try_files.clear();
	_client_max_body_size = "";
	_allow_methods.clear();
	_locations.clear();
}

ServerParser::ServerParser(const ServerParser &copy)
{
	*this = copy;
}

ServerParser &ServerParser::operator=(const ServerParser &copy)
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
	_locations = copy._locations;
	return *this;
}

void	ServerParser::parseLine(std::string line)
{
	// If the line is empty, skip it.
	if (line.empty())
		return ;

	static t_location	loc;

	std::vector<std::string> tokens = split(line, " ");

	if (loc._location.empty()){

		ConfigConfigKey key = isValidServerBlockKey(tokens[0]);

		/**
		 * If the key is invalid, throw an exception.
		*/
		if (key == SERVER_CONFIG_KEY__INVALID && loc._location.empty())
			throw std::runtime_error("Invalid server config key `" + tokens[0] + "`");

		// if (key == SERVER_CONFIG_KEY__INVALID && !location.empty())
		// {
		// 	key = SERVER_CONFIG_KEY__LOCATION;
		// 	tokens.insert(tokens.begin(), location);
		// }

		std::vector<std::string> listen_tokens;

		switch (key)
		{
			case SERVER_CONFIG_KEY__LISTEN:
				// Parse the listen directive.
				listen_tokens = split(tokens[1], ":");
				if (listen_tokens.size() != 2 || tokens.size() != 2)
					throw std::runtime_error("Invalid listen directive");
				_host = extract_host(listen_tokens[0]);
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
					loc._location = tokens[1];

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
			default:
				break;
			

		}
	}
	else {
		ConfigConfigKey key = isValidLocationBlockKey(tokens[0]);

		if (key == SERVER_CONFIG_KEY__INVALID && tokens[0] == "}")
		{
			std::cout << "new_loc._location: " << loc._location << std::endl;
			_locations.insert(std::pair<std::string, t_location>(loc._location, loc));
			std::cout << "new_loc._location: " << loc._location << std::endl;

			loc._location = "";
			loc._root = "";
			loc._index = "";
			loc._try_files.clear();
			loc._client_max_body_size = "";
			loc._return.clear();
			loc._autoindex = "";
			loc._limit_except.clear();
			return ;
		}

		/**
		 * If the key is invalid, throw an exception.
		*/
		if (key == SERVER_CONFIG_KEY__INVALID)
			throw std::runtime_error("Invalid location config key `" + tokens[0] + "`");

		std::vector<std::string> listen_tokens;

		switch (key)
		{
			case SERVER_CONFIG_KEY__ROOT:
				// Parse the root directive.
				if (tokens.size() != 2)
					throw std::runtime_error("Invalid root directive");

				loc._root = tokens[1];

				break;
			case SERVER_CONFIG_KEY__INDEX:
				// Parse the index directive.
				if (tokens.size() != 2)
					throw std::runtime_error("Invalid index directive");

				loc._index = tokens[1];

				break;
			case SERVER_CONFIG_KEY__TRY_FILES:
				// Parse the try_files directive.
				if (tokens.size() < 2)
					throw std::runtime_error("Invalid try_files directive");

				for (size_t i = 1; i < tokens.size(); i++)
					loc._try_files.push_back(tokens[i]);

				break;
			case SERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE:
				// Parse the client_max_body_size directive.
				if (tokens.size() != 2)
					throw std::runtime_error("Invalid client_max_body_size directive");

				loc._client_max_body_size = tokens[1];

				break;
			case SERVER_CONFIG_KEY__LIMIT_EXCEPT:
				// Parse the limit_except directive.
				if (tokens.size() < 2)
					throw std::runtime_error("Invalid limit_except directive");

				for (size_t i = 1; i < tokens.size(); i++)
					loc._limit_except.push_back(tokens[i]);

				break;
			case SERVER_CONFIG_KEY__RETURN:
				// Parse the return directive.
				if (tokens.size() != 3)
					throw std::runtime_error("Invalid return directive");

				loc._return[tokens[2]] = tokens[1];

				break;
			case SERVER_CONFIG_KEY__AUTOINDEX:
				// Parse the autoindex directive.
				if (tokens.size() != 2)
					throw std::runtime_error("Invalid autoindex directive");

				loc._autoindex = tokens[1];

				break;
			default:
				break;
		}
	}
}

Config *ServerParser::parseServer(std::vector<std::string> serverBlockLines)
{
	size_t i = 0;

	try {
		while (i < serverBlockLines.size())
		{
			parseLine(serverBlockLines[i]);
			i++;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return NULL;
	}

	Config *config = new Config(*this);

	return config;
}

ConfigConfigKey	ServerParser::isValidServerBlockKey(std::string key)
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
	if (key == SSERVER_CONFIG_KEY__LIMIT_EXCEPT)
		return SERVER_CONFIG_KEY__LIMIT_EXCEPT;
	if (key == SSERVER_CONFIG_KEY__RETURN)
		return SERVER_CONFIG_KEY__RETURN;
	if (key == SSERVER_CONFIG_KEY__AUTOINDEX)
		return SERVER_CONFIG_KEY__AUTOINDEX;
	return SERVER_CONFIG_KEY__INVALID;
}

ConfigConfigKey	ServerParser::isValidLocationBlockKey(std::string key)
{
	if (key == SSERVER_CONFIG_KEY__ROOT)
		return SERVER_CONFIG_KEY__ROOT;
	if (key == SSERVER_CONFIG_KEY__INDEX)
		return SERVER_CONFIG_KEY__INDEX;
	if (key == SSERVER_CONFIG_KEY__TRY_FILES)
		return SERVER_CONFIG_KEY__TRY_FILES;
	if (key == SSERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE)
		return SERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE;
	if (key == SSERVER_CONFIG_KEY__LIMIT_EXCEPT)
		return SERVER_CONFIG_KEY__LIMIT_EXCEPT;
	if (key == SSERVER_CONFIG_KEY__RETURN)
		return SERVER_CONFIG_KEY__RETURN;
	if (key == SSERVER_CONFIG_KEY__AUTOINDEX)
		return SERVER_CONFIG_KEY__AUTOINDEX;
	return SERVER_CONFIG_KEY__INVALID;
}