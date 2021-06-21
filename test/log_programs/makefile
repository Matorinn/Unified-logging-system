.PHONY: clean start all 

EXE = simple_example.exe \
	zlog_01_simple.exe \
	zlog_02_categories.exe \
	zlog_03_formats.exe \
	zlog_04_rules.exe \
	zlog_05_levels.exe \
	zlog_06_levels.exe \
	zlog_07_rotation.exe

all: $(EXE)

#создание исполняемого файла:
%.exe: %.o
	gcc -o $@ $^ -L/usr/local/lib -lzlog -lpthread
#создание объектного файла:
%.o: %.c
	gcc -Wall -c -o $@ $< -I/usr/local/include

# '%' означает одинаковые имена

clean:
	rm -rf *.o *.exe