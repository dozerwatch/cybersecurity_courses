#include <stdio.h>

main()
{
    float f, c;
    float l, u, s;

    l = 0;
    u = 300;
    s = 20;

    f = l;
    while (f <= u) {
        c = (5.0/9.0) * (f-32.0);
        printf("%3.0f\t%3.1f\n", f, c);
        f = f + s;
    }
}