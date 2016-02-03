#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <sstream>
#include <vector>
#include <tuple>

std::vector<std::string>& split_args(std::string args);
std::tuple<std::string, std::string, bool> parse_helper(int argc, char *argv[]);

#endif /* _UTILS_H_ */
