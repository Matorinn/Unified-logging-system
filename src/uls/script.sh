#!/bin/bash
uls=/home/mato/Desktop/Unified-logging-system/src/uls/uls

make clean && make

$uls first set configfile first.config
$uls second set configfile second.config
$uls third set configfile third.config
$uls third set configfile tartar.config
$uls second set logfile second.log
$uls second set level debug
