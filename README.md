# cpp 11 training 

Exercises to traing your C++11.

[![Build Status](https://drone.io/bitbucket.org/xtofl/cpp11training2015/status.png)](https://drone.io/bitbucket.org/xtofl/cpp11training2015/latest)

## Getting started

### Linux

On Linux all you need is

    git clone git@bitbucket.org:xtofl/cpp11training2015
    cd cpp11training2015/cpp11training
    cmake .
    make

### Windows

On Windows not all is ready yet: you need google test as a submodule:

    git clone --recurse-submodules git@bitbucket.org:xtofl/cpp11training2015
    
and open the `cpp11training/cpp11training.sln` solution.
   

## Exercising

The project contains a bunch of failing unit tests.  The idea is that you un-DISABLE_ each one of them, and make it pass (using C++11, obviously).

Once all tests pass, I have nothing more to teach you :)