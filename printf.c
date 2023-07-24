#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>




int _printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int count_char = 0;

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++; // Move past '%'
			switch (*format)
			{
				case 'c':
					{
						  char ch = va_arg(args, int);
						  count_char += write_ch_stdout(ch);
						  break;
					}
				case 's':
					{
						char *str = va_arg(args, char *);
						if (str != NULL)
						{
							int len = 0;
							while (str[len] != '\0')
								len++;
							if (write(1, str, len) == -1)
							{
								va_end(args);
								return -1; // Error occurred during write
							}
							count_char += len;
						}
						break;
					}
				case '%':
					{
						count_char += write_ch_stdout('%');
						break;
					}
				default:
					{
						// Ignore invalid specifier or just print the character
						count_char += write_ch_stdout(*format);
						break;
					}
			}
		}
		else
		{
			char ch = *format;
			if (write(1, &ch, 1) == -1)
			{
				va_end(args);
				return -1; // Error occurred during write
			}
			count_char++;
		}
		format++;
	}

	va_end(args);
	return count_char;
}

static int write_ch_stdout(char ch)
{
	if (write(1, &ch, 1) == -1)
		return -1; // Error occurred during write
	return 1;
}
