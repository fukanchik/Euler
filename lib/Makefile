#
#
#
LIB=libueuler.a
OBJS=palindrome.o large.o primes.o reverse.o pandigital.o assert.o
OBJS+=ullrev.o ullpal.o number.o perm.o totient.o fibo.o ifactors.o

TESTOBJS=test.o

include ../flags.mk

all: $(LIB) test

$(LIB): $(OBJS)
	ar rc $(LIB) $(OBJS)

clean:
	rm -rf $(LIB) $(OBJS) test

test: $(TESTOBJS) $(LIB)
	$(CC) $(LDOPT) -o test $(TESTOBJS) $(LIBS)

test.o: test.c
	$(CC) $(CFLAGS) -c -o test.o test.c
