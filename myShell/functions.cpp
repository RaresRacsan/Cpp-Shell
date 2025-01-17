#include "functions.h"
#include "builtin_functions.h"

// The implementation of the available commands
int lsh_sort(std::vector<std::string>& args){
	// sort file
	// sorting the lines of the file "file"
	if(args.size() != 2){//incorrect structure
		std::cerr << "err: incorrect number of arguments for \"sort\"" << std::endl;
	}
	else{
		std::string file = args[1];	// file

		// opening the file
		std::ifstream fileIn(file);

		std::vector<std::string> lines;
		std::string line;

		// keeping the lines in a vector to be able to sort them
		while(std::getline(fileIn, line)){
			lines.push_back(line);
		}

		sort(lines.begin(), lines.end());

		// printing the sorted lines
		for(int i = 0; i < lines.size(); i++){
			std::cout << lines[i] << std::endl;
		}

		fileIn.close();
	}
	return 1;
}

int lsh_tail(std::vector<std::string>& args){
	// tail nr_lines file
	// prints the last "nr_lines" lines from the file "file"
	if(args.size() != 3){//incorrect structure
		std::cerr << "err: incorrect number of arguments for \"head\"" << std::endl;
	}
	else{
		int lines = std::stoi(args[1]);	// inputed nr of lines
		std::string file = args[2];		// inputed file

		// opening the file
		std::ifstream fileIn(file);

		std::vector<std::string> l;
		std::string line;

		// creating a vector containing all the lines of the file in order
		// to see if the "nr_lines" > actual nr of line
		while(std::getline(fileIn, line)){
			l.push_back(line);
		}

		int nrLines = l.size();
		int startLine = (nrLines > lines) ? nrLines - lines : 0;

		// printing the saved lines
		for(int i = startLine; i < nrLines; i++){
			std::cout << l[i] << std::endl;
		}

		fileIn.close();
	}
	return 1;
}

int lsh_head(std::vector<std::string>& args){
	// head nr_line file
	// prints the first "nr_line" lines from the file "file"
	if(args.size() != 3){//incorrect structure
		std::cerr << "err: incorrect number of arguments for \"head\"" << std::endl;
	}
	else{
		int lines = std::stoi(args[1]);	// inputed nr of lines
		std::string file = args[2];		// file

		// opening the file
		std::ifstream fileIn (file);

		if(fileIn.is_open()){	// open
			std::string line;
			// printing the lines 
			for(int i = 0; i < lines && std::getline(fileIn, line); i++){
				std::cout << line<< std::endl;
			}
		}
		else{	// not open
			std::cerr << "err: couldn't open the file" << std::endl;
		}
		fileIn.close();
	}
	return 1;
}

int lsh_cp(std::vector<std::string>& args){
	// cp source destination
	if(args.size() != 3){//incorrect structure
		std::cerr << "err: incorrect number of arguments for \"cp\"" << std::endl;
	}
	else{
		std::string from = args[1];	// source
		std::string to = args[2];	// destination
		try {
        // Perform the copy operation
        fs::copy_file(from, to, fs::copy_options::overwrite_existing);

        std::cout << "File copied successfully." << std::endl;
    } catch (const fs::filesystem_error& e) {//error
        std::cerr << "Error copying file: " << e.what() << std::endl;
    } 
	}
	return 1;
}

int lsh_cat(std::vector<std::string>& args){
	// cat file
	if(args.size() != 2){//incorrect structure
		std::cerr << "err: incorrect number of arguments for \"cat\"" << std::endl;
	}
	else{
		// opening the file
		std::string file = args[1];
		std::ifstream fileIn(file);

		// printing the content of the file
		std::cout << std::string((std::istreambuf_iterator<char>(fileIn)),( std::istreambuf_iterator<char>()));
		std::cout << std::endl;

		fileIn.close();
	}
	return 1;
}

int lsh_mkdir(std::vector<std::string>& args){
	// mkdir directory_name
	if(args.size() != 2){//incorrect structure
		std::cerr << "err: incorrect number of arguments for \"mkdir\"" << std::endl;
	}
	else{
		// in args[1] is the directorry_name
		// creating new directory
		std::filesystem::create_directory(args[1]);
	}
	return 1;
}

