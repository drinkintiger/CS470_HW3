#
# Vladimir Tsoy & Jordan Harmel 
# CS 470
#
# Makefile for Pre Order Tree
#

CC=gcc
CFLAGS=-g -Wall -std=gnu99
LDFLAGS=-lpthread

all: preorder tree

preorder: tree preorder.c
	$(CC) -o preorder tree.o $(CFLAGS) $(LDFLAGS) preorder.c

tree: tree.c tree.h
	$(CC) -c -o tree.o $(CFLAGS) tree.c

clean:
	$(RM) preorder *.o
	$(RM) -rf *.dSYM
