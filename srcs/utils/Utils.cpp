#include "Utils.hpp"
#include <algorithm>
#include <cctype>
#include <vector>

// Functor to check if a character is not a whitespace
struct NotSpace {
    bool operator()(int ch) const {
        return !std::isspace(ch);
    }
};

// Trim from the start (left)
std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), NotSpace()));
    return s;
}

// Trim from the end (right)
std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), NotSpace()).base(), s.end());
    return s;
}

// Trim from both ends (left & right)
std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

// is ends with
bool ends_with(const std::string& str, const std::string& suffix) {
	return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

std::string extract_host(std::string host) {
	// if the host is "localhost" it have to be "127.0.0.1"
	if (host == "localhost")
		host = "127.0.0.1";
	return host;
}

int		is_path_is_file(const std::string& path)
{
	struct stat s;
	if (stat(path.c_str(), &s) == 0 )
	{
		if (s.st_mode & S_IFDIR)
			return 0;
		else if (s.st_mode & S_IFREG)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
