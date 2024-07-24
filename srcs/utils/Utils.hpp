#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <map>

// Trim from the start (left)
std::string& ltrim(std::string& s);

// Trim from the end (right)
std::string& rtrim(std::string& s);

// Trim from both ends (left & right)
std::string& trim(std::string& s);

std::vector<std::string> split(std::string s, std::string delimiter);

bool ends_with(const std::string& str, const std::string& suffix);

std::string extract_host(std::string host);

int is_path_is_file(const std::string& path);

typedef struct s_location {
	std::string 						_location;
	std::string 						_root;
	std::string 						_index;
	std::vector<std::string> 			_try_files;
	std::string 						_client_max_body_size;
	std::map<std::string, std::string> 	_return;
	std::string 						_autoindex;
	std::vector<std::string> 			_limit_except;
}				t_location;

#endif // UTILS_HPP
