#include "shell.h"
/**
 * _atoi - turn string ti integr
 * @s: string pointer
 * Return: the number in string
 */
int _atoi(char *s)
{
int i;
int sign = 1;
int total = 0;
for (i = 0; s[i] != '\0'; i++)
{



while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
{
if (s[i] == '-')
sign *= -1;
i++;
}




if (s[i] >= '0' && s[i] <= '9')
{

if (total > (2147483647 - (s[i] - '0')) / 10)
{
int result = (sign == 1) ? 2147483647 : -2147483648;
return (result);
}
total = total * 10 + (s[i] - '0');
if (s[i + 1] < '0' || s[i + 1] > '9')
{
break;
}
}
else
{
continue;
}
}
total = total *sign;
return (total);
}
