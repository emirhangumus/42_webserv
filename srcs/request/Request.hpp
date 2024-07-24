/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:25:32 by egumus            #+#    #+#             */
/*   Updated: 2024/07/24 01:26:00 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>

class Request
{
	public:
		Request();
		Request(std::string request);
		~Request();

		std::string getRequest();
		std::string getMethod();
		std::string getUri();
		std::string getHttpVersion();
		std::map<std::string, std::string> getHeaders();
		std::string getBody();

		void setRequest(std::string request);
		void setMethod(std::string method);
		void setUri(std::string uri);
		void setHttpVersion(std::string http_version);
		void setHeaders(std::map<std::string, std::string> headers);
		void setBody(std::string body);

		bool parseRequest();

	private:
		std::string _request;
		std::string _method;
		std::string _uri;
		std::string _http_version;
		std::map<std::string, std::string> _headers;
		std::string _body;
};

#endif