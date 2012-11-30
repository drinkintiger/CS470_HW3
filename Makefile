#
# Vladimir Tsoy & Jordan Harmel 
# CS 470
#
# Makefile for Pre Order Tree
#

CC=gcc
CFLAGS=-g -Wall -std=gnu99
LDFLAGS=-lpthread

all: preorder

preorder: preorder.c
	$(CC) -o preorder $(CFLAGS) $(LDFLAGS) preorder.c

clean:
	$(RM) preorder *.o
	$(RM) -rf *.dSYM
