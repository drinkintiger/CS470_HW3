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
Node ** nodearr;
int currentpos = 0, node_arr_length = 1;
void * find_next (void *param);
void * preorder_num (void *param);
pthread_barrier_t barrier;

int main(int argc, char * argv[]) {
    Node *temp;
    pthread_t *node_threads = NULL;

    temp = buildNode(NULL, "(A(B(C(D))(E(F)(G)))(H(I)(J)))", NULL);
    
    pthread_barrier_init(&barrier, NULL, node_arr_length - 1);
    node_threads = malloc(sizeof(pthread_t) * node_arr_length);

    for (int i = 0; i < node_arr_length - 1; i++) {
        pthread_create(&(node_threads[i]), NULL, find_next, (void*) nodearr[i]);
    }

    for(int i = 0; i < node_arr_length; ++i ) {
        pthread_join(node_threads[i], NULL);
    }
    
    for (int i = 0; i < node_arr_length - 1; i++) {
        pthread_create(&(node_threads[i]), NULL, preorder_num, (void*) nodearr[i]);
    }
    
    for(int i = 0; i < node_arr_length; ++i ) {
        pthread_join(node_threads[i], NULL);
    }
    
    for (int i = 0; i < node_arr_length - 1; i++) {
        printf("My name is: %s\n", nodearr[i]->name);
        printf("My preorder number is: %d\n", nodearr[i]->pre);
    }
    return 0;
}

void * find_next (void * param) {
    Node * me = (Node *) param;
    me->next = NULL;
    Node * temp;
    
    if (me->child != NULL){
        me->next = me->child;
    }
    else if (me->sibling != NULL){
        me->next = me->sibling;
    }
    else {
        temp = me->parent;
        while (temp != NULL) {
            if (temp->sibling != NULL) {
                me->next = temp->sibling;
                break;
            }
            else temp = temp->parent;
        }
    }
    
    return NULL;
}

void * preorder_num (void *param) {
    Node *temp = (Node *) param;
    Node *n;
    int d;
        if (temp->next != NULL ){
            n = temp->next->next;
            d = temp->pre + temp->next->pre;
        }
        pthread_barrier_wait(&barrier);
        if (temp->next != NULL) {
            temp->pre = d;
            temp->next = n;
        }
        pthread_barrier_wait(&barrier);

    temp->pre = node_arr_length - temp->pre;
    
    return NULL;
}

Node *buildNode (Node * parent, char * node, char * sibling) {
    int start = -1, end, parans = -1, count = 0, length = 0; // if parans = 1 it's closed parenthese, parans = 0 it's open
    Node * current = malloc(sizeof(Node));
    current->child = NULL;
    current->sibling = NULL;
    current->pre = 1;
    char * temp;
    char * first;
    char * rest;

    length = strlen(node);
    
    nodearr = realloc(nodearr, sizeof(Node *) * node_arr_length);
    nodearr[currentpos] = current;
    currentpos += 1;
    node_arr_length += 1;
    
    for (int i = 0; i < length; ++i) {
        if (node[i] == '(') {
            start = i;
            break;
        }
    }
    for (int i = start + 1; i < length; ++i) {
        if (node[i] == ')') {
            parans = 1;
            end = i;
            break;
        }
        else if (node[i] == '(') {
            parans = 0;
            end = i;
            break;
        }
    }
    
    current->name = substring(&node[start + 1], end - 1);
    
    if (sibling != NULL) {
        split (sibling, &first, &rest);
        current->sibling = buildNode(parent, first, rest);
    }
    
    if ( parans == 0) {
        for (int i = length; i > 0; --i) {
            if (node [i] == ')') {
                count += 1;
                if (count == 2) {
                    count = i;
                    break;
                }
            }
        }
        temp = substring (&node[end], count - end + 1);
        split (temp, &first, &rest);
        current->child = buildNode(current, first, rest);
    }
    
    printf ("My node is : %s\n", current -> name);
    if (current-> parent != NULL) printf ("My parent is : %s\n", current -> parent -> name);
    if (current-> child != NULL) printf ("The child is : %s\n", current -> child -> name);
    if (current->sibling != NULL) printf ("My sibling is : %s\n", current->sibling->name);
    printf("\n");
    return current;
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
