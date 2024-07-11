#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <functional>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
#include <filesystem>

// List of the commands that are introduced into the shell
std::vector<std::string> builtin_str = {
    "cd",
    "help",
    "exit",
	"ls",
	"echo",
	"touch",
	"rm"
};

std::vector<std::function<int(std::vector<std::string>&)>> builtin_func = {
    lsh_cd,
    lsh_help,
    lsh_exit,
	lsh_ls,
	lsh_echo,
	lsh_touch,
	lsh_rm
};

int lsh_num_builtins() {
    return builtin_str.size();
}

// The implementation of the commands
int lsh_rm(std::vector<std::string>& args) {
	if (args.size() < 2) {
		std::cerr << "err: expected arguments to \"rm\"" << std::endl;
	}
	else if (args.size() > 2) {
		std::cerr << "err: too many arguments to \"rm\"" << std::endl;
	}
	else {
		std::string file_name = args[1];
		try {
			if (std::filesystem::remove(file_name))
				std::cout << "file " << file_name << " deleted.\n";
			else
				std::cout << "file " << file_name << " not found.\n";
		}
		catch (const std::filesystem::filesystem_error& err) {
			std::cout << "filesystem error: " << err.what() << '\n';
		}
	}
	return 1;
}

int lsh_touch(std::vector<std::string>& args) {
	if (args.size() < 2) {
		std::cerr << "err: expected arguments to \"touch\"" << std::endl;
	}
	else if (args.size() > 2) {
		std::cerr << "err: too many arguments to \"touch\"" << std::endl;
	}
	else {
		std::string file_name = args[1];
		std::ofstream file(file_name);
		if (file.fail()) {
			std::cerr << "err: couldn't create file" << std::endl;
		}
	}
	return 1;
}

int lsh_echo(std::vector<std::string>& args) {
	if (args.size() < 2) {
		std::cerr << "err: expected arguments to \"echo\"" << std::endl;
	}
	else {
		for (int i = 1; i < args.size(); i++) {
			std::cout << args[i] << ' ';
		}
		std::cout << std::endl;
	}
	return 1;
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
	std::cout << "Read the README file for info." << std::endl;
	std::cout << "The following are built in commands:" << std::endl;

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

std::string get_file_type(const std::string& path) {
	struct stat file_stat;

	// Use lstat to get information about the file
	if (lstat(path.c_str(), &file_stat) == -1) {
		perror("lstat error");
		return "error";
	}

	// Check the file type using macros defined in sys/stat.h
	if (S_ISREG(file_stat.st_mode))
		return "regular file";
	else if (S_ISDIR(file_stat.st_mode))
		return "directory";
	else if (S_ISLNK(file_stat.st_mode))
		return "symbolic link";
	else if (S_ISFIFO(file_stat.st_mode))
		return "FIFO/pipe";
	else if (S_ISSOCK(file_stat.st_mode))
		return "socket";
	else if (S_ISCHR(file_stat.st_mode))
		return "character device";
	else if (S_ISBLK(file_stat.st_mode))
		return "block device";
	else
		return "unknown";
}

int lsh_ls(const std::vector<std::string>& args) {
	// checking if there are arguments passed
	if (args.size() > 1) {
		std::cerr << "err: ls command takes no arguments" << std::endl;
		return 1;
	}

	DIR* dir;
	struct dirent* entry;

	// opening the directory
	dir = opendir(".");
	if (dir == NULL) {
		std::cerr << "err: Cannot open directory" << std::endl;
		return 1;
	}

	// read and print the directory content
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.')
			continue;
		std::cout << entry->d_name << " - " << get_file_type(entry->d_name) << std::endl;
	}

	closedir(dir);
	return 1;
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
	pid_t pid;
	int status;

	pid = fork();	

	/* 
		creating a parent and a child
		the child will try to exec the command
		value of pid - 0 => child
	 				 - < 0 => failed fork()
	 				 - > 0 => parent
	*/

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
