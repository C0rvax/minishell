# Minishell - A Custom UNIX Shell

![42 Project](https://img.shields.io/badge/42%20Project-Minishell-blue)![Language](https://img.shields.io/badge/Language-C-informational)![License](https://img.shields.io/badge/License-MIT-green)

Minishell is a custom implementation of a UNIX command-line interpreter, written entirely in C. This project is a core part of the curriculum at **École 42**, designed to provide a deep understanding of process management, file descriptor manipulation, and the inner workings of a shell.

Our shell faithfully replicates a subset of `bash`'s functionality, including command execution, pipes, redirections, environment variable handling, and built-in commands.

## ✨ Key Features

*   **Interactive Prompt**: Displays a dynamic prompt with user and current path information, similar to `bash`.
*   **Command History**: Navigable command history using arrow keys, powered by the `readline` library.
*   **Robust Parsing**:
    *   Handles single (`'`) and double (`"`) quotes.
    *   Expands environment variables (e.g., `$PATH`, `$USER`).
    *   Supports special variable `$?` to get the exit code of the last command.
*   **Execution Engine**:
    *   Executes system binaries and local executables using the `PATH` environment variable.
    *   Manages multiple commands linked by **pipes (`|`)**.
*   **I/O Redirections**:
    *   `>`: Redirect standard output, overwriting the file.
    *   `>>`: Redirect standard output, appending to the file.
    *   `<`: Redirect standard input from a file.
    *   `<<`: Heredoc for multi-line input.
*   **Signal Handling**:
    *   `Ctrl-C` (SIGINT): Interrupts the current process or displays a new prompt.
    *   `Ctrl-D` (EOF): Exits the shell.
    *   `Ctrl-\` (SIGQUIT): Ignored, just like in `bash`.
*   **Built-in Commands**: A set of essential shell commands implemented internally.
*   **Error Management**: Provides clear error messages for syntax errors, command not found, permission denied, and more.

## ⚙️ How It Works

The shell processes user input through a two-stage pipeline: **Parsing** and **Execution**.

### 1. Parsing
The raw command string entered by the user is processed in several steps to build an executable command structure:

1.  **Lexer (Tokenization)**: The input string is broken down into a list of tokens, such as `COMMAND`, `ARGUMENT`, `PIPE`, `REDIRECT_IN`, `HEREDOC`, etc.
2.  **Variable Expansion**: Any occurrences of `$VAR` are replaced with their corresponding values from the environment. Special variables like `$?` are also handled.
3.  **Quote Removal**: Quotes are interpreted to group arguments and are then removed from the final command tokens.
4.  **Syntax Validation**: The token list is checked for syntax errors (e.g., unexpected pipes `||`, invalid redirection sequences `>> >`).
5.  **Command Table Creation**: The tokens are organized into a structured list of commands, where each command has its arguments and a list of associated redirections.

### 2. Execution
Once the command table is built, the execution engine takes over:

*   **Single Command**: For a single command, the shell `forks` a child process. Redirections are set up using `dup2()`, and the command is executed with `execve()`.
*   **Piped Commands**: For commands linked by pipes (`|`), the shell creates a child process for each command. The standard output of one process is connected to the standard input of the next using `pipe()` and `dup2()`.
*   **Built-ins**: If the command is a built-in (like `cd` or `exit`), it is handled differently. Some built-ins (`cd`, `export`, `unset`, `exit`) are executed in the main process to affect the shell's state, while others can be executed in a child process if part of a pipe.

## 🛠️ Implemented Built-in Commands

| Command | Description |
| :--- | :--- |
| `echo` | Prints arguments to standard output. Supports the `-n` flag. |
| `cd` | Changes the current working directory. |
| `pwd` | Prints the current working directory. |
| `export` | Sets or displays environment variables. |
| `unset` | Removes environment variables. |
| `env` | Prints the environment variables. |
| `exit` | Exits the minishell with a specified status code. |

## 🚀 How to Use

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/C0rvax/minishell.git
    cd minishell
    ```

2.  **Compile the project:**
    The Makefile compiles the shell and its dependencies (`libft` and `printf`).
    ```bash
    make
    ```

3.  **Run the shell:**
    ```bash
    ./minishell
    ```

## 🎬 Demo

*(A short GIF demonstrating the shell's features can be added here.)*

**Example Session:**
```bash
minishell$ echo "Hello World!" > greeting.txt
minishell$ cat < greeting.txt | wc -w
1
minishell$ ls -l | grep ".txt"
-rw-r--r-- 1 user group 13 Sep 15 17:30 greeting.txt
minishell$ export MESSAGE="Minishell is working"
minishell$ echo $MESSAGE
Minishell is working
minishell$ exit
```

## 💻 Technologies Used

*   **Language:** C
*   **Compiler:** GCC
*   **Build System:** Make
*   **External Libraries:** `readline` for interactive input and history.
*   **Custom Libraries:** A custom `libft` and `ft_printf` implementation as per 42's requirements.

## 👥 Authors

This project was developed by:

*   **C. Truchot** ([C0rvax](https://github.com/C0rvax))
*   **A. Duvilla** ([aduvilla](https://github.com/aduvilla-s))
