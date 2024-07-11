#include "functions.h"

#define BUFSIZE 1024

using namespace std;

void f_loop() {
	string line;
	vector<string> args;
	int status = 1;

	do {
		cout << ">> ";
		line = f_read_line();
		//args = f_split_line(line);
		//status = f_try_execute(args);
	} while (status);
}

string f_read_line() {
	string line;

	if (!getline(cin, line)) {	// fail
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
