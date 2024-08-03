# 42 Pipex Project

## Overview

The 42 Pipex project aims to replicate the functionality of the Unix pipe (`|`), which is a powerful feature that allows for the chaining of commands. This project will help you understand the intricacies of process creation, inter-process communication, and file descriptor manipulation by creating a program that mimics the following shell command behavior:

```sh
< file1 cmd1 | cmd2 > file2
```

## Objectives

- Learn how to create and manage processes using `fork`.
- Understand and implement inter-process communication using pipes.
- Manipulate file descriptors to redirect input and output.
- Gain a deeper understanding of Unix-like operating systems' internals.

## Features

- Execute two commands in sequence, where the output of the first command is used as the input for the second command.
- Redirect input from a file (`file1`) and output to another file (`file2`).

## Requirements

- Your program must follow the structure and behavior of the provided shell command.
- You cannot use `system` calls; you must handle process creation and communication manually.
- Proper error handling for file operations and process creation must be implemented.

## Usage

### Compilation

To compile the project, run the following command:

```sh
make
```

This will generate an executable file named `pipex`.

### Execution

To run the program, use the following syntax:

```sh
./pipex file1 cmd1 cmd2 file2
```

- `file1`: The input file.
- `cmd1`: The first command to execute.
- `cmd2`: The second command to execute.
- `file2`: The output file.

### Example

```sh
./pipex infile "ls -l" "grep pipex" outfile
```

This command will take the content of `infile`, pass it to `ls -l`, then pipe its output to `grep pipex`, and finally save the result in `outfile`.

## File Structure

- `pipex.c`: Main file containing the implementation of the program.
- `Makefile`: Script to compile the program.
- `README.md`: This file.
- Additional helper files and headers as needed.

## Error Handling

- The program should handle errors gracefully, providing appropriate error messages for issues such as file not found, command not found, and failed system calls.
- Make sure to free allocated memory and close file descriptors to prevent leaks.

## Conclusion

The 42 Pipex project is an excellent opportunity to deepen your understanding of process control and inter-process communication in Unix-like operating systems. By completing this project, you'll gain valuable skills that are fundamental for systems programming.