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

```scheme
; Lexical scoping
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

We have learned the elements of programming - primitive expressions, means of combination, means of abstraction, but we do not know how to program yet. We lack the knowledge of which procedures are worth defining and the experience to predict the consequences of executing a procedure.

The ability to visualize the processes generated by various types of procedures is *crucial* to becoming an expert programmer.

A procedure is a pattern ("shape") for the *local evolution* of a computational process.

**Goals for this section:**
1. Examine common "shapes" for processes generated by simple procedures. 
2. Investigate the rates at which these processes consume time and space.

### 1.2.1 Linear Recursion and Iteration

```scheme
; Linear recursive process:
(define (factorial n)
  (if (= n 1) 
      1 
      (* n (factorial (- n 1)))))

; Chain of deferred operations
(factorial 6)
(* 6 (factorial 5))
(* 6 (* 5 (factorial 4)))
(* 6 (* 5 (* 4 (factorial 3))))
(* 6 (* 5 (* 4 (* 3 (factorial 2)))))
(* 6 (* 5 (* 4 (* 3 (* 2 (factorial 1))))))
(* 6 (* 5 (* 4 (* 3 (* 2 1)))))
(* 6 (* 5 (* 4 (* 3 2))))
(* 6 (* 5 (* 4 6)))
(* 6 (* 5 24))
(* 6 120)
720
```

```scheme
; Linear iterative process:
(define (factorial n) 
  (fact-iter 1 1 n))

(define (fact-iter product counter max-count)
  (if (> counter max-count)
      product
      (fact-iter (* counter product)
                 (+ counter 1)
                 max-count)))

(factorial 6)
(fact-iter 1 1 6)
(fact-iter 1 2 6)
(fact-iter 2 3 6)
(fact-iter 6 4 6)
(fact-iter 24 5 6)
(fact-iter 120 6 6)
(fact-iter 720 7 6)
720
```

A recursive process is different from a recursive procedure. The former talks about how a process evolves, while the latter is about the syntax of how a procedure is written.

### 1.2.2 Tree Recursion

```scheme
; Really bad procedure!
; Tree recursive process:
(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1))
                 (fib (- n 2))))))
```

```scheme
; Linear iterative process:
(define (fib n) 
  (fib-iter 1 0 n))

(define (fib-iter a b count)
  (if (= count 0)
      b
      (fib-iter (+ a b) a (- count 1))))
```

**Example: Counting change**

```scheme
; Tree recursive process:
(define (count-change amount)
  (cc amount 5))

(define (cc amount kinds-of-coins)
  (cond ((= amount 0) 1)
        ((or (< amount 0) 
             (= kinds-of-coins 0)) 
         0)
        (else 
         (+ (cc amount (- kinds-of-coins 1))
            (cc (- amount (first-denomination 
                           kinds-of-coins))
                kinds-of-coins)))))

(define (first-denomination kinds-of-coins)
  (cond ((= kinds-of-coins 1) 1)
        ((= kinds-of-coins 2) 5)
        ((= kinds-of-coins 3) 10)
        ((= kinds-of-coins 4) 25)
        ((= kinds-of-coins 5) 50)))
```

Tree recursive processes may be highly inefficient but easy to define, whereas linear iterative processes may be efficient but are difficult to define.

### 1.2.3 Orders of Growth

Order of growth generally measures the amount of resources required by a process as the inputs grows larger. Although it provides a basic description of the behavior of a process, it is a useful indicator of what to expect as the input changes.

### 1.2.4 Exponentiation

```scheme
; Linear recursive process
; Space: O(n)
; Time:  O(n)
(define (expt b n)
  (if (= n 0) 
      1 
      (* b (expt b (- n 1)))))
```      

```scheme
; Linear iterative process
; Space: O(1) 
; Time:  O(n)
(define (expt b n) 
  (expt-iter b n 1))

(define (expt-iter b counter product)
  (if (= counter 0)
      product
      (expt-iter b
                 (- counter 1)
                 (* b product))))
```

```scheme
; b^n = (b^(n/2))^2     if n is even
; b^n = b * b^(n-1)     if n is odd
; Space: O(log n) 
; Time:  O(log n)
(define (fast-expt b n)
  (cond ((= n 0) 
         1)
        ((even? n) 
         (square (fast-expt b (/ n 2))))
        (else 
         (* b (fast-expt b (- n 1))))))

(define (even? n)
  (= (remainder n 2) 0))
```

### 1.2.5 Greatest Common Divisors

```scheme
; Iterative process
; O(log n)
(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))
```

### 1.2.6 Example: Testing for Primality
```scheme
; O(√n)
(define (smallest-divisor n)
    (define (find-divisor n test-divisor)
        (cond ((> (square test-divisor) n) 
                n)
                ((divides? test-divisor n) 
                test-divisor)
                (else (find-divisor 
                    n 
                    (+ test-divisor 1)))))
    (find-divisor n 2))

(define (divides? a b)
  (= (remainder b a) 0))
```

Fermat's Little Theorem: \
If $a$ is a prime number and $n$ is any positive integer less than $a$, then $n^a \cong n$ mod $a$.

```scheme
; O(log n)

```