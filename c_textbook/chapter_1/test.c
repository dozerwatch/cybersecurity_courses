#include <stdio.h>

#define LINE_LEN 20

int main() {

    int c;
    char line[LINE_LEN+1]; // Array to store one line of input

    int i = 0; // Current index

    int found_blank = 0; // Check whether a blank has been found on current line
    int blank_index;

    while ((c = getchar()) != EOF) {

        // Check for newline character, flush buffer and begin new line
        if (c == '\n') {
            line[i] = '\0';
            puts(line);
            i = 0;
            found_blank = 0;
            continue;
        }

        // Check for blanks, set variables accordingly
        if (c == ' ' || c == '\t') {
            found_blank = 1;    // Found blank is true
            blank_index = i;
        }

        // Insert into array
        line[i] = c;

        // Line is too long
        if ( i == LINE_LEN-1 ) 
        { 
            // There are blanks
            if ( found_blank ) 
            {
                // Print the characters up to the last blank
                line[blank_index] = '\0';
                puts(line);
                
                // Put the rest of the characters into start of next line !!
                int k = 0;
                for (int j = blank_index+1; j <= i; j++) {
                    line[k] = line[j];
                    k++;
                }

                // Set current index
                i = k;

                found_blank = 0;
                continue;
            }
            // There are no blanks
            else 
            {
                // Flush buffer, reset for new line
                line[i+1] = '\0';
                puts(line);
                i = 0;
                found_blank = 0;
                continue;
            }
        }

        // Increment array index
        i++;
    }

    return 0;
}