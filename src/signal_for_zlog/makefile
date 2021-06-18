.PHONY: clean start all 

all: zlog_with_signal.exe

zlog_with_signal.exe: zlog_with_signal.o 
	gcc -o $@ $^ -L/usr/local/lib -lzlog -lpthread
zlog_with_signal.o: zlog_with_signal.c 
	gcc -Wall -c -o $@ $< -I/usr/local/include