#!/bin/bash
uls=bin/uls

make clean && make

$uls first set configfile bin/first.conf
$uls example set configfile src/signal_for_zlog/example.conf
$uls third set configfile bin/third.conf
$uls example set logfile bin/EXAMPLE.LOG
$uls example set logfile /home/$(whoami)/Desktop/example.log
$uls example set level debug
$uls example set level info
$uls example commit
