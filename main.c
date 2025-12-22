#include "shell.h"

int main(int argc, char **argv)
{
	char *buffer = NULL, *storge[100];
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
		if (buffer[0] == '\0')
			continue;
		line_count++;
		storge[0] = buffer;
		storge[1] = NULL;
		if (access(buffer, X_OK) != -1)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("Error:");
				return (-1);
			}
			if (pid >= 1)
				wait(NULL);
			if (pid == 0)
			{
				if (execve(buffer, storge, environ) == -1)
				{
					fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_count, buffer);
					exit(EXIT_FAILURE);
				}
			}
		}
		else
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
	}
	free(buffer);
	return (0);
}
