/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:44:12 by egumus            #+#    #+#             */
/*   Updated: 2024/07/20 16:27:31 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"
#include "../utils/Utils.hpp"
#include <string>
#include <vector>

ServerParser::ServerParser() {}

ServerParser::~ServerParser() {}

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
	return *this;
}

void ServerParser::parseServer(std::string line)
{
	// If the line is empty, skip it.
	if (line.empty())
		return;

	static std::string location;

	std::vector<std::string> tokens = split(line, " ");
	ConfigConfigKey key;

	// size_t i = 0;
	key = isValidConfigKey(tokens[0]);

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
			if (listen_tokens.size() != 2 || tokens.size() != 2)
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
			{
				location = tokens[1];
				// depth++;
			}

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

ConfigConfigKey	ServerParser::isValidConfigKey(std::string key)
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
