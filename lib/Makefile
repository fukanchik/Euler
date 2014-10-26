#
#
#
LIB=libueuler.a
OBJS=palindrome.o large.o primes.o reverse.o pandigital.o assert.o
OBJS+=ullrev.o ullpal.o 

TESTOBJS=test.o

include ../flags.mk

all: $(LIB)

$(LIB): $(OBJS)
	ar rc $(LIB) $(OBJS)

clean:
	rm -rf $(LIB) $(OBJS)

test: $(TESTOBJS) $(LIB)
	$(CC) $(LDOPT) -o test $(TESTOBJS) $(LIBS)

