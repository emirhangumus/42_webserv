/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:42:34 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 03:06:04 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../utils/Utils.hpp"
#include <string>
#include <vector>
#include <map>

class ServerParser;

class Config {
	private:
		std::string 						_host;
		int									_port;
		std::vector<std::string>			_server_names;
		std::string 						_root;
		std::string 						_index;
		std::vector<std::string>			_try_files;
		std::string 						_client_max_body_size;
		std::vector<std::string>			_allow_methods;
		std::map<std::string, t_location> 	_locations;

	public:
		Config();
		Config(ServerParser &server);
		~Config();
		Config(const Config &copy);
		Config &operator=(const Config &copy);

		// bool parseConfig(std::string file);
		// void parseBaseBlock(std::string line, int &depth);
		// void parseConfigBlock(std::string line, int &depth);

		std::string getHost() const { return _host; }
		int getPort() const { return _port; }
		std::vector<std::string> getConfigNames() const { return _server_names; }
		std::string getRoot() const { return _root; }
		std::string getIndex() const { return _index; }
		std::vector<std::string> getTryFiles() const { return _try_files; }
		std::string getClientMaxBodySize() const { return _client_max_body_size; }
		std::vector<std::string> getAllowMethods() const { return _allow_methods; }
		std::map<std::string, t_location> getLocations() const { return _locations; }
		t_location getLocation(std::string location) { return _locations[location]; }
};

#endif
