#include "shell.h"


/**
 * read_input - Reads a line from standard input
 * @info: The parameter struct
 *
 * Return: The number of bytes read, or -1 on failure
 */
ssize_t read_input(info_t *info)
{
	ssize_t nread;
	char *buffer = NULL;
	size_t  len = 0;

	nread = getline(&buffer, &len, stdin);
	if (nread == -1)
	{
		free(buffer);
		return (-1);
	}
	if (buffer[nread - 1] == '\n')
		buffer[nread - 1] = '\0';
	info->line = buffer;
	return (nread);
}
/**
 * parse_input - parses the input string into arguments
 * @info: the parameter struct
 *
 * Return: void
 */
void parse_input(info_t *info)
{
	int i = 0;
	char *token;

	info->args = malloc(sizeof(char *) * 64);
	if (info->args == NULL)
		return;
	token = strtok(info->line, " \t\n");
	while (token != NULL && i < 63)
	{
		info->args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	info->args[i] = NULL;
}

/**
 * find_path - finds the command in the PATH environment variable
 * @info: the parameter struct
 *
 * Return: 0 on success, -1 on error
 */
int find_path(info_t *info)
{
	int i = 0;
	char *textpath = "PATH=", *tmp_buffer = NULL, *path_copy, *token;
	char full_path[1024];

	if (info->args[0][0] == '/' || info->args[0][0] == '.')
	{
		if (access(info->args[0], X_OK) == 0)
		{
			info->path = strdup(info->args[0]);
			if (info->path == NULL)
				return (-1);
			return (0);
		}
		return (-1);
	}
	while (info->env[i])
	{
		if (strncmp(info->env[i], textpath, 5) == 0)
		{
			tmp_buffer = info->env[i];
			break;
		}
		i++;
	}
	if (tmp_buffer == NULL)
		return (-1);
	path_copy = strdup(tmp_buffer + 5);
	if (path_copy == NULL)
		return (-1);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, info->args[0]);
		if (access(full_path, X_OK) == 0)
		{
			info->path = strdup(full_path);
			if (info->path == NULL)
			{
				free(path_copy);
				return (-1);
			}
			free(path_copy);
			return (0);
		}
	token = strtok(NULL, ":");
	}
	free(path_copy);
	return (-1);
}
