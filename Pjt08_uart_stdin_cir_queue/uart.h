#include <stdio.h>
FILE Mystdout;
char uart_busy;
void uart_init();
int uart_putchar(char ch, FILE *stream);
int uart_getchar(FILE *stream);


