# cpplox

Interpreter for a custom scripting language, similar to JS

## Demo

You can peek into the supported functionality in this short REPL session.

![demo_repl](https://github.com/pancanin/cpplox/blob/main/demo_2022_12_8.PNG)


## Steps to build and run

This is a CMake based project, so you can [install CMake](https://cmake.org/install/) and do the following steps.

1. Create a `build` folder in the repo root
2. Change directory into this `build`
3. Open a terminal and type `cmake .. -G"Your generator"`. There are [many types](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) of generators. For windows, if you have Visual studio installed, you can use a windows generator which will generate a VS solution.
4. Compile the actual program and run.
-  For windows, if you are working under VS, you can use the IDE to run the project.
- For linux, after the `cmake` command, you have to run `make` and run the binary executable.


## Important classes

- Main
- Scanner
- Parser
- Interpreter

## Bugs

- When the process is terminated with Ctrl + C, the program crashes. When adding Windows.h to handle the Ctrl+C, the project goes wild.
- It would be good to warn users if they input a floating point number which overflows the supported precision in our language. For this, we have to introduce a BigDecimal
type of object.
- Multiple statements on one line do not work well! It seems that only the first one is considered. Maybe I should introduce semicolon.
- Expressions that are not part of a statement throw a parsing error when ended with semicolon. These expressions, I concluded, have no meaning in the program,
so they should throw. Example is a line of code like "5;" or "1 + 1;". I can improve the REPL so that we get results of the expressions directly in the console 
and then adding semicolons would not be needed, so the current behavior is fine, but maybe it should not throw, it should silently consume the semicolon.

## Improvements Plan

- LoxValue is copied a lot while storing and retrieving from Environment storage. Let's improve that.


## Lessons learned

- Never ignore the warnings from the compiler. Really odd linking errors could happen and some compilers are more strict than others.
- In visual studio compiler, when you have reference to an object fields in classes, you must import the header files of these classes. Forward declarations won't work for fields.