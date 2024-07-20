#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

// Trim from the start (left)
std::string& ltrim(std::string& s);

// Trim from the end (right)
std::string& rtrim(std::string& s);

// Trim from both ends (left & right)
std::string& trim(std::string& s);

std::vector<std::string> split(std::string s, std::string delimiter);

bool ends_with(const std::string& str, const std::string& suffix);

#endif // UTILS_HPP
