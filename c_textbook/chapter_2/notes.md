# Chapter 2 - Types, Operators and Expressions

Variables and constants are the basic *data objects* maniputed in a program.

*Declarations* list the variables to be used, and state what type they have, and maybe their initial values.

*Operators* specify what is to be done to variables.

*Expressions* combine variables and constants to produce new values.

## 2.1 Variable Names

Names are made up of letters and digits; the first character must be a letter.

## 2.2 Data Types and Sizes

`int` will be the natural size of a machine.

Each compiler is free to choose appropriate sizes for its own hardware (with few exceptions).

The qualifier `signed` or `unsigned` may be applied to `char` or any integer.

## 2.3 Constants

*Floating-point constants* have type `double` unless suffixed;. The suffix `f / F` indicates a `float` constant; `l / L` indicate a `long double`.

A *character constant* is an integer, written as oone character within single quotes.

`\0..` represents a bit pattern in octal.

`\x..` represents a bit patten in hexadecimal.