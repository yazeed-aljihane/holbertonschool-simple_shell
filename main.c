#include "shell.h"

/**
 * main - Simple Shell 0.1 (gnu89 compatible)
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	info_t info = {NULL, NULL, NULL, 0, NULL, 0, NULL};
	ssize_t nread;

	populate_env_list(&info, env);
	info.prog_name = av[0];
	(void)ac;
	signal(SIGINT, signal_handler);
	while (1)
	{
		info.line_count++;
		if (isatty(STDIN_FILENO))
			asm_puts("$ ");
		nread = read_input(&info);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				asm_puts("\n");
			break;
		}
		if (info.line && *info.line)
		{
			parse_input(&info);
			if (info.args && info.args[0])
			{
				if (!check_builtins(&info))
				{
					find_path(&info);
					execute_cmd(&info);
				}
			}
		}
		free_info(&info);
	}
	free_env(&info);
	return (info.status);
}
