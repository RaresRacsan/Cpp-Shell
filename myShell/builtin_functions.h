#ifndef BUILTIN_FUNCTIONS_H
#define BUILTIN_FUNCTIONS_H

#include <vector>
#include <string>
#include <functional>

// Declare external variables
extern std::vector<std::string> builtin_str;
extern std::vector<std::function<int(std::vector<std::string>&)>> builtin_func;

// Declaration of function protorype
int lsh_num_builtins();

#endif // BUILTIN_FUNCTIONS_H

