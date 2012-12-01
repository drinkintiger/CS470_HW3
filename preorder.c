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

typedef struct Node {
char *name;
struct Node *parent;
struct Node *child;
struct Node *sibling;
struct Node *next;
int pre;
}Node;

char *substring(char * input, int length);
void split(char * in, char ** first, char ** rest);
Node *buildNode (Node * parent, char * node, char * sibling);

int main(int argc, char * argv[]) {
    char * first;
    char * rest;
    Node *temp = malloc(sizeof(Node));
    Node *parent = malloc(sizeof(Node));
    
    temp = buildNode(parent, "(A(B)(C(E)(F))(D(G)))", NULL);
    //split ("(A)(B)(C)", &first, &rest);
    //printf ("First : %s Rest: %s\n", first, rest);
}

Node *buildNode (Node * parent, char * node, char * sibling) {
    int start = -1, end, length, next, count = 0;
    Node * child;
    Node * sibling;
    char * temp;
    char * first;
    char * rest;

    length = strlen(node);
    for (int i = 0; i < length; ++i) {
        if (node[i] == '(') {
            if (start < 0) {
                start = i;
                count += 1;
                next = i;
            }
            else if (count == 1) {
                if (parent->name == NULL) {
                    printf("ONE A\n");
                    parent -> name = substring(&node[start+1], i - 1);
                    printf("ONE B\n");
                    next = i;
                }
                count += 1;
            }
        }
        else if (node[i] == ')') {
            count -= 1;
            if (count == 0) {
                temp = substring(&node[start + 1], length - 2 );
                end = i;
                break;
            }
        }
    }
    split(temp, &first, &rest);
    
    printf ("The parent is : %s\n", parent -> name);
    printf ("The child is : %s\n", first);
    printf ("The remainder is : %s\n", rest);
    
    if (first == NULL && rest == NULL) {
        return parent;
    }
    parent->child = buildNode(parent, first, rest);
    return parent;
}
char *substring(char * input, int length) {
    char * temp = malloc(sizeof(char) * (length + 1));
    temp = memcpy(temp, input, length);
    temp[length] = 0;
    return temp;
}

void split(char * in, char ** first, char ** rest) {
    int length = strlen(in);
    int start = -1, count = 0, end;
    
    if (in == NULL || in == '\0') {
        *first = NULL;
        *rest = NULL;
        return;
    }
    
    for (int i = 0; i < length; ++i) {
        if (in[i] == '(') {
            if (start == -1) {
                start = i;
            }
            count += 1;
        }
        else if (in[i] == ')') {
            count -= 1;
            if (count == 0) {
                end = i;
                break;
            }
        }
    }
    
    if (start < 0) {
        *first = NULL;
        *rest = NULL;
        return;
    }
    
    *first = substring (&in[start], end - start + 1);
    if (end + 1 >= length) {
        *rest = NULL;
    }
    else {
        *rest = substring(&in[end + 1], length - (end + 1));
    }
}
