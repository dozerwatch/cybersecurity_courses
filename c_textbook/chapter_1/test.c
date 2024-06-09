#include <stdio.h>

#define TAB 8   // Tab stop every 8th column
#define IN 1    // In a string of blanks
#define OUT 0   // Outside a string of blanks

int main() {

    int c, state, tabs, spaces;
    int space_count = 0;

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' && state == IN)
            space_count++;
        else if (c == ' ') {
            state = IN;
            space_count++;
        }
        else {
            state = OUT;
            if (space_count > 0) {
                tabs = space_count / TAB;
                spaces = space_count % TAB;
                space_count = 0;
                for (int i = 0; i < tabs; ++i) putchar('\t');
                for (int i = 0; i < spaces; ++i) putchar(' ');
            }
            putchar(c);
        }
    }

    return 0;
}

// I FORGOT ABOUT TAB STOPS! NEED TO FACTOR THEM IN FOR THE COUNT OF TABS!