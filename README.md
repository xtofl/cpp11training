# cpp 11 training 

Exercises to train your C++11/14/17 (and then some).

[![Build Status](https://travis-ci.org/xtofl/cpp11training.svg?branch=master)](https://travis-ci.org/xtofl/cpp11training)
[![Build status](https://xtofl.visualstudio.com/cpp11exercises/_apis/build/status/cpp11exercises-CI)](https://xtofl.visualstudio.com/cpp11exercises/_build/latest?definitionId=2)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e1556f3ddf3645fe98d1fb06bf011b1c)](https://app.codacy.com/app/kristoffel-pirard/cpp11training?utm_source=github.com&utm_medium=referral&utm_content=xtofl/cpp11training&utm_campaign=Badge_Grade_Dashboard)

## About

This repo is intended as a resource to use during C++ trainings.  If you're curious about how it came
to be, take a look at [about.md](about.md).

## Getting started

### Linux

On Linux all you need is a compiler with C++17 support; gcc-7 and gcc-8 have it.

    git clone git@github.com:xtofl/cpp11training
    mkdir -p cpp11training/build
    cd cpp11training/build
    cmake ../src
    make

### Windows

    
Prerequisite: currently I have it up and running for Visual Studio 2017 Community edition.  It relies on NuGet package manager, which should be installed explicitly (cf. [stackoverflow](http://stackoverflow.com/questions/42875451/cant-find-the-nuget-package-manager-in-visual-studio-2017))

Open the `cpp11training/cpp11training.sln` solution.

### Docker host

If you don't want to litter your system with tools you don't trust, but you _do_ trust Docker, you can
build and run the docker container in [docker](docker).  You may even be in luck and simply `docker pull xtofl/cpp11training`.

Then, clone the repository, and start a cpp11training container.  Now you can follow the steps like in Linux.

(windows users may be happy to find a `run_container.bat` script to help)

## Exercising

The project contains a bunch of failing unit tests.  The idea is that you un-DISABLE each one of them, and make it pass (using C++11, obviously).  (the gtest library by default ignores tests starting with `DISABLED_`.)

I tried to add a TODO: comment hinting what's expected from you to fulfill the exercise.

Once all tests pass, I have nothing more to teach you :)
