#include <stdio.h>

void delete_trailing(char [], int);

int main() {

    int c, i;
    char line[1000];

    i = 0;
    while ( (c=getchar()) != EOF ) {
        line[i] = c;
        ++i;
        if (c == '\n') {
            if (i == 0) continue;
            else {
                line[i] = '\0';
                printf("%s", line);
                i = 0;
            }
        }
    }

    return 0;
}

void delete_trailing(char line[], int size) {
    for (int i = size-2; i >= 0; --i)
        if (line[i] == ' ' || line[i] == '\t')
            line[i] = '\0';
        else
            break;
}
