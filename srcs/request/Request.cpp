/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egumus <egumus@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:26:15 by egumus            #+#    #+#             */
/*   Updated: 2024/07/24 01:32:08 by egumus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

Request::Request() {
	this->_request = "";
	this->_method = "";
	this->_uri = "";
	this->_http_version = "";
	this->_headers = std::map<std::string, std::string>();
	this->_body = "";
}

Request::Request(std::string request) {
	this->_request = request;
	this->_method = "";
	this->_uri = "";
	this->_http_version = "";
	this->_headers = std::map<std::string, std::string>();
	this->_body = "";

	this->parseRequest();
}

Request::~Request() {}

bool	Request::parseRequest() {
	std::string line;
	std::string key;
	std::string value;
	std::string body;
	std::string::size_type pos;

	std::istringstream request_stream(this->_request);

	std::getline(request_stream, line);
	std::istringstream line_stream(line);
	line_stream >> this->_method >> this->_uri >> this->_http_version;

	while (std::getline(request_stream, line) && line != "\r") {
		pos = line.find(":");
		key = line.substr(0, pos);
		value = line.substr(pos + 2);
		this->_headers[key] = value;
	}

	if (request_stream) {
		std::getline(request_stream, body);
		this->_body = body;
	}

	return true;
}

std::string	Request::getRequest() {
	return this->_request;
}

std::string	Request::getMethod() {
	return this->_method;
}

std::string	Request::getUri() {
	return this->_uri;
}

std::string	Request::getHttpVersion() {
	return this->_http_version;
}

std::map<std::string, std::string>	Request::getHeaders() {
	return this->_headers;
}

std::string	Request::getBody() {
	return this->_body;
}

void	Request::setRequest(std::string request) {
	this->_request = request;
}

void	Request::setMethod(std::string method) {
	this->_method = method;
}

void	Request::setUri(std::string uri) {
	this->_uri = uri;
}

void	Request::setHttpVersion(std::string http_version) {
	this->_http_version = http_version;
}

void	Request::setHeaders(std::map<std::string, std::string> headers) {
	this->_headers = headers;
}

void	Request::setBody(std::string body) {
	this->_body = body;
}