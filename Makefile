CC=gcc
CFLAGS=-std=c99 -Werror -Wall -Wextra -pedantic-errors
LIBS=
TESTDIR=tests
SRCDIR=src
OBJS=roman.o

all: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o main.out $(SRCDIR)/main.c $(SRCDIR)/*.o $(LIBS)

.c.o: 
	$(CC) -c -o $@ $(CFLAGS) $< $(LIBS)

test: $(TESTDIR)/roman_test.c $(SRCDIR)/roman.o
	$(CC) $(CFLAGS) -o roman_test.out $(TESTDIR)/roman_test.c $(SRCDIR)/*.o $(LIBS) -lcheck
	./roman_test.out

clean: 
	rm -f $(TESTDIR)/*.o $(SRCDIR)/*.o roman_test.out main.out

format: 
	clang-format -i */*.c */*.h
