#!/bin/bash

grep "^#" | sed -e "s/#/  */g"
