CFLAGS = -Wall
LDFLAGS = -lrt -pthread -lm

default: ex2 ex1-fork

all: default ex3.o ficha-sinc-ficheiros.zip

ex2: ex2.o myprint.o 

ex3.o: mymq.h

ficha-sinc-ficheiros.zip: ex3.c myprint.c ex2.c makefile mymq.h
	-rm $@
	zip $@ $^

clean:
	-rm *.o ex2
