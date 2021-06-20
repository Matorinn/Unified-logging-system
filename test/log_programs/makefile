.PHONY: clean start all 

all: simple_example.exe 01_zlog_simple.exe

#создание исполняемого файла:
simple_example.exe: simple_example.o 
	gcc -o $@ $^
#создание объектного файла:
simple_example.o: simple_example.c 
	gcc -Wall -c -o $@ $<

01_zlog_simple.exe: 01_zlog_simple.o
	gcc -o $@ $^ -L/usr/local/lib -lzlog -lpthread
01_zlog_simple.o: 01_zlog_simple.c 
	gcc -Wall -c -o $@ $< -I/usr/local/include