/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:42:34 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 08:55:15 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERPARSER_HPP
#define SERVERPARSER_HPP

#include "Config.hpp"
#include "../utils/Utils.hpp"
#include <string>
#include <vector>
#include <map>

#define SSERVER_CONFIG_KEY__LISTEN "listen" // server
#define SSERVER_CONFIG_KEY__SERVER_NAME "server_name" // server
#define SSERVER_CONFIG_KEY__LOCATION "location" // server
#define SSERVER_CONFIG_KEY__ROOT "root" // server location
#define SSERVER_CONFIG_KEY__INDEX "index" // server location
#define SSERVER_CONFIG_KEY__TRY_FILES "try_files" // server location
#define SSERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE "client_max_body_size" // server location
#define SSERVER_CONFIG_KEY__LIMIT_EXCEPT "limit_except" // location
#define SSERVER_CONFIG_KEY__RETURN "return" // server location
#define SSERVER_CONFIG_KEY__AUTOINDEX "autoindex" // server location

enum ConfigConfigKey
{
	SERVER_CONFIG_KEY__LISTEN = 0,
	SERVER_CONFIG_KEY__SERVER_NAME = 1,
	SERVER_CONFIG_KEY__LOCATION = 2,
	SERVER_CONFIG_KEY__ROOT = 3,
	SERVER_CONFIG_KEY__INDEX = 4,
	SERVER_CONFIG_KEY__TRY_FILES = 5,
	SERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE = 6,
	SERVER_CONFIG_KEY__LIMIT_EXCEPT = 7,
	SERVER_CONFIG_KEY__RETURN = 8,
	SERVER_CONFIG_KEY__AUTOINDEX = 9,

	SERVER_CONFIG_KEY__INVALID = -1
};

class ServerParser {
	private:
		std::string 						_host;
		int									_port;
		std::vector<std::string>			_server_names;
		std::string 						_root;
		std::string 						_index;
		std::vector<std::string>			_try_files;
		std::string 						_client_max_body_size;
		std::vector<std::string>			_allow_methods;
		std::map<std::string, t_location>	_locations;

		ConfigConfigKey	isValidServerBlockKey(std::string key);
		ConfigConfigKey	isValidLocationBlockKey(std::string key);
		void			parseLine(std::string line);
	public:
		ServerParser();
		~ServerParser();
		ServerParser(const ServerParser &copy);
		ServerParser &operator=(const ServerParser &copy);

		Config *parseServer(std::vector<std::string> serverBlockLines);

		std::string getHost() const { return _host; }
		int getPort() const { return _port; }
		std::vector<std::string> getServerNames() const { return _server_names; }
		std::string getRoot() const { return _root; }
		std::string getIndex() const { return _index; }
		std::vector<std::string> getTryFiles() const { return _try_files; }
		std::string getClientMaxBodySize() const { return _client_max_body_size; }
		std::vector<std::string> getAllowMethods() const { return _allow_methods; }
		std::map<std::string, t_location> getLocations() const { return _locations; }
		t_location getLocation(std::string location) { return _locations[location]; }
};

#endif
