#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...) {
	va_list args;
	va_start(args, format);

	int char_count = 0;
	char ch;
	char *str;
	int len;

	while (*format != '\0') {
		if (*format == '%') {
			format++; // Move past '%'
			switch (*format) {
				case 'c':
					ch = va_arg(args, int);
					if (write(1, &ch, 1) == -1) {
						va_end(args);
						return -1; // Error occurred during write
					}
					char_count++;
					break;
				case 's':
					str = va_arg(args, char *);
					if (str != NULL) {
						len = 0;
						while (str[len] != '\0')
							len++;
						if (write(1, str, len) == -1) {
							va_end(args);
							return -1; // Error occurred during write
						}
						char_count += len;
					}
					break;
				case '%':
					ch = '%';
					if (write(1, &ch, 1) == -1) {
						va_end(args);
						return -1; // Error occurred during write
					}
					char_count++;
					break;
				default:
					// Ignore invalid specifier or just print the character
					ch = *format;
					if (write(1, &ch, 1) == -1) {
						va_end(args);
						return -1; // Error occurred during write
					}
					char_count++;
					break;
			}
		} else {
			ch = *format;
			if (write(1, &ch, 1) == -1) {
				va_end(args);
				return -1; // Error occurred during write
			}
			char_count++;
		}
		format++;
	}

	va_end(args);
	return char_count;
}

int main() {
	int chars_printed = _printf("Hello, %s! The character is: %c%%\n", "world", 'A');
	printf("Number of characters printed: %d\n", chars_printed);
	return 0;
}

