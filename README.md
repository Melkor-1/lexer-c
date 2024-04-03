# Lexer for the Monkey Programming Language

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://https://github.com/Melkor-1/lexer-c/edit/main/LICENSE)

A C version of a lexer for [the Monkey programming language](https://monkeylang.org/), originally written in Go, as presented in the book [Writing An Interpreter In Go](https://interpreterbook.com/).

## Language:

Copy pasting from the book:

> Here is how we bind values to names in Monkey: 
    
    let age = 1; 
    let name = "Monkey"; 
    let result = 10 * (20 / 2);

> Besides integers, booleans and strings, the Monkey interpreter we’re going to build will also support arrays and hashes. Here’s what binding an array of integers to a name looks like: 

    let myArray = [1, 2, 3, 4, 5]; 

> And here is a hash, where values are associated with keys: 

    let thorsten = {"name": "Thorsten", "age": 28}; 

> Accessing the elements in arrays and hashes is done with index expressions: 

    myArray[0] // => 1 
    thorsten["name"] // => "Thorsten" 

> The let statements can also be used to bind functions to names. Here’s a small function that adds two numbers: 

    let add = fn(a, b) { return a + b; };

> But Monkey not only supports return statements. Implicit return values are also possible, which means we can leave out the return if we want to: 

    let add = fn(a, b) { a + b; }; 

> And calling a function is as easy as you’d expect: 

    add(1, 2); 

> A more complex function, such as a fibonacci function that returns the Nth Fibonacci number, might look like this: 

    let fibonacci = fn(x) { 
        if (x == 0) { 
            0
        } else { 
            if (x == 1) {
                 1 
            } else { 
                 fibonacci(x - 1) + fibonacci(x - 2);
            }
        }
    }; 

> Note the recursive calls to fibonacci itself! Monkey also supports a special type of functions, called higher order functions. These are functions that take other functions as arguments. Here is an example:

    let twice = fn(f, x) { return f(f(x)); }; 
    let addTwo = fn(x) { return x + 2; }; 
    twice(addTwo, 2); // => 6

## Building:

To build the REPL, clone the repository and run:

```shell
cd lexer-c
make
```

The executable will be generated in the `bin` directory.

To run the tests:

```shell
make test
```


