.PHONY: clean all create_static_lib  

all: example.exe

# исполняемая программа:
example.exe: example.o signal_for_zlog.o
	gcc -o $@ $^ -L/usr/local/lib -lzlog -lpthread

# объектные файлы:
example.o: example.c 
	gcc -Wall -c -o $@ $< -I/usr/local/include
signal_for_zlog.o: signal_for_zlog.c
	gcc -Wall -c -o $@ $< -I/usr/local/include

# статическая библиотека:
create_static_lib: 
	ar rc libsignal_for_zlog.a signal_for_zlog.o

# линковать стат. библиотеку надо примерно так:
#	gcc main.c -o main.exe -L. -lsignal_for_zlog

# для примера, как слинковать ее с example.c:
#	gcc example.c -o example.exe -L. -lsignal_for_zlog -L/usr/local/lib -lzlog -lpthread

clean:
	rm -rf *.o *.exe PID.txt