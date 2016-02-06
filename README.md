# cpp 11 training 

Exercises to traing your C++11.

[![Build Status](https://drone.io/github.com/xtofl/cpp11training/status.png)](https://drone.io/github.com/xtofl/cpp11training/latest)

## Getting started

### Linux

On Linux all you need is

    git clone git@github.com:xtofl/cpp11training
    cd cpp11training/cpp11training
    cmake .
    make

### Windows

On Windows not all is ready yet: you need google test as a submodule:

    git clone --recurse-submodules git@github.com:xtofl/cpp11training
    
and open the `cpp11training/cpp11training.sln` solution.


## Exercising

The project contains a bunch of failing unit tests.  The idea is that you un-DISABLE_ each one of them, and make it pass (using C++11, obviously).

Once all tests pass, I have nothing more to teach you :)
