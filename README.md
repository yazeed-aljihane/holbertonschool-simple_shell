# C - Simple Shell

This project is a custom implementation of a UNIX command interpreter (Shell), written in C. It replicates the core functionality of the `sh` shell, including process creation, execution, environment management, and built-in commands.

A unique feature of this implementation is the integration of **Assembly Language** for critical I/O operations (`puts`), optimizing output performance on Linux (x86_64) and macOS (ARM64).

## 📂 Project Architecture

The shell is designed around a central state structure (`info_t`) that maintains the runtime context. The architecture is modular, separating concerns into:
- **Core Loop:** Read-Eval-Print Loop (REPL).
- **Parser:** Custom tokenization (`_strtok`) and parsing logic.
- **Executor:** Process forking and `execve` handling.
- **Memory Management:** Custom reallocation and garbage collection.
- **Built-ins:** Internal command implementations.

## 🛠 Requirements

- **OS:** Ubuntu 20.04 LTS
- **Compiler:** gcc
- **Flags:** `-Wall -Werror -Wextra -pedantic -std=gnu89`
- **Style:** Betty Style compliant

## ⚙️ Compilation

To compile the shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## 🚀 Usage

The shell works in two modes: **Interactive** and **Non-Interactive**.

### 1. Interactive Mode
Run the shell and type commands manually:
```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$
```

### 2. Non-Interactive Mode
Pipe commands into the shell:
```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$
```

## ⚡ Features & Built-ins

### Supported Built-in Commands
| Command | Description |
| :--- | :--- |
| `env` | Prints the current environment variables. |
| `setenv` | Initialize a new environment variable, or modify an existing one. |
| `unsetenv` | Remove an environment variable. |
| `exit` | Exits the shell with a given status code. |

### Low-Level Optimizations
- **Assembly Integration (`asm_puts.c`):**
  Direct system calls are used via inline assembly for string output. This bypasses the standard library overhead for `write`, providing a slight performance edge in high-throughput scenarios.
  - Supports **x86_64 (Linux)** using `syscall`.
  - Supports **ARM64 (macOS/Apple Silicon)** using `svc`.

- **Custom Buffer Management (`_getline.c`):**
  Implements a static buffer to minimize `read()` system calls, handling line breaking and memory reallocation manually to ensure memory safety.

- **Custom Tokenizer (`_strtok.c`):**
  A robust, reentrant implementation of string tokenization that handles delimiters without corrupting the original static state in an unsafe manner.

## 📂 File Structure

| File | Description |
| :--- | :--- |
| `main.c` | Entry point. Initializes the `info_t` struct and runs the loop. |
| `shell.h` | Header file containing prototypes, structs, and macros. |
| `execute.c` | Handles `fork`, `execve`, and `wait` logic. |
| `env.c` | Helper functions for environment variable manipulation. |
| `set_env.c` | Logic for `setenv` and `unsetenv` built-ins. |
| `_getline.c` | Custom implementation of `getline` with buffering. |
| `_strtok.c` | Custom string tokenizer. |
| `asm_puts.c` | Assembly optimized string output. |
| `100-atoi.c` | String to integer conversion logic. |
| `memory.c` | Memory reallocation and freeing functions. |
| `read.c` | Handles input reading, argument parsing, and command path resolution. |
| `exit.c` | Implements the exit built-in command with status code validation. |
| `ctrl_c.c` | Signal handler for `SIGINT` (Ctrl+C) to prevent abrupt termination. |

## 🧪 Testing

The shell mimics the standard `/bin/sh` output, including error messages.

**Example Error Handling:**
```bash
$ ./hsh
($) qwerty
./hsh: 1: qwerty: not found
```

## 👥 Authors

- **Mohammed Saeed Al-Dosari**
- **Yazeed Mostafa Al-Johani**