#include <stdio.h>

#define WSPT 8      // White space per tab

/* print the longest input line */
int main() {

    int c;
    int count = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < WSPT - (count % WSPT); ++i)
                putchar(' ');
            count = 0;
        }
        else {
            putchar(c);
            if (c == '\n') count = 0;
            else count++;
        }
    }

    return 0; 
}