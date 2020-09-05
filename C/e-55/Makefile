ifndef CC
	CC=gcc
endif
CFLAGS=-std=c99 -Wall -Wpedantic -Wextra
SRCS=main.c main2.c
OBJS=$(subst .c,.o,$(SRCS))
RM=rm -f

all: main main2

foo: main.o main2.o
	$(CC) $(CFLAGS) -o main main.c main2 main2.c

clean:
	$(RM) $(OBJS) main
