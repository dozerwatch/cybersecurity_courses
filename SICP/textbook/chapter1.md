# Building Abstractions with Procedures

The mind uses simple ideas to make complex ideas, relate to other simple or complex ideas, and to abstract general ideas.

## 1.1 The Element of Programming

1. **Primitive expressions**: simplest entities of a programming language.
2. **Means of combination**: build compound elements from simpler ones.
3. **Means of abstraction**: compound elements are named and manipulated as units.

### 1.1.1 Expressions

Example of primitive expression: `241`. \
Example of primitive procedure: `(+ 2 4)`.

Scheme uses *prefix notation*. Its interpreter runs in a *read-eval-print* loop.

### 1.1.2 Naming and the Environment

Use `define` to create variables. This is the *simplest* form of abstraction.

Complex programs are constructed by building computational objects of increasing complexity.

The environment is the *memory* that keeps track of *name-object* pairs.

### 1.1.3 Evaluating Combinations

1. Evaluate the *subexpressions* of the combination.
2. Apply the *procedure* (the operator) to the *arguments*, which are the values of the other subexpressions (the operands).

Some expressions, like `define`, DO NOT follow the general evaluation rules. These expressions are called *special forms* and have their own evaluation rules. 

These special forms make up the syntax of a language.

### 1.1.4 Compound Procedures
*Procedure defintion* is an abstraction technique by which a compound operation can be given a name and then referred to as a unit.

```scheme
(define (square x) (* x x)) ; <-- Compound procedure named square
```

The general form of a procedure definition is
```scheme
(define (<name> <formal parameters>) <body>)
```



