/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  syscalls.c
 * Created date			        :  3.10.2019
 * Brief Description of file            :  It serves as UART Interface 
                                           

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 ***************************************************************************/

#if 0
#include <stdint.h>
//#include <string.h>
#include <stdarg.h>
#include <limits.h>
//#include <sys/signal.h>
//#include "util.h"


size_t strnlen(const char *s, size_t n)
{
  const char *p = s;
  while (n-- && *p)
    p++;
  return p - s;
}

#undef putchar
int putchar(int ch)
{
  
  register char a0 asm("a0") = ch;
  asm volatile ("li t1, 0x11300" "\n\t"	//The base address of UART config registers
        "uart_status_simple: lb a1, 12(t1)" "\n\t"
        "andi a1,a1,0x2" "\n\t"
        "bnez a1, uart_status_simple" "\n\t"
				"sb a0, 4(t1)"  "\n\t"
				:
				:
				:"a0","t1","cc","memory");
  return 0;

}

void _init(int cid, int nc)
{
  // only single-threaded programs should ever get here.
  int ret = main(0, 0);

}


static inline void printnum(void (*putch)(int, void**), void **putdat,
                    unsigned long long num, unsigned base, int width, int padc)
{

  unsigned digs[sizeof(num)*CHAR_BIT];
  int pos = 0;

  while (1)
  {
    digs[pos++] = num % base;
    if (num < base)
      break;
    num /= base;
  }

  while (width-- > pos)
    putch(padc, putdat);

  while (pos-- > 0)
    putch(digs[pos] + (digs[pos] >= 10 ? 'a' - 10 : '0'), putdat);
}

static unsigned long long getuint(va_list *ap, int lflag)
{

  if (lflag >= 2)
    return va_arg(*ap, unsigned long long);
  else if (lflag)
    return va_arg(*ap, unsigned long);
  else
    return va_arg(*ap, unsigned int);
}
#if 0
static long long getint(va_list *ap, int lflag)
{
  if (lflag >= 2)
    return va_arg(*ap, long long);
  else if (lflag)
    return va_arg(*ap, long);
  else
    return va_arg(*ap, int);
}
#endif
static void vprintfmt(void (*putch)(int, void**), void **putdat, const char *fmt, va_list ap)
{

  register const char* p;
  const char* last_fmt;
  register int ch, err;
  unsigned long long num;
  int base, lflag, width, precision, altflag;
  char padc;

  while (1) {
    while ((ch = *(unsigned char *) fmt) != '%') {
      if (ch == '\0')
        return;
      fmt++;
      putch(ch, putdat);
    }
    fmt++;

    // Process a %-escape sequence
    last_fmt = fmt;
    padc = ' ';
    width = -1;
    precision = -1;
    lflag = 0;
    altflag = 0;
  reswitch:
    switch (ch = *(unsigned char *) fmt++) {
#if 0
    // flag to pad on the right
    case '-':
      padc = '-';
      goto reswitch;

    // flag to pad with 0's instead of spaces
    case '0':
      padc = '0';
      goto reswitch;

    // width field
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      for (precision = 0; ; ++fmt) {
        precision = precision * 10 + ch - '0';
        ch = *fmt;
        if (ch < '0' || ch > '9')
          break;
      }
      goto process_precision;

    case '*':
      precision = va_arg(ap, int);
      goto process_precision;

    case '.':
      if (width < 0)
        width = 0;
      goto reswitch;

    case '#':
      altflag = 1;
      goto reswitch;

    process_precision:
      if (width < 0)
        width = precision, precision = -1;
      goto reswitch;

    // long flag (doubled for long long)
    case 'l':
      lflag++;
      goto reswitch;
    // character
    case 'c':
      putch(va_arg(ap, int), putdat);
      break;

#endif
    // string
    case 's':
      if ((p = va_arg(ap, char *)) == NULL)
        p = "(null)";
      if (width > 0 && padc != '-')
        for (width -= strnlen(p, precision); width > 0; width--)
          putch(padc, putdat);
      for (; (ch = *p) != '\0' && (precision < 0 || --precision >= 0); width--) {
        putch(ch, putdat);
        p++;
      }
      for (; width > 0; width--)
        putch(' ', putdat);
      break;
#if 0
    // (signed) decimal
    case 'd':
      num = getint(&ap, lflag);
      if ((long long) num < 0) {
        putch('-', putdat);
        num = -(long long) num;
      }
      base = 10;
      goto signed_number;

    // unsigned decimal
    case 'u':
      base = 10;
      goto unsigned_number;
/*
    // (unsigned) octal
    case 'o':
      // should do something with padding so it's always 3 octits
      base = 8;
      goto unsigned_number;

    // pointer
    case 'p':
      static_assert(sizeof(long) == sizeof(void*));
      lflag = 1;
      putch('0', putdat);
      putch('x', putdat);
*/      /* fall through to 'x' */
#endif
    // (unsigned) hexadecimal
    case 'x':
      base = 16;
    unsigned_number:
      num = getuint(&ap, lflag);
    signed_number:
      printnum(putch, putdat, num, base, width, padc);
      break;

    // escaped '%' character
    case '%':
      putch(ch, putdat);
      break;

    // unrecognized escape sequence - just print it literally
    default:
      putch('%', putdat);
      fmt = last_fmt;
      break;
    }
  }
}

int printf(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  vprintfmt((void*)putchar, 0, fmt, ap);

  va_end(ap);
  return 0; // incorrect return value, but who cares, anyway?
}
#endif 

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

// #include "utils.h"
// #include "uart.h"

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

				// long flag (doubled for long long)
				case 'l':
					lflag++;
					backtothebeginning = 1;
					break;

					// character
				case 'c':
					putchar(va_arg(ap, int));
					break;

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
				case 'f':
					float_num =  va_arg(ap, double);

					//ftoa(float_num, float_arr, 6);

					for( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						if(i > 29) break;
					}
					break;

					// unsigned decimal
				case 'u':
					base = 10;

					if (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					else if (lflag)
						num = va_arg(ap, unsigned long);
					else
						num = va_arg(ap, unsigned int);

					itoa( num, base);

					break;

					// (unsigned) octal
				case 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					if (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					else if (lflag)
						num = va_arg(ap, unsigned long);
					else
						num = va_arg(ap, unsigned int);

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

