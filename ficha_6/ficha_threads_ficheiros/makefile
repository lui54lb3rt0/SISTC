CFLAGS = -Wall
LDFLAGS = -lrt -pthread -lm

default: ex1 par mutex

ex1: ex1.o myprint.o 

par: par.o
	gcc par.o -o par $(LDFLAGS)

par_50: par_50_t.o
	gcc par_50_t.o -o par_50_t $(LDFLAGS)

mutex: mutex.o myprint.o

ficha-threads-ficheiros.zip: ex1.c myprint.c par.c par_50_t.c mutex.c makefile
	-rm $@
	zip $@ $^

clean:
	-rm *.o ex1 par mutex par_50_t
