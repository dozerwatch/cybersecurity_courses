# Building Abstractions with Procedures 

## Lecture 1: Functional Programming 1

`00:00 - 19:14` Go over basic Scheme syntax. 

`19:14 - 32:00` Administrative and class stuff

`32:00 - 34:29` Vocabulary Lesson: formal parameter, body, actual argument expression, actual argument value

`35:00 - End` Examples of procedures: plural, pig-latin 

This lecture was mostly a review of the Scheme language and how procedures work in Scheme, along with some procedure examples. There was also administrative stuff.

## Lecture 2: Functional Programming 2

`00:00 - 7:25` Administrative stuff / Yapping

`7:25 - 11:00` Review of last lecture 

`11:00 - 16:30` Computer Science vs Software Engineering vs Electrical Engineering vs Complexity Engineering, Programming Paradigm / Yapping

Go over the levels of Abstraction for computers: quantom physics -> Applications.

Function vs Procedure - Functions give the same output for same input. Functions are good for parallelism, because it doesn't care what else goes on in the other CPUs.

Faster computers generate more heat. Now chips melt if computers runs any faster. Solution is computers run slower, but we bunch a lot of them (CPU) into one chip.

```
f(x) = 2x+6   Same Function
g(x) = 2(x+3) Different Procedures
```

In computers, we don't really have functions. We have procedures.

It's much easier to make a program that works faster, then make a fast program work.

Demonstrates Buzz program: go over `cond`. 

Normal order vs Applicative order.

Random is a procedure that is NOT a function.

Correct functional programs give the same answer no matter the order (normal or applicative).

## Lecture 3: Higher-Order Procedures 1

Big Idea: Function is Data. \
There is naturally a brick wall separating `things` (nouns, data) and `actions` (verbs, procedures). 

Simple Idea: Generalizing Patterns \
We can generalize similar functions into one function with more arguments. These arguments can be a number or a function.

`lambda` is the way to make a procedure. These two `define`'s are EQUAL.
```scheme
(define (square x) (* x x))
(define square (lambda (x) (* x x)))
```
`lambda` is usually used as an argument to a procedure.

Higher-order procedures either take a procedure as its argument or returns a procedure as its value. 

Generalizing patterns is good for keeping programs from getting too long.

## Lecture 4: Higher-Order Procedures 2





