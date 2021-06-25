#!/bin/bash

mkdir /home/$(whoami)/.cache/uls

make clean && make

LD_LIBRARY_PATH=/usr/local/lib ./example
