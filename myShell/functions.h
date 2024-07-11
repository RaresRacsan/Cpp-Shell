#ifndef MYSHELLFUNCTIONS_H
#define MYSHELLFUNCTIONS_H

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cerrno>

int lsh_cd(std::vector<std::string>& args);
int lsh_help(const std::vector<std::string>& args);
int lsh_exit(const std::vector<std::string>& args);
int lsh_ls(const std::vector<std::string>& args);
int lsh_echo(std::vector<std::string>& args);
int lsh_touch(std::vector<std::string>& args);
int lsh_rm(std::vector<std::string>& args);
int lsh_ping(std::vector<std::string>& args);

#endif // MYSHELLFUNCTIONS_H
