#ifndef BUILTIN_FUNCTIONS_H
#define BUILTIN_FUNCTIONS_H

#include <vector>
#include <string>
#include <functional>

extern std::vector<std::string> builtin_str;
extern std::vector<std::function<int(std::vector<std::string>&)>> builtin_func;

int lsh_num_builtins();

#endif // BUILTIN_FUNCTIONS_H

