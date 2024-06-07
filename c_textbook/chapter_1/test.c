#include <stdio.h>

#define MAXLINE 1000   /* maximum input line length */

int _getline(char [], int);
void _remove(char [], int);
void _reverse(char []);

/* print the longest input line */
int main() {

    int len;                /* current line length */
    char line[MAXLINE];     // current input line

    while ((len = _getline(line, MAXLINE)) > 0) {
        _reverse(line);
        printf("%s", line);
    }

    return 0; 
}
/* getline:  read a line into s, return length  */
int _getline(char s[],int lim) {

    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i; 
    }

    s[i] = '\0';

    return i;
}

void _remove(char line[], int i) {
    if (i == 1) {
        if (line[0] != '\n')
            printf("%s", line);
    }
    else if (i > 1) {
        i -= 2;
        while (line[i] == ' ' || line[i] == '\t') {
            line[i] = '\0';
            --i;
        }
        for (int j = 0; j <= i; ++j)
            printf("%d ", line[j]);
    }
}

void _reverse(char s[]) {
    
    int i;
    char temp;

    for (i = 0; s[i] != '\0'; ++i);

    --i;

    if (s[i] == '\n') --i;

    int j = 0;

    while (j < i) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        --i;
        ++j; 
    }
}