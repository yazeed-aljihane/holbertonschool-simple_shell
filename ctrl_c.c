#include "shell.h"

/**
 * signal_handler - handles Ctrl+C (SIGINT) signal
 * @signal: the signal number
 *
 * Return: void
 */
void signal_handler(int signal)
{
	(void)signal;
	asm_puts("\n");
	if (isatty(STDIN_FILENO))
		asm_puts("($) ");
}
