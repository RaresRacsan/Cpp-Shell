#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <functional>
#include <cstring>

// List of builtin commands, followed by their corresponding functions
std::vector<std::string> builtin_str = {
    "cd",
    "help",
    "exit"
};

std::vector<std::function<int(std::vector<std::string>&)>> builtin_func = {
    lsh_cd,
    lsh_help,
    lsh_exit
};

int lsh_num_builtins() {
    return builtin_str.size();
}

int lsh_cd(std::vector<std::string>& args) {
	if (args.size() < 2) {
		std::cerr << "err: expected argument to \"cd\"" << std::endl;
	}
	else {
		if (chdir(args[1].c_str()) != 0) {
			std::cerr << "err: " << strerror(errno) << std::endl;
		}
	}
	return 1;
}

int lsh_help(const std::vector<std::string>& args) {
	std::cout << "Rares Racsan's shell." << std::endl;
	std::cout << "Read the README file for info." << std::endl;
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

std::string f_read_line() {
	/**
		* Reading a line from the console
	*/
	std::string line;

	if (!std::getline(std::cin, line)) {	// fail
		perror("readline");
		exit(0);
	}
	else {						// success
		if (feof(stdin)) {
			exit(0);
		}
	}
	return line;
}

std::vector<std::string> f_split_line(std::string line) {
	/**
		* Parameters: a string in which the content of a line read from the console
		* The function separates the word from the line read before
	*/
	std::vector<std::string> arguments;
	std::stringstream ss(line);
	std::string word;

	// extracting the words from the line
	while (ss >> word) {
		arguments.push_back(word);
	}

	return arguments;
}

int f_launch(std::vector<std::string> args) {
	pid_t pid;// , wpid;
	int status;

	pid = fork();	// creating a parent and a child
	// the child will try to exec the command
	// value of pid - 0 => child
	// 		- < 0 => failed fork()
	// 		- > 0 => parent
	if (pid == 0) {
		// child
		std::vector<char*> c_args;
		for (auto& arg : args) {
			c_args.push_back(&arg[0]);
		}
		c_args.push_back(nullptr);

		if (execv(c_args[0], c_args.data()) == -1) {
			perror("Failed to execute command.");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) {
		// failed fork()
		perror("Failed fork");
	}
	else {
		// parent
		do {
			pid_t wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		
	}
	return 1;
}

int f_execute(std::vector<std::string>& args) {
    if (args.empty()) {
        // An empty command was entered.
        return 1;
    }

    for (int i = 0; i < lsh_num_builtins(); ++i) {
        if (args[0] == builtin_str[i]) {
            return builtin_func[i](args);
        }
    }

    return f_launch(args);
}

void f_loop() {
	std::string line;
	std::vector<std::string> args;
	int status = 1;

	do {
		std::cout << ">> ";
		line = f_read_line();
		args = f_split_line(line);
		status = f_execute(args);
	} while (status);
}

int main() {
	f_loop();
	return 0;
}
