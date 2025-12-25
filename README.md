# Simple Shell

## Description
Simple Shell is a basic UNIX command line interpreter written in C.
It replicates some core features of the UNIX shell (`/bin/sh`).

The shell displays a prompt, waits for user input, executes commands,
and handles errors. It works in both interactive and non-interactive modes.

## Features
- Displays a prompt and waits for user commands
- Executes commands using `execve`
- Handles command line arguments
- Handles end-of-file (Ctrl + D)
- Works in interactive and non-interactive modes
- Error handling for invalid commands

## Requirements
- Ubuntu 20.04 LTS
- gcc compiler
- Betty style

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
