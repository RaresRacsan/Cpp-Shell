#ifndef MYSHELL_FUNCTIONS_H
#define MYSHELL_FUNCTIONS_H

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <functional>
#include <cstring>
#include <sys/stat.h>
#include <fstream>

namespace fs = std::filesystem;

// Function declarations for each shell command
int lsh_cd(std::vector<std::string>& args);
int lsh_help(const std::vector<std::string>& args);
int lsh_exit(const std::vector<std::string>& args);
int lsh_ls(const std::vector<std::string>& args);
int lsh_echo(std::vector<std::string>& args);
int lsh_touch(std::vector<std::string>& args);
int lsh_rm(std::vector<std::string>& args);
int lsh_ping(std::vector<std::string>& args);
int lsh_pwd(std::vector<std::string>& args);
int lsh_mkdir(std::vector<std::string>& args);
int lsh_cat(std::vector<std::string>& args);
int lsh_cp(std::vector<std::string>& args);
int lsh_head(std::vector<std::string>& args);
int lsh_tail(std::vector<std::string>& args);
int lsh_sort(std::vector<std::string>& args);

// Utility functions
std::string get_file_type(const std::string& path);
std::string f_read_line();
std::vector<std::string> f_split_line(std::string line);
int f_launch(std::vector<std::string> args);
int f_execute(std::vector<std::string>& args);
void f_loop();

#endif
