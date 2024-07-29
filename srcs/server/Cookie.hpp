/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cookie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:08:24 by burkaya           #+#    #+#             */
/*   Updated: 2024/07/29 16:38:07 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COOKIE_HPP
# define COOKIE_HPP

# include <iostream>
# include <string>
# include <map>

class Cookie
{
    public:
        Cookie();
        Cookie(std::string const &cookie);
        Cookie(Cookie const &src);
        ~Cookie();

        Cookie &operator=(Cookie const &rhs);

        std::string getCookie(std::string const &key) const;
        void setCookie(std::string const &cookie);
        void setCookie(std::string const &key, std::string const &value);
        void printCookies() const;
        void deleteCookie(std::string const &key);

    private:
        std::map<std::string, std::string> _cookie;
};

#endif