# MyShell
It is a simple Unix-like shell implemented in C++. It supports several built-in commands and provides basic file and process management functionalities. This project serves as a learning tool for understanding how command-line interpreters work.

## Features
- Built-in Commands: Supports common shell commands such as cd, ls, cp, rm, echo, mkdir, and more.
- File Operations: Provides file manipulation commands like cat, head, tail, sort, and cp.
- Process Management: Includes commands like ping and exit.
- Error Handling: Basic error handling for incorrect usage of commands.

## Commands

Here is a list of supported built-in commands:

- cd <directory>: Change the current directory.
- help: Display information about built-in commands.
- exit: Exit the shell.
- ls: List files in the current directory.
- echo <message>: Print a message to the terminal.
- touch <file>: Create a new file.
- rm <file>: Remove a file.
- ping <host>: Ping a host.
- pwd: Print the current working directory.
- mkdir <directory>: Create a new directory.
- cat <file>: Display the contents of a file.
- cp <source> <destination>: Copy a file.
- head <number_of_lines> <file>: Display the first few lines of a file.
- tail <number_of_lines> <file>: Display the last few lines of a file.
- sort <file>: Sort the contents of a file and display the sorted lines.

## How to Use

Compile: Compile the project using a C++ compiler.

```sh
g++ MyShell.cpp functions.cpp -o myshell
```

Run: Execute the compiled binary:

```sh
./myshell
```
Interact: Use the supported commands in the shell prompt (>>).
