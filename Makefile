.PHONY: clean all remake

object1=build/uls.o
object2=build/uls_functions.o
object3=build/UlsChangeConfFile.o
src1=src/uls/uls.c
src2=src/uls/uls_functions.c
src3=src/uls/UlsChangeConfFile.c
LIBDIR=bin build

all: $(LIBDIR) bin/uls

remake: clean all

bin/uls: $(object1) $(object2) $(object3)
	gcc $^ -o $@

$(object1): $(src1)
	gcc -c $^ -Wall -o $@

$(object2): $(src2)
	gcc -c $^ -Wall -o $@

$(object3): $(src3)
	gcc -c $^ -Wall -o $@

$(LIBDIR):
	mkdir $@ -p

clean:
	rm -rf $(LIBDIR) uls_cache
