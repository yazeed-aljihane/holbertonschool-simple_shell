#include "shell.h"

/**
 * check_builtins - checks and executes builtin commands
 * @info: parameter struct
 *
 * Return: 1 if a builtin command was executed, 0 otherwise
 */
int check_builtins(info_t *info)
{
	int i; /* Loop variable */

	if (strcmp(info->args[0], "exit") == 0)
	{
		if (shell_exit(info) == -1)
			return (1);
	}

	if (strcmp(info->args[0], "env") == 0)
	{
		/* Print all environment variables */
		for (i = 0; info->env[i]; i++)
		{
			write(STDOUT_FILENO, info->env[i], strlen(info->env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		info->status = 0; /* Success */
		return (1);
	}

	if (strcmp(info->args[0], "setenv") == 0)
	{
		set_env(info);
		return (1);

	}
	if (strcmp(info->args[0], "unsetenv") == 0)
	{
	unset_env(info);
	return (1);
	}

	return (0); /* Not a builtin */
}

/**
 * execute_cmd - executes an external command
 * @info: parameter struct
 *
 * Return: void
 */
void execute_cmd(info_t *info)
{
	pid_t child_pid; /* Process ID of the child */
	int status; /* Status variable to capture child's exit status */

	if (!info->path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				info->prog_name, info->line_count, info->args[0]);
		info->status = 127; /* Command not found */
		return;
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->args, info->env) == -1)
		{
			perror(info->prog_name);
			exit(2); /* Exit with status 2 on execve failure */
		}
	}

	else
	{
		wait(&status);

		/* Update the status based on child's exit status */
		if (WIFEXITED(status))
			info->status = WEXITSTATUS(status); /* Normal exit */
		else if (WIFSIGNALED(status))
			info->status = 128 + WTERMSIG(status); /* Terminated by signal */
	}
}






















