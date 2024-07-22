/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:32:12 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 03:13:54 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGMANAGER_HPP
# define CONFIGMANAGER_HPP

# include <string>
# include <map>
# include "Config.hpp"

# define COMMENT_CHAR '#'

class ConfigManager {
	private:
		std::map<std::string, Config>	_servers;
		
		std::vector<std::vector<int> >	serverBlockCount(const std::string &filename);
	public:
		ConfigManager();
		~ConfigManager();

		bool							parseConfigFile(const std::string &filename);
		std::map<std::string, Config>	getServers() const { return _servers; }
		Config							getServer(std::string server_name) { return _servers[server_name]; }
};

#endif
