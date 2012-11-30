/*
 * Vladimir Tsoy & Jordan Harmel
 * Nov. 11, 2012
 *
 * CS 470 : Project 3
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
char *name;
struct Node *parent;
struct Node *child;
struct Node *sibling;
//struct Node *order;
int pre;
};

#define OPENP 1
#define CLOSEP 2
#define EOL -1
#define NAME 3

void BuildTree(char *t, struct Node **root, struct Node *** nodes, int *count, struct Node **leftMost);

int numNodes;
struct Node ** nodesArray;
struct Node * build(struct Node *p, struct Node **temp);

void BuildTree(char *t, struct Node **root, struct Node *** nodes, int *count, struct Node ** child) {
    struct Node *temp;
    numNodes = 0;
    initTokens(t);
    nodesArray = (struct Node **) malloc(sizeof(struct Node*) *strlen(t)/2);
    numNodes = 0;
    *root = build(NULL, &temp);
    *child = temp;
    *count = numNodes;
    *nodes = nodesArray;
}
