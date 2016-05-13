# cpp 11 training 

Exercises to train your C++11 (and then some).

[![Build Status](https://drone.io/github.com/xtofl/cpp11training/status.png)](https://drone.io/github.com/xtofl/cpp11training/latest)
:( Currently I don't get g++5 nor clang installed on drone.io - have to look for e.g. travis or some other ci.

## Getting started

### Linux

On Linux all you need is

    # unless you're happy with g++ - the compile messages
    # can get quite cumbersome when dealing with templates
    export CXX=clang++

    git clone git@github.com:xtofl/cpp11training
    cd cpp11training/cpp11training
    cmake .
    make



### Windows

On Windows not all is ready yet: you need google test as a submodule:

    git clone --recurse-submodules git@github.com:xtofl/cpp11training
    
and open the `cpp11training/cpp11training.sln` solution.


## Exercising

The project contains a bunch of failing unit tests.  The idea is that you un-DISABLE each one of them, and make it pass (using C++11, obviously).  (the gtest library by default ignores tests starting with `DISABLED_`.)

I tried to add a TODO: comment hinting what's expected from you to fulfill the exercise.

Once all tests pass, I have nothing more to teach you :)
