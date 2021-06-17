.PHONY: clean start all 

all: simple_example.exe

#создание исполняемого файла:
simple_example.exe: simple_example.o 
	gcc -o $@ $^
#создание объектного файла:
simple_example.o: simple_example.c 
	gcc -Wall -c -o $@ $<

