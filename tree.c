/*
 * Vladimir Tsoy & Jordan Harmel
 * Nov. 11, 2012
 *
 * CS 470 : Project 3
 */
#include "tree.h"

struct Node * build(struct Node *p, struct Node **temp) {
    int token;
    struct Node *n;
    struct Node *temp2;
    struct Node *temp1;
    struct Node *last;
    char *name;
    token = getToken(&name);
    if (token == OPENP) {
        token = getToken(&name);
        if (token == NAME) {
            n = (struct Node *) malloc(sizeof(struct Node));
            nodesArray[numNodes] = n;
            numNodes++;
            n->parent = p;
            //n->pre = 1; dont't number utill the tree is built
            n->sibling = NULL;
            n->name = name;
            n->child = build(n, &temp1);
            
            if (n->child != NULL) {
                n->sibling = build(n, &temp2);
                n->child->sibling = n->sibling;
            }
            
           /*if (n->child != NULL && n->sibling != NULL) {
                token = getToken(&name);
                n->left->order = temp2;
            }*/
            
            if (n->child == NULL && n->sibling == NULL) *temp = n;
            else *temp = temp1;
        }
    }
    else if (token == CLOSEP) {
        n = NULL;
        *temp = NULL;
    }
    return n;
}
