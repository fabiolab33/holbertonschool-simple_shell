# Simple Shell

## Description
Simple Shell is a basic UNIX command line interpreter written in C as part of the Holberton School curriculum.

The shell displays a prompt, waits for the user to enter a command, and executes it using system calls. It supports both interactive and non-interactive modes.

## Features
- Displays a prompt and waits for user input
- Executes commands using absolute paths and the PATH environment variable
- Handles commands with arguments
- Built-in commands:
  - `exit`: exits the shell
  - `env`: prints the current environment
- Handles end-of-file condition (Ctrl + D)
- Error handling for invalid commands
- No memory leaks

## Files
| File                 | Description                             |
| -------------------- | --------------------------------------- |
| `main.c`             | Entry point of the shell                |
| `shell.c`            | Main loop and built-in command handling |
| `execute_command.c`  | Command execution and PATH resolution   |
| `shell.h`            | Header file with function prototypes    |
| `man_1_simple_shell` | Manual page for the shell               |
| `AUTHORS`            | List of project contributors            |

### Usage
The shell works correctly in both interactive and non-interactive modes:

Interactive Mode

`$ ./hsh`
 
 `($) ls -l`
 
 `($) env`
 
 `($) exit`

 `($) /bin/ls`

Non-Interactive Mode

`$ echo "ls" | ./hsh`

`$ cat file_with_commands | ./hsh`
 
`$ echo "/bin/ls" | ./hsh`

### Error Handling
Errors are printed exactly like `/bin/sh`, except that the program name matches `argv[0]`.

### Built-in Commands
| Command                 | Description                             |
| -------------------- | --------------------------------------- |
| `exit`             | Exits the shell and returns the last command status                |
| `env`            | Prints all environment variables |

### Manual Page
To view the manual page:

`man ./man_1_simple_shell`

### Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
