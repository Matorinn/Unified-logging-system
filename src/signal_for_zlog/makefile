.PHONY: clean start all 

all: example.exe

example.exe: example.o signal_for_zlog.o
	gcc -o $@ $^ -L/usr/local/lib -lzlog -lpthread
example.o: example.c 
	gcc -Wall -c -o $@ $< -I/usr/local/include

signal_for_zlog.o: signal_for_zlog.c
	gcc -Wall -c -o $@ $< -I/usr/local/include


clean:
	rm -rf *.o *.exe