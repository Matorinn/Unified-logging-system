#!/bin/bash

make clean
cd log_programs
make clean
make
./zlog_01_simple.exe
./zlog_02_categories.exe
./zlog_03_formats.exe
cd ..
make
./main_test.exe
