#include <stdio.h>

#define TAB 8

int main() {

    int c; // Variable to hold input
    int i = 0; // Index of input
    int _i; // temp for i

    while ((c = getchar()) != EOF) 
    {
        // If char is tab, replace with spaces to tabstop
        if (c == '\t')
        {
            _i = i;
            for (int j = 0; j < TAB - (_i % TAB); j++)
            {
                putchar(' ');
                i++;
            }
        } else
        {
            // Print char
            putchar(c);

            i++;
            
            // Reset on newline char
            if (c == '\n') i = 0;
        }
    }

    return 0;
}