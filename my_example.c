/* no chatGPT here, but Google search for sure */
/* int my_printf(char * restrict format, ...); */
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

// https://markaicode.com/how-to-append-a-character-to-string-in-c-5-proven-methods/
char* append_char_dynamic(char *str, char ch) {
    size_t len = strlen(str);
    char *new_str = realloc(str, len + 2);  // +1 for char, +1 for null

    if (new_str == NULL) {
        return str;  // Return original if realloc fails
    }

    new_str[len] = ch;
    new_str[len + 1] = '\0';

    return new_str;
}

char hex_table[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

/*	from man 3 stdarg	*/
void food(char *fmt, ...)
{
        va_list ap, ap2;
        int d, n;
	void *p;
	size_t t;
	char *my_string, c, *s;
	/* no way in C to dynamically determine type. */

        va_start(ap, fmt);
        va_copy(ap2, ap);
        while (*fmt) {
		if(*fmt != '%') {
			write(1, fmt, 1);
		} else {
 		    fmt++;
//		    printf("%c", *fmt);
            	    switch(*fmt) {
	               	case 's':  
               		        s = va_arg(ap, char *);
				for(int i=0; i<strlen(s); i++) write(1, s+i, 1);
                       		// printf("%s", s);
	                        break;
			case 'd': 
                        	d = va_arg(ap, int);
                        	// printf("%d", d);
				// integer convert to ascii
				if(d<0) { write(1, &"-", 1); d = -d; }
				n=0; my_string = malloc(1);
				do {
					int i = d%10;
					i+='0';
					d/=10;
					append_char_dynamic(my_string, i);
					my_string[n] = i;
					n++;
				} while(d != 0);
				for(int i = n; i>0; i--) {
					write(1, my_string+i-1, 1);
				}
				free(my_string);
                        	break;
			case 'c':
                       		c = va_arg(ap, int);
				write(1, &c, 1);
               	 	        break;
			case 'p':
        	                // printf("%p", p);
				// uint convert to hexadecimal
                       		p = va_arg(ap, void *);
  				unsigned long int converted = (unsigned long int) p;
// printf("\n%lu %lu %lu\n", converted, converted/16, converted%16);

				n=0; my_string = malloc(1);
				do {
					int i = converted%16;
// printf("%d %c\n", i, hex_table[i]);
// printf("%lu %lu\n", converted, converted/16);
					converted/=16;
					append_char_dynamic(my_string, hex_table[i]);
// printf("%s\n", my_string);
					n++;
				} while(converted != 0);
				// write(1, my_string, n);
				for(int i = n; i>0; i--) {
					write(1, my_string+i-1, 1);
				}
				free(my_string);
                        	break;
			default:
				write(1, "error", 5);
		   }
	      }
	      fmt++;
	}
	write(1, "\n", 1);
        va_end(ap);
        va_end(ap2);
}

/* https://stackoverflow.com/questions/62699018/how-to-use-write-or-fwrite-for-writing-data-to-terminal-stdout */
/* ssize_t write(int fd, const void *buf, size_t count); */

int main(int argc, char **argv) {
	char *fmt;
	int i, len, lenstr, d, c;
	void food(char * an_arg, ...);
	void *p;
	size_t t = 5;
	char *s;

	d=100;
	c='x';
	s = "abcdef";
	p = malloc(t);
	fmt = "the integer: %d, the character: %c, the string: %s, the pointer: %p";
	food(fmt, d, c, s, p);
	return 0;

/*
 	from bing search on "c write to stdout"
	return 0;
	write(1, message, 14); // 1 is the file descriptor for stdout
*/

	return 0;
}
