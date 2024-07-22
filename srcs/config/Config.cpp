/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:44:12 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 03:05:48 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "ServerParser.hpp"
#include <string>
#include <vector>

Config::Config() {
	_host = "";
	_port = 0;
	_server_names = std::vector<std::string>();
	_root = "";
	_index = "";
	_try_files = std::vector<std::string>();
	_client_max_body_size = "";
	_allow_methods = std::vector<std::string>();
	_locations = std::map<std::string, t_location>();
}

Config::Config(ServerParser &server) {
	_host = server.getHost();
	_port = server.getPort();
	_server_names = server.getServerNames();
	_root = server.getRoot();
	_index = server.getIndex();
	_try_files = server.getTryFiles();
	_client_max_body_size = server.getClientMaxBodySize();
	_allow_methods = server.getAllowMethods();
	_locations = server.getLocations();
}

Config::~Config() {}

Config::Config(const Config &copy)
{
	_host = copy._host;
	_port = copy._port;
	_server_names = copy._server_names;
	_root = copy._root;
	_index = copy._index;
	_try_files = copy._try_files;
	_client_max_body_size = copy._client_max_body_size;
	_allow_methods = copy._allow_methods;
	_locations = copy._locations;
}

Config &Config::operator=(const Config &copy)
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

