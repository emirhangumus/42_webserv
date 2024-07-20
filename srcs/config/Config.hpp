/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:42:34 by egumus            #+#    #+#             */
/*   Updated: 2024/07/20 13:04:25 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>

#define SSERVER_CONFIG_KEY__LISTEN "listen"
#define SSERVER_CONFIG_KEY__SERVER_NAME "server_name"
#define SSERVER_CONFIG_KEY__LOCATION "location"
#define SSERVER_CONFIG_KEY__ROOT "root"
#define SSERVER_CONFIG_KEY__INDEX "index"
#define SSERVER_CONFIG_KEY__TRY_FILES "try_files"
#define SSERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE "client_max_body_size"
#define SSERVER_CONFIG_KEY__ALLOW_METHODS "allow_methods"
#define SSERVER_CONFIG_KEY__RETURN "return"
#define SSERVER_CONFIG_KEY__AUTOINDEX "autoindex"
#define SSERVER_CONFIG_KEY__LIMIT_EXCEPT "limit_except"

enum ConfigConfigKey
{
	SERVER_CONFIG_KEY__LISTEN = 0,
	SERVER_CONFIG_KEY__SERVER_NAME = 1,
	SERVER_CONFIG_KEY__LOCATION = 2,
	SERVER_CONFIG_KEY__ROOT = 3,
	SERVER_CONFIG_KEY__INDEX = 4,
	SERVER_CONFIG_KEY__TRY_FILES = 5,
	SERVER_CONFIG_KEY__CLIENT_MAX_BODY_SIZE = 6,
	SERVER_CONFIG_KEY__ALLOW_METHODS = 7,
	SERVER_CONFIG_KEY__RETURN = 8,
	SERVER_CONFIG_KEY__AUTOINDEX = 9,
	SERVER_CONFIG_KEY__LIMIT_EXCEPT = 10,
	
	SERVER_CONFIG_KEY__INVALID = -1
};

class Config {
	private:
		std::string 				_host;
		int							_port;
		std::vector<std::string>	_server_names;
		std::string 				_root;
		std::string 				_index;
		std::vector<std::string>	_try_files;
		std::string 				_client_max_body_size;
		std::vector<std::string>	_allow_methods;
		
		ConfigConfigKey	isValidConfigKey(std::string key);

	public:
		Config();
		~Config();
		Config(const Config &copy);
		Config &operator=(const Config &copy);
		
		bool parseConfig(std::string file);
		void parseBaseBlock(std::string line, int &depth);
		void parseConfigBlock(std::string line, int &depth);
		
		std::string getHost() const { return _host; }
		int getPort() const { return _port; }
		std::vector<std::string> getConfigNames() const { return _server_names; }
		std::string getRoot() const { return _root; }
		std::string getIndex() const { return _index; }
		std::vector<std::string> getTryFiles() const { return _try_files; }
		std::string getClientMaxBodySize() const { return _client_max_body_size; }
		std::vector<std::string> getAllowMethods() const { return _allow_methods; }
};

#endif