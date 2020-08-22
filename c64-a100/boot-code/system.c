/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  system.c
 * Created date			        :  21.8.2020
 * Brief Description of file            :   Use for trap and UART display

 Copyright (C) 2020 IIT Madras. All rights reserved.

//check LICENSE.iitm

 ***************************************************************************/


#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#undef putchar
int putchar(int ch)
{
  
  register char a0 asm("a0") = ch;
  asm volatile ("li t1, 0x11300" "\n\t"	//The base address of UART config registers
        "1: lb a1, 12(t1)" "\n\t"
        "andi a1,a1,0x2" "\n\t"
        "bnez a1, 1b" "\n\t"
				"sb a0, 4(t1)"  "\n\t"
				:
				:
				:"a0","t1","cc","memory");
  return 0;

}

/** @fn  itoa
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned 
 */

static inline void itoa (unsigned long long int number, unsigned base)
{
	unsigned int size = 0;
	int i = 0;
	unsigned int intermediate = 0;
	unsigned int digits[sizeof(number)*8];

	while (1) {
		digits[i] = number % base;

		if (number < base)
			break;

		number /= base;
		i++;
	}
	i++;

	while (i-- > 0)
	{
		if (digits[i] >= 10)
			intermediate = 'a' - 10;
		else
			intermediate = '0';

		putchar(digits[i] + intermediate);
	}
}

/** @fn _printf_
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char
 */
void _printf_(const char *fmt, va_list ap)
{
	register const char* p;
	const char* last_fmt;
	register int ch;
	unsigned long long num;
	int base, lflag, i;
	float float_num = 0;
	char float_arr[30] = {'\0'};
	int backtothebeginning;

	for (;;) {
		for (;(ch = *(unsigned char *) fmt) != '%'; fmt++) {
			if (ch == '\0')
				return;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0; 

		backtothebeginning = 0;
		for (;;) {

			switch (ch = *(unsigned char *) fmt++) {

				// string
				case 's':
					if ((p = va_arg(ap, char *)) == NULL)
						p = "(null)";
					for (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					break;

					// (signed) decimal
				case 'd':
					base = 10;

					if (lflag >= 2)
						num = va_arg(ap, long long);
					else if (lflag ==1)
						num = va_arg(ap, long);
					else
						num = va_arg(ap, int);

					if ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					break;

				case 'x':
					base = 16;

					if (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					else if (lflag)
						num = va_arg(ap, unsigned long);
					else
						num = va_arg(ap, unsigned int);

					itoa( num, base);

					break;

					// escaped '%' character
				case '%':
					putchar(ch);
					break;

					// unrecognized escape sequence - just print it literally
				default:
					putchar('%');
					fmt = last_fmt;
					break;
			}

			if (backtothebeginning)
			{
				backtothebeginning = 0;
				continue;
			}
			else
				break;
		}
	}
}

/** @fn printf
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
int printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	return 0; // incorrect return value, but who cares, anyway?
}

void handle_trap(uintptr_t mcause, uintptr_t epc)
{
	printf("Trap happened ! \n mcause = %x, epc = %x", mcause, epc);
	while(1);
}


