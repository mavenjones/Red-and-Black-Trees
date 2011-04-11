##
## Makefile for CS161 Final Programming Project
##

## Set the compiler to be a known ANSI compliant one
CC = gcc

## the -I allows you to include any local header files for our
## class libraries.  
CFLAGS = -g -Wall -Wpointer-arith
LDFLAGS = -g

HDRS = collection.h
SRCS = collection.c
TESTOBJS = collectionTest.o $(SRCS:.c=.o)
TIMEOBJS = timeTest.o $(SRCS:.c=.o)
TARGET = collectionTest

default : collectionTest timeTest

collectionTest : $(TESTOBJS)
	$(CC) $(TESTOBJS) $(CFLAGS) $(LDFLAGS) -o collectionTest

timeTest : $(TIMEOBJS)
	$(CC) $(TIMEOBJS) $(CFLAGS) $(LDFLAGS) -o timeTest

# The dependencies below make use of make's default rules,
# under which a .o automatically depends on its .c and
# the action taken uses the $(CC) and $(CFLAGS) variables.
# These lines describe a few extra dependencies involved.

collection.o : collection.h
collectionTest.o : collection.h
timeTest.o : collection.h

clean : 
	@echo "Removing all object files..."
	\rm -fr core *.o $(TARGET) collectionTest timeTest