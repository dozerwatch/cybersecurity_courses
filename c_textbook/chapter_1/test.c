#include <stdio.h>

int main()
{
    // Frequency of characters a-z, whitespace, and other

    // Declare variables and arrays
    int c, i, j, nwhite, nother;
    int nlower[26];
    int nupper[26];
    int ndigit[10];
    
    // Initialize arrays
    nwhite = nother = 0;
    for (i = 0; i < 26; ++i)
        nlower[i] = nupper[i] = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;
    
    
    while ((c = getchar()) != EOF)
        if (c >= 'a' && c <= 'z')
            ++nlower[c-'a'];
        else if (c >= 'A' && c <= 'Z')
            ++nupper[c-'A'];
        else if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    
    for (i = 0; i < 10; ++i) {
        printf("%d: ", i);
        for (j = 0; j < ndigit[i]; ++j)
            printf("-");
        printf("\n");
    }
    for (i = 0; i < 26; ++i) {
        printf("%c: ", i+97);
        for (j = 0; j < nlower[i]; ++j)
            printf("-");
        printf("\n");
        printf("%c: ", i+65);
        for (j = 0; j < nupper[i]; ++j)
            printf("-");
        printf("\n");
    }
    printf("white space: ");
        for (j = 0; j < nwhite; ++j)
            printf("-");
    printf("\n");
    printf("other: ");
        for (j = 0; j < nother; ++j)
            printf("-");
        
}