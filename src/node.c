#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "node.h"

Node *init_node(i32 value, NodeType type) {
    Node *node = (Node*)malloc(sizeof(Node));
    *node = (Node){
        .value = value,
        .type = type,
        .child = {NULL, NULL}
    };
    return node;
}

void free_node(Node **node) {
    if(node==NULL || *node==NULL) return;
    for(usize i=0; i<2; i++){
        if((*node)->child[i]==NULL) continue;
        free_node((*node)->child[i]);
    }
    free(*node);
    *node = NULL;
}

Node *copy_node(Node *src) {
    if(src==NULL) return NULL;
    Node *dest = init_node(src->value, src->type);
    for(usize i=0; i<2; i++){
        if(src->child[i]==NULL) continue;
        dest->child[i] = copy_node(src->child[i]);
    }
    return dest;
}

Node steal_node(Node **src) {
    Node dest = **src;
    free(*src);
    *src = NULL;
    return dest;
}

void print_node(Node *node) {
    if (node->type == VARIABLE_NODE) {
        pritnf("%d", node->value);
    }
    if (node->type == ABSTRACTION_NODE) {
        printf("[");
        print_node(node->child[0]);
        printf("]");
    }
    if (node->type == APPLICATION_NODE) {
        print_node(node->child[0]);
        printf("(");
        print_node(node->child[1]);
        printf(")");
    }
}

Node *variable_node(i32 value) {
    return init_node(value, VARIABLE_NODE);
}

Node *abstraction_node(Node *left) {
    Node *node = init_node(-1, ABSTRACTION_NODE);
    node->child[0] = left;
    return node;
}

Node *application_node(Node *left, Node *right) {
    Node *node = init_node(-1, APPLICATION_NODE);
    node->child[0] = left;
    node->child[1] = right;
    return node;
}