int lsh_pwd(std::vector<std::string>& args){
	// pwd
	if(args.size() != 1){// incorrect structure
		std::cerr << "err: Number of arguments is invalid for \"pwd\"" << std::endl;
	}
	else{
		// Get the current working directory
    	fs::path currentPath = fs::current_path();
    
    	// Output the current working directory
    	std::cout << "Current Directory: " << currentPath << std::endl;
	}
	return 1;
}

int lsh_ping(std::vector<std::string>& args) {
	// ping host
	if (args.size() < 2) {// incorrect structure
		std::cerr << "err: expected argument to \"ping\"" << std::endl;
		return 1;
	}

	// the second argument is going to be the host
	std::string host = args[1];

	// Prepare command and arguments for execvp
	std::vector<char*> c_args;
	c_args.push_back(const_cast<char*>("ping"));    // Command
	c_args.push_back(const_cast<char*>("-c"));      // Count option
	c_args.push_back(const_cast<char*>("4"));       // Number of requests
	c_args.push_back(const_cast<char*>(host.c_str())); // Host
	c_args.push_back(nullptr);                      // Null-terminated array

	// Fork a child process
	pid_t pid = fork();

	if (pid == 0) {
		// Child process: execute ping command
		if (execvp("ping", c_args.data()) == -1) {
			perror("Failed to execute command.");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) {
		// Forking failed
		perror("Failed to fork");
	}
	else {
		// Parent process: wait for child to finish
		int status;
		do {
			pid_t wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int lsh_rm(std::vector<std::string>& args) {
	// rm file
	if (args.size() < 2) {//incorrect structure
		std::cerr << "err: expected arguments to \"rm\"" << std::endl;
	}
	else if (args.size() > 2) {//incorrect structure
		std::cerr << "err: too many arguments to \"rm\"" << std::endl;
	}
	else {
		std::string file_name = args[1];
		// trying to remove the file, if it is found
		try {
			if (std::filesystem::remove(file_name))	// found
				std::cout << "file " << file_name << " deleted.\n";
			else	// not found
				std::cout << "file " << file_name << " not found.\n";
		}
		catch (const std::filesystem::filesystem_error& err) {	// error
			std::cout << "filesystem error: " << err.what() << '\n';
		}
	}
	return 1;
}

int lsh_touch(std::vector<std::string>& args) {
	//touch file_name
	if (args.size() < 2) {//incorrect structure
		std::cerr << "err: expected arguments to \"touch\"" << std::endl;
	}
	else if (args.size() > 2) {//incorrect structure
		std::cerr << "err: too many arguments to \"touch\"" << std::endl;
	}
	else {
		// trying to create a file with the name typed after the touch command
		std::string file_name = args[1];
		std::ofstream file(file_name);
		if (file.fail()) {	// failed
			std::cerr << "err: couldn't create file" << std::endl;
		}
		// no error message => file created 
		file.close();
	}
	return 1;
}

int lsh_echo(std::vector<std::string>& args) {
	// echo message
	if (args.size() < 2) {// incorrect structure
		std::cerr << "err: expected arguments to \"echo\"" << std::endl;
	}
	else {
		// printing the arguments that were typed into the console
		for (int i = 1; i < args.size(); i++) {
			std::cout << args[i] << ' ';
		}
		std::cout << std::endl;
	}
	return 1;
}

int lsh_cd(std::vector<std::string>& args) {
	// cd directory_name
	if (args.size() < 2) {//incorrect structure
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
	// help
	std::cout << "Read the CommandsFile file for more info." << std::endl;
	std::cout << "The following are built in commands:" << std::endl;

	// Print out the list of built-in commands
	for (const auto& cmd : builtin_str) {
		std::cout << "  " << cmd << std::endl;
	}

	std::cout << "Use the man command for information on other programs." << std::endl;
	return 1;
}

int lsh_exit(const std::vector<std::string>& args) {
	// exit
	// Changing the status to 0
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

	// read and print the directory content ( name - file type )
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.')
			continue;
		std::cout << entry->d_name << " - " << get_file_type(entry->d_name) << std::endl;
	}

	closedir(dir);
	return 1;
}

std::string f_read_line() {
	// Reading a line from the console
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
	// Parameters: a string in which the content of a line read from the console
	// The function separates the word from the line read before
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

	// Search the function in the built-in functions 
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

	// Keep going until the status is 0 (exit was typed)
	do {
		std::cout << ">> ";
		line = f_read_line();
		args = f_split_line(line);
		status = f_execute(args);
	} while (status);
}
