#!/bin/bash

cd $(cd $(dirname $0)/..; pwd)
docker build --tag cpp11training docker
docker/test_buildimage.sh
