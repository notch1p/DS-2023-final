CC = clang
CFLAGS := -O2 -Wall

all: main
main: huff.o main.c
test:
	./main -c -i test -o test.ahed -l test.log
	cat test.log
	./main -x -i test.ahed -o test.dec
	cat test.ahed.log
	md5sum test
	md5sum test.dec
clean:
	-rm -f *.o main test.ahed test.dec test.log test.ahed.log
clear:
	-rm -f test.ahed test.dec test.log test.ahed.log