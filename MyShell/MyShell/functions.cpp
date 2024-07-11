#include "functions.h"

#define BUFSIZE 1024

void f_loop() {
	std::string line;
	std::vector<std::string> args;
	int status = 1;

	do {
		std::cout << ">> ";
		line = f_read_line();
		args = f_split_line(line);
		//status = f_try_execute(args);
	} while (status);
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
