#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

// Trim from the start (left)
std::string& ltrim(std::string& s);

// Trim from the end (right)
std::string& rtrim(std::string& s);

// Trim from both ends (left & right)
std::string& trim(std::string& s);

std::vector<std::string> split(std::string s, std::string delimiter);

bool ends_with(const std::string& str, const std::string& suffix);

std::string extract_host(std::string host);

typedef struct s_location {
	std::string 				location;
	std::string 				root;
	std::string 				index;
	std::vector<std::string> 	try_files;
	std::string 				client_max_body_size;
	std::vector<std::string> 	allow_methods;
}				t_location;

#endif // UTILS_HPP
