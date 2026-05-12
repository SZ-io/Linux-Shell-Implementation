# Linux Shell Implementation

A custom command-line interpreter written in C that replicates basic Bash functionality.

## Overview
This project handles the core lifecycle of a shell:
- Reading and parsing user input into commands and arguments.
- Creating child processes using fork().
- Executing binaries using execv and searching the system PATH.
- Synchronizing parent and child processes.

## Built-in Commands
- Support for absolute paths (e.g., /bin/ls).
- Custom 'leave' command to exit the shell.

## Compilation
gcc Shell.c -o matan_shell
./matan_shell
