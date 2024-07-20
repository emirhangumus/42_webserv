/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:32:12 by egumus            #+#    #+#             */
/*   Updated: 2024/07/20 16:29:09 by egumus           ###   ########.fr       */
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
	public:
		ConfigManager();
		~ConfigManager();

		bool	parseConfigFile(const std::string &filename);
};

#endif
