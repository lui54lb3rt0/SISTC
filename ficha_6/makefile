CFLAGS = -Wall
LDFLAGS = -lrt -pthread -lm

default: ex4 clt_ex4

ex4: ex4.o
	gcc ex4.o -o ex4 $(LDFLAGS)

clt_ex4: clt_ex4.o
	gcc clt_ex4.o -o clt_ex4

clean:
	-rm *.o ex4 clt_ex4
