# Chapter 1

## 1.1 Getting Started

The type specifier for `main()` can be missing and the program can still be compiled.

What is the difference between `cc` and `gcc`?

A C program conists of *functions* and *variables*. Programs begin executing at the beginning of the `main` function.

`#include <stdio.h>`  tells the compiler to include information about the standard input/output library.

A *character string* or *string constant* is a sequence of characters in double quotes.

An *escape sequence* like `\n` provides a way to represent hard-to-type or invisible characters.

## 1.2 Variables and Arithmetic Expressions

In C, all variables must be declared before they are used.

The body of a `while` can be one or more statements enclosed in braces, or a single statement without braces.

In C, **integer division** truncates: any fractional part is discarded! Thus, it is not very accurate.

`printf` is a general-purpose output formatting function. It is not a part of the C language, but from the standard library of functions. C, itself, has no input or output defined.

If an arithmetic operator has one floating-point operand and one integer operand, the integer will be converted to floating point before the operation is done.

## 1.3 The for statement

A general rule: In any context where it is permissible to use the value of some type, you can use a more complicated expression of that type.

## 1.4 Symbolic Constants

A `#define` line defines a *symbolic name* or *symbolic constant* to be a particular string of characters. 

Conventionally written in upper case. 

Does not end in semicolon.

## 1.5 Character Input and Output

Text input or output is dealt with as *streams of characters*.

A *text stream* is a sequence of characters divided into lines; each line consists of zero or more characters followed by a newline character.

`getchar()` reads the *next input character* from a text stream and returns that as its value.

`putchar(c)` prints the contents of `c` as a character.

### 1.5.1 File Copying

This simple program copies its input to its output one character at a time.
```c
#include <stdio.h>
main()
{
    int c;
    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
}
```
We use `int` instead of `char` because `char` isn't big enough to hold `EOF`.

`EOF` is an integer defined in <stdio.h>. It is `-1`.

In C, any assignment is an expression and has a value, which is the LHS after the assignment. Thus the above program can be made more concise.

```c
#include <stdio.h>
main()
{
    int c;
    while ((c = getchar()) != EOF)
        putchar(c);
}
```
The paratheses around the assignment is *necessary* because the precedence of `!=` is higher than `=`.

### 1.5.2 Character Counting

```c
#include <stdio.h>
main()
{
    double nc;
    for (nc = 0; getchar() != EOF; ++nc)
        ;
    printf("%.0f\n", nc);
}
```
The body of the for loop is empty. C requires a for statement to have a body and the isolated semicolon, called a *null statement*, is there to satisfy that requirement.

### 1.5.3 Line Counting

The standard library ensures that an input text stream appears as a sequence of lines, each terminated by a newline. Hence, counting lines is just counting newlines.

```c
#include <stdio.h>
main()
{
    int c, nl;
    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);
}
```

A character written between single quotes represent an integer value equal to the numerical value of the character. It is called a *character constant*.

### 1.5.4 Word Counting