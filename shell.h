#ifndef SHEEL_H
#define SHEEL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * struct shell_info - Structure to hold shell information
 * @line: The input line from the user
 * @args: The parsed arguments from the input line
 * @path: The current working directory path
 * @status: The exit status of the last command
 * @prog_name: The name of the shell program
 * @line_count: The line number in the input file
 * @env: The environment variables
 */
typedef struct shell_info
{
	char *line;
	char **args;
	char *path;
	int status;
	char *prog_name;
	int line_count;
	char **env;
} info_t;

/* Assembly functions */
long int asm_puts(char *str);
long int puts_linux(char *str);
long int puts_mac(char *str);

/* Function prototypes */
ssize_t read_input(info_t *info);
void parse_input(info_t *info);
int find_path(info_t *info);
void execute_cmd(info_t *info);
int check_builtins(info_t *info);
void free_info(info_t *info);
int shell_exit(info_t *info);
void signal_handler(int signal);
int set_env(info_t *info);
int unset_env(info_t *info);
void populate_env_list(info_t *info, char **env);
void free_env(info_t *info);
int is_delim(char c, char *delim);

/* costim functions */
char *_strdup(const char *str);
char *_getline(void);
int _atoi(char *s);
char *_strtok(char *str, char *delim);
int _strcmp(const char *s1, const char *s2);
void *_realloc(void *ptr, size_t old_size, size_t new_size);




#endif /*SHEEL_H*/
