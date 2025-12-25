#include "shell.h"




int shell_exit(info_t *info)
{
	int i, exit_num = 0;
	if (info->args[1] != NULL)
	{
		if (info->args[2] != NULL)
		{
			fprintf(stderr,"%s: %d: %s: exit: too many arguments\n", info->prog_name, info->line_count, info->args[1]);
			info->status = 2;
			return (-1);
		}
		for (i = 0; info->args[1][i] != '\0'; i++)
		{
			if (info->args[1][i] < '0' || info->args[1][i] > '9')
			{
				fprintf(stderr,"%s: %d: %s: exit: numeric argument required\n", info->prog_name, info->line_count, info->args[1]);
				info->status = 2;
				return (-1);
			}
		}
		exit_num = _atoi(info->args[1]);
		free_info(info);
		exit(exit_num);
	}
	free_info(info);
	exit(info->status);
}
