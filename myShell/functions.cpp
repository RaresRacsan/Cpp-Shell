#include "functions.h"

std::vector<std::string> builtin_str = {
    "cd",
    "help",
    "exit"
};

int lsh_cd(std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "lsh: expected argument to \"cd\"" << std::endl;
    }
    else {
        if (chdir(args[1].c_str()) != 0) {
            std::cerr << "lsh: " << strerror(errno) << std::endl;
        }
    }
    return 1;
}

int lsh_help(const std::vector<std::string>& args) {
    std::cout << "Stephen Brennan's LSH" << std::endl;
    std::cout << "Type program names and arguments, and hit enter." << std::endl;
    std::cout << "The following are built in:" << std::endl;

    // Print out the list of built-in commands
    for (const auto& cmd : builtin_str) {
        std::cout << "  " << cmd << std::endl;
    }

    std::cout << "Use the man command for information on other programs." << std::endl;
    return 1;
}

int lsh_exit(const std::vector<std::string>& args) {
    return 0;
}
