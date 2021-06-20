.PHONY: clean start all 

all: simple_example.exe zlog_01_simple.exe

#создание исполняемого файла:
simple_example.exe: simple_example.o 
	gcc -o $@ $^
#создание объектного файла:
simple_example.o: simple_example.c 
	gcc -Wall -c -o $@ $<

zlog_01_simple.exe: zlog_01_simple.o
	gcc -o $@ $^ -L/usr/local/lib -lzlog -lpthread
zlog_01_simple.o: zlog_01_simple.c 
	gcc -Wall -c -o $@ $< -I/usr/local/include