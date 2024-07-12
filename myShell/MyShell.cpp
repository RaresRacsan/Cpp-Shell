#include "functions.h"
#include "builtin_functions.h"

namespace fs = std::filesystem;

// List of the commands that are introduced into the shell
std::vector<std::string> builtin_str = {
    "cd",
    "help",
    "exit",
	"ls",
	"echo",
	"touch",
	"rm",
	"ping",
	"pwd", 
	"mkdir",
	"cat",
	"cp",
	"head",
	"tail",
	"sort"
};

std::vector<std::function<int(std::vector<std::string>&)>> builtin_func = {
    lsh_cd,
    lsh_help,
    lsh_exit,
	lsh_ls,
	lsh_echo,
	lsh_touch,
	lsh_rm,
	lsh_ping,
	lsh_pwd,
	lsh_mkdir,
	lsh_cat,
	lsh_cp,
	lsh_head,
	lsh_tail,
	lsh_sort
};

int lsh_num_builtins() {
    return builtin_str.size();
}

int main() {
	f_loop();
	return 0;
}
