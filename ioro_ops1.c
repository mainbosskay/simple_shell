#include "main.h"

/**
 * err_msg - Printing error message
 * @k: info structure
 * @errstr: error string
 * Return: either 0 or converted number or -1 if error
 */

void err_msg(psinfo_t *k, char *errstr)
{
	exec_puts(k->filename);
	exec_puts(": ");
	dec_print(k->ln_count, STDERR_FILENO);
	exec_puts(": ");
	exec_puts(k->argv[0]);
	exec_puts(": ");
	exec_puts(errstr);
}

/**
 * dec_print - Printing a decimal number
 * @i: input
 * @fdes: file descriptor
 * Return: number of printed character
 */

int dec_print(int i, int fdes)
{
	int (*__putchar)(char) = _putchar;
	int k;
	int sum;
	unsigned int abs_val;
	unsigned int present;

	sum = 0;
	if (fdes == STDERR_FILENO)
		__putchar = exec_putchar;
	if (i < 0)
	{
		abs_val = -i;
		__putchar('-');
		sum++;
	}
	else
		abs_val = i;
	present = abs_val;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (abs_val / k)
		{
			__putchar('0' + present / k);
			sum++;
		}
		present %= k;
	}
	__putchar('0' + present);
	sum++;
	return (sum);
}

/**
 * itoa_int - Cloning of itoa
 * @number: number
 * @base: base
 * @flgs: flags
 * Return: it is a string
 */

char *itoa_int(long int number, int base, int flgs)
{
	static char *arr;
	static char buffer[50];
	char symbol;
	char *pointer;
	unsigned long a;

	symbol = 0;
	a = number;
	if (!(flgs & UNSIGNED_CONVERT) && number < 0)
	{
		a = -number;
		symbol = '-';
	}
	arr = flgs & LOWERCASE_CONVERT ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';
	do	{
		*--pointer = arr[a % base];
		a /= base;
	} while (a != 0);

	if (symbol)
		*--pointer = symbol;
	return (pointer);
}

/**
 * del_comms - Replacing '#' with '\0'
 * @buff: string to modify
 * Return: it is 0
 */

void del_comms(char *buff)
{
	int k;

	for (k = 0 ; buff[k] != '\0' ; k++)
		if (buff[k] == '#' && (!k || buff[k - 1] == ' '))
		{
			buff[k] = '\0';
			break;
		}
}
