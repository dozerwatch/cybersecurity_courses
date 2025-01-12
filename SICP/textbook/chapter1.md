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

### 1.1.5 The Substitution Model for Procedure Application

To apply a compound procedure to arguments, evaluate the body of the procedure with each formal parameter replaced by the corresponding argument.

Example of applying a compound procedure to argument(s) using *substitution model* for procedure application.
```scheme
; Applicative order
; first evaluates the operator and operands 
; and then applies the
; resulting procedure to the resulting arguments

(f 5)
(sum-of-squares (+ a 1) (* a 2))

(sum-of-squares (+ 5 1) (* 5 2))

(+ (square 6) (square 10))

(+ (* 6 6) (* 10 10))

(+ 36 100)

136
```
```scheme
; Normal order
; don't evaluate the operands
; until their values were needed

(f 5)
(sum-of-squares (+ a 1) (* a 2))

(sum-of-squares (+ 5 1) (* 5 2))

(+ (square (+ 5 1)) 
   (square (* 5 2)))

(+ (* (+ 5 1) (+ 5 1)) 
   (* (* 5 2) (* 5 2)))

(+ (* 6 6) 
   (* 10 10))

(+ 36 100)

136
```
The substitution model helps us visualize how to apply procedures, but is not representative of how the interpreter actually does it. The general idea is this: substitute the compound procedure with its body and substitute the formal parameters with the arguments.

### 1.1.6 Conditional Expressions and Predicates

$$|x| = \begin{cases}
  x & x \geq 0, \\
  -x & x < 0.  
\end{cases}$$

The above construct is called a *case analysis* and `cond` is a *special form* which handles case analysis.

```scheme
(define (abs x)
    (cond ((> x 0) x)
          ((= x 0) 0)
          ((< x 0) (- x))))
```

The general form for a `cond` expression is:
```scheme
(cond (⟨p₁⟩ ⟨e₁⟩)   
      (⟨p₂⟩ ⟨e₂⟩)   ; Clause - predicate
      …             ;        - consequent expression
      (⟨pₙ⟩ ⟨eₙ⟩))
```

`if` is a special form to be used if the case analysis has exactly two cases. The general form is:

```scheme
(if <predicate> <consequent> <alternative>) 
```

### 1.1.7 Example: Square Roots by Newton’s Method

There is an important difference between mathematical functions and computer procedures. Procedures must be *effective*.

Mathematical functions: describe properties of things, declarative knowledge. \
Computer procedures: describe how to do things, imperative knowledge.

### 1.1.8 Procedures as Black-Box Abstractions

Procedures could be used as a module in defining other procedures. Such procedures are regarded as "black boxes" and how they compute their results (their implementation) does not matter.

The parameter names of a procedure must be local to the body of the procedure.

*Block structure* is a nesting of definitions in procedures.
```scheme
(define (sqrt x)

  (define (good-enough? guess x)    ; Nested definition
    (< (abs (- (square guess) x)) 0.001))

  (define (improve guess x)         ; Nested definition
    (average guess (/ x guess)))

  (define (sqrt-iter guess x)       ; Nested definition
    (if (good-enough? guess x)
        guess
        (sqrt-iter (improve guess x) x)))

  (sqrt-iter 1.0 x))
```
*Lexical scoping*
```scheme
(define (sqrt x)

  (define (good-enough? guess)  ; No x parameter
    (< (abs (- (square guess) x)) 0.001))

  (define (improve guess)       ; No x parameter
    (average guess (/ x guess)))

  (define (sqrt-iter guess)     ; No x parameter
    (if (good-enough? guess)
        guess
        (sqrt-iter (improve guess))))

  (sqrt-iter 1.0))
```
Block structure helps break up large programs into tractable, or easy to deal with, pieces.

## 1.2 Procedures and the Processes They Generate

