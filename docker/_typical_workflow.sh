#!/bin/sh

set -x
projectdir=$(cd $(dirname $0)/.. && pwd)

# make a build folder
cd $(mktemp -d -t cpp11training_build)

# make the project
cmake $projectdir/src && make

# run the tests
./cpp11training

