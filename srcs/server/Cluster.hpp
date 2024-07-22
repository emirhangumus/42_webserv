/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:58:05 by egumus            #+#    #+#             */
/*   Updated: 2024/07/22 03:28:18 by egumus           ###   ########.fr       */
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

class Cluster
{
	private:
		ConfigManager	*_configManager;
		std::string		_config_file;
	
	public:
		Cluster();
		Cluster(std::string config_file);
		~Cluster();

		bool	initCluster();
		bool	runCluster();
		void	test();
};

#endif