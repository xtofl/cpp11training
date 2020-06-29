#!/bin/sh

# script to test the build container
#
# it runs the typical workflow in the build container
# (cf. _typical_workflow.sh)

project_dir=$(cd $(dirname $0)/..; pwd)

docker build -t xtofl/cpp11training $project_dir/docker

docker run --volume $(pwd):$(pwd) --workdir $(pwd) --rm ${IMAGE:-"xtofl/cpp11training"} /bin/sh docker/_typical_workflow.sh

