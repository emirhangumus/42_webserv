/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:58:05 by egumus            #+#    #+#             */
/*   Updated: 2024/07/20 13:03:19 by egumus           ###   ########.fr       */
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

class Cluster
{
	private:
		std::map<std::string, Config>	_servers;
};

#endif