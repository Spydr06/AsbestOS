#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}
 
int vprintf(const char* restrict format, va_list parameters) {
	int written = 0;
	char strbuf[20];
 
	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;
 
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format++;
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd' || *format == 'i') {
			format++;
			int i = (int) va_arg(parameters, int);
			unsigned int len = itoa(i, strbuf, 10);
			if(maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
			}
			if(!print(strbuf, len))
				return -1;
			written += len;
		} else if (*format == 'x') {
			format++;
			unsigned int i = (unsigned int) va_arg(parameters, int);
			unsigned int len = utoa(i, strbuf, 16);
			if(maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
			}
			if(!print(strbuf, len))
				return -1;
			written += len;
		} else if (*format == 'u') {
			format++;
			unsigned int i = (unsigned int) va_arg(parameters, int);
			unsigned int len = utoa(i, strbuf, 10);
			if(maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
			}
			if(!print(strbuf, len))
				return -1;
			written += len;
		} else if (*format == 'o') {
			format++;
			unsigned int i = (unsigned int) va_arg(parameters, int);
			unsigned int len = utoa(i, strbuf, 8);
			if(maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
			}
			if(!print(strbuf, len))
				return -1;
			written += len;
		} else if (*format == 'n') {
			format++;
			signed int* p = (signed int*) va_arg(parameters, signed int*);
			*p = written;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}
	return written;
}
