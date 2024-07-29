/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cookie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:09:37 by burkaya           #+#    #+#             */
/*   Updated: 2024/07/29 16:41:21 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cookie.hpp"

Cookie::Cookie() {}

Cookie::Cookie(std::string const &cookie)
{
    std::string key;
    std::string value;
    size_t pos = 0;
    size_t pos2 = 0;

    while (pos != std::string::npos)
    {
        pos2 = cookie.find('=', pos);
        key = cookie.substr(pos, pos2 - pos);
        pos = pos2 + 1;
        pos2 = cookie.find(';', pos);
        value = cookie.substr(pos, pos2 - pos);
        pos = pos2 + 2;
        _cookie[key] = value;
    }
}

Cookie::Cookie(Cookie const &src)
{
    *this = src;
}

Cookie::~Cookie() {}

Cookie &Cookie::operator=(Cookie const &rhs)
{
    if (this != &rhs)
        _cookie = rhs._cookie;
    return *this;
}

std::string Cookie::getCookie(std::string const &key) const
{
    std::map<std::string, std::string>::const_iterator it = _cookie.find(key);
    if (it != _cookie.end())
        return it->second;
    return "";
}

void Cookie::setCookie(std::string const &cookie)
{
    std::string key;
    std::string value;
    size_t pos = 0;
    size_t pos2 = 0;
    bool    flag = true;
    
    while (flag)
    {
        pos2 = cookie.find('=', pos);
        if (pos2 == std::string::npos)
            break;
        key = cookie.substr(pos, pos2 - pos);
        pos = pos2 + 1;
        pos2 = cookie.find(';', pos);
        if (pos2 == std::string::npos)
        {
            pos2 = cookie.size();
            flag = false;
        }
        value = cookie.substr(pos, pos2 - pos);
        pos = pos2 + 2;
        _cookie[key] = value;
    }
}

void Cookie::setCookie(std::string const &key, std::string const &value)
{
    _cookie[key] = value;
}

void Cookie::deleteCookie(std::string const &key)
{
    _cookie.erase(key);
}

void Cookie::printCookies() const
{
    std::map<std::string, std::string>::const_iterator it = _cookie.begin();
    while (it != _cookie.end())
    {
        std::cout << it->first << "\t=\t" << it->second << std::endl;
        it++;
    }
}
