#ifndef SHEEL_H
#define SHEEL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
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

ssize_t read_input(info_t *info);
void parse_input(info_t *info);
int find_path(info_t *info);
void execute_cmd(info_t *info);
int check_builtins(info_t *info);
void free_info(info_t *info);
int shell_exit(info_t *info);
int _atoi(char *s);
void signal_handler(int signal);
int set_env(info_t *info);
int unset_env(info_t *info);
char *_strdup(const char *str);
void populate_env_list(info_t *info, char **env);
void free_env(info_t *info);
#endif /*SHEEL_H*/
