Make a compiler for a language that is a simple functional programming langauge with basically the functionality of haskell










Defining a named function:

Func retType myfunc(arg1, arg2)(
    let var1 = ..... & let var2
    in

)


Anonymous functions:
\x -> x*x               x is the free variable

\x \y \x -> x+y+z       will be evaluated as \x -> (\y -> (\z - > x + y + z))

Arrays: [1, 2, 3, 4]

Strings: "Hello"
    Concatenation - ++

Logical expressions(TODO still need to figure out exactly how this should be syntactically defined):
    if 

Arithmetic expressions(This will be a lot of work to properly check at the abstract syntax tree):
    (2*(3 + 4)) will get curryed to ( (* 2)   ((+ 3) 4)), and should get this order deterministically

    (4 - 2*3) will get curryed to ((- 4) ((* 2) 3) )

