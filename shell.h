#ifndef SHEEL_H
#define SHEEL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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

void read_input(info_t *info);
void parse_input(info_t *info);
void find_path(info_t *info);
void execute_cmd(info_t *info);
void check_builtins(info_t *info);
void free_info(info_t *info);


#endif /*SHEEL_H*/
