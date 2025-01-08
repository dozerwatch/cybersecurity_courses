# Lecture 2: Functional Programming 2

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