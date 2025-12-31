#include "shell.h"

/**
 * asm_puts - Assembly implementation of puts
 * @str: the string to write
 *
 * Return: number of bytes written
 */
long int asm_puts(char *str)
{
	#if defined(__linux__) && defined(__x86_64__)
		return (puts_linux(str));
	#elif defined(__APPLE__) && defined(__aarch64__)
		return (puts_mac(str));
	#else
		int i;

		for (i = 0; str[i]; i++)
			;
		return (write(STDOUT_FILENO, str, i));
	#endif
}

#if defined(__linux__) && defined(__x86_64__)
/**
 * puts_linux - Linux x86_64 assembly implementation of puts
 * @str: the string to write
 *
 * Return: number of bytes written
 */
long int puts_linux(char *str)
{
	long int ret;

	__asm__ __volatile__ (
		".intel_syntax noprefix\n"	/* switch to Intel syntax */
		"mov rax, 1\n"				/* syscall: write */
		"mov rdi, rax\n"			/* file descriptor: stdout */
		"mov rsi, %1\n"				/* pointer to string */
		"xor rdx, rdx\n"			/* clear rdx for length calculation */
	"1:\n"
		"cmp byte ptr [rsi + rdx], 0\n"
		"je 2f\n"
		"inc rdx\n"
		"jmp 1b\n"
	"2:\n"
		"syscall\n"
		"mov %0, rax\n"				/* return value: number of bytes written */
		".att_syntax prefix\n"		/* switch back to AT&T syntax */
		: "=r"(ret)
		: "r"(str)
		: "rax", "rdi", "rsi", "rdx", "rcx", "r11"
	);
	return (ret);
}
#elif defined(__APPLE__) && defined(__aarch64__)
/**
 * puts_mac - macOS aarch64 assembly implementation of puts
 * @str: the string to write
 *
 * Return: number of bytes written
 */
long int puts_mac(char *str)
{
	long int ret;

	__asm__ volatile (
		"mov x1, %0\n"
		"mov x2, xzr\n"
	"1:\n"
		"ldrb w3, [x1, x2]\n"
		"cbz  w3, 2f\n"
		"add  x2, x2, #1\n"
		"b    1b\n"
	"2:\n"
		"mov  w0, #1\n"
		"movz  w16, #0x0004\n"
		"movk w16, #0x0200, lsl #16\n"
		"svc  #0\n"
		: "=r"(ret)
		: "r"(str)
		: "x0", "x1", "x2", "x3", "x16"
	);
	return (ret);
}
#endif
