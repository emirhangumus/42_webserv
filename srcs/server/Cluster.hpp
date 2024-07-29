/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:58:05 by egumus            #+#    #+#             */
/*   Updated: 2024/07/29 14:13:21 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_HPP
# define CLUSTER_HPP

# include <iostream>
# include <vector>
# include <map>
# include <string>
# include <fstream>
# include "Config.hpp"
# include "ConfigManager.hpp"
# include "Cookie.hpp"

class Cluster
{
	private:
		ConfigManager	*_configManager;
		std::string		_config_file;
		Cookie			_cookie;
	
	public:
		Cluster();
		Cluster(std::string config_file);
		~Cluster();

		bool	initCluster();
		bool	runCluster();
		void	parseCookie(std::string cookie);
		void	test(std::string key);
};

#endif