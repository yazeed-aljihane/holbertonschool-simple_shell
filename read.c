#include "shell.h"


/**
 * read_input - Reads a line from standard input
 * @info: The parameter struct
 *
 * Return: The number of bytes read, or -1 on failure
 */
ssize_t read_input(info_t *info)
{
	ssize_t nread = 0;
	char *buffer = NULL;

	buffer = _getline();

	if (!buffer)
		return (-1);

	while (buffer[nread])
		nread++;

	if (nread > 0 && buffer[nread - 1] == '\n')
	{
		buffer[nread - 1] = '\0';
		nread--;
	}

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

	info->args = malloc(64 * sizeof(char *));
	if (info->args == NULL)
		return;
	for (i = 0; i < 64; i++)
	info->args[i] = NULL;

	i = 0;
	token = _strtok(info->line, " \t\n");
	while (token != NULL && i < 63)
	{
		info->args[i] = token;
		i++;
		token = _strtok(NULL, " \t\n");
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
	char *textpath = "PATH=", *path_copy, *token;
	char full_path[1024];

	if (info->args[0][0] == '/' || info->args[0][0] == '.')
	{
		if (access(info->args[0], X_OK) == 0)
			info->path = _strdup(info->args[0]);
		return (info->path ? 0 : -1);
	}
	while (info->env[i] && strncmp(info->env[i], textpath, 5) != 0)
		i++;
	if (!info->env[i])
		return (-1);
	path_copy = _strdup(info->env[i] + 5);
	if (!path_copy)
		return (-1);
	token = _strtok(path_copy, ":");
	while (token)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, info->args[0]);
		if (access(full_path, X_OK) == 0)
		{
			info->path = _strdup(full_path);
			free(path_copy);
			return (info->path ? 0 : -1);
		}
		token = _strtok(NULL, ":");
	}
	free(path_copy);
	return (-1);
}
