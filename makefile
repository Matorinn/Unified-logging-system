#переменная для подключения файлов:
INCLUDE = -I thirdparty

.PHONY: clean start all test 

test: test.exe 

#создание исполняемого файла:
test.exe: test/main_test.o 
	gcc -o $@ $^
#создание объектного файла:
test/main_test.o: test/main_test.c 
	gcc $(INCLUDE) -Wall -c -o $@ $<

