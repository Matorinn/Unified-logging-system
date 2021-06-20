#переменная для подключения файлов:
INCLUDE = -I ../thirdparty

.PHONY: clean all test 

test: main_test.exe 

#создание исполняемого файла:
main_test.exe: main_test.o 
	gcc -o $@ $^
#создание объектного файла:
main_test.o: main_test.c 
	gcc $(INCLUDE) -Wall -c -o $@ $<

clean:
	rm -rf *.o *.exe log_files/*.log
