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
            n->post = 1;
            n->sibling = NULL;
            n->name = name;
            n->left = build(n, &temp1);
            
            if (n->left != NULL) {
                n->right = build(n, &temp2);
                n->left->sibling = n->right;
            }
            
            if (n->left != NULL && n->right != NULL) {
                token = getToken(&name);
                n->left->order = temp2;
            }
            
            if (n->left == NULL && n->right == NULL) *temp = n;
            else *temp = temp1;
        }
    }
    else if (token == CLOSEP) {
        n = NULL;
        *temp = NULL;
    }
    return n;
}
