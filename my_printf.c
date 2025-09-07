/* no chatGPT here, but Google search for sure */
/* int my_printf(char * restrict format, ...); */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

/*	from man 3 stdarg	*/
void foo(char *fmt, ...)
{
        va_list ap, ap2;
        int d;
        char c, *s;

        va_start(ap, fmt);
        va_copy(ap2, ap);
        while (*fmt)
                switch(*fmt++) {
                case 's':                       /* string */
                        s = va_arg(ap, char *);
                        printf("string %s\n", s);
                        break;
                case 'd':                       /* int */
                        d = va_arg(ap, int);
                        printf("int %d\n", d);
                        break;
                case 'c':                       /* char */
                        /* Note: char is promoted to int. */
                        c = va_arg(ap, int);
                        printf("char %c\n", c);
                        break;
                }
        va_end(ap);
        /* use ap2 to iterate over the arguments again */
        va_end(ap2);
}
/* https://stackoverflow.com/questions/62699018/how-to-use-write-or-fwrite-for-writing-data-to-terminal-stdout */
/* ssize_t write(int fd, const void *buf, size_t count); */

int main(int argc, char **argv) {
	char *fmt;
	const char *message = "Hello, World!\n";

	fmt = "%d";
	foo(fmt, 5);

/* 	from bing search on "c write to stdout"	*/
	write(1, message, 14); // 1 is the file descriptor for stdout
	return 0;
}
