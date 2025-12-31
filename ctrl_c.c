#include "shell.h"





void signal_handler(int signal)
{
	(void)signal;
	write(1,"\n",1);
	if (isatty(STDIN_FILENO))
		write(1, "($) ", 4);
}
