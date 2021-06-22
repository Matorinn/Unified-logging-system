#!/bin/bash

make clean
cd log_programs
make clean
make
./zlog_01_simple.exe
./zlog_02_categories.exe
./zlog_03_formats.exe
./zlog_04_rules.exe
./zlog_05_levels.exe
./zlog_06_levels.exe
./zlog_07_rotation.exe
./zlog_08_MDC.exe
cd ..
make
./main_test.exe
