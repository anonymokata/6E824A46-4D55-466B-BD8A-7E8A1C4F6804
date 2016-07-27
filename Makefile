CC=gcc
CFLAGS=-std=c99 -march=native -pedantic -pedantic-errors -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs  -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Wconversion -Wwrite-strings -Wpointer-arith -Wstrict-prototypes -Wmissing-prototypes  
LIBS=
TESTDIR=tests
SRCDIR=src
OBJS=roman.o

all: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o main.out $(SRCDIR)/main.c $(SRCDIR)/*.o $(LIBS)

.c.o: 
	$(CC) -c -o $@ $(CFLAGS) $< $(LIBS)

test: $(TESTDIR)/roman_test.c $(SRCDIR)/roman.o $(SRCDIR)/string_functions.o
	$(CC) $(CFLAGS) -o roman_test.out $(TESTDIR)/roman_test.c $(SRCDIR)/*.o $(LIBS) -lcheck
	./roman_test.out

clean: 
	rm -f $(TESTDIR)/*.o $(SRCDIR)/*.o roman_test.out main.out

format: 
	clang-format -i */*.c */*.h
