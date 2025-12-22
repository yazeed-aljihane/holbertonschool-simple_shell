#include "shell.h"

/**
 * main - Simple Shell 0.1 (gnu89 compatible)
 * @argc: Argument count
 * @argv: Argument vector
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *buffer = NULL, *token, *args[2];
	size_t len = 0;
	ssize_t nread;
	int line_count = 0, pid;

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		nread = getline(&buffer, &len, stdin);
		if (nread == -1)
			break;
		if (buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';
		token = strtok(buffer, " \t\r\n\a");
		if (token == NULL)
			continue;
		line_count++;
		if (access(token, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				args[0] = token;
				args[1] = NULL;
				if (execve(token, args, environ) == -1)
					exit(EXIT_FAILURE);
			}
			wait(NULL);
		}
		else
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_count, token);
	}
	free(buffer);
	return (0);
}
