#pragma once
#include "type.h"
#include "zxl.h"

typedef enum {
    ERROR_NODE=-2,
    EMPTY_NODE=-1,
    VARIABLE_NODE=0,
    ABSTRACTION_NODE=1,
    APPLICATION_NODE=2
} NodeType;

typedef struct Node {
    NodeType type;
    i32 value;
    struct Node *child[2];
} Node;

Node *init_node(i32 value, NodeType type);
void free_node(Node **node);
Node *copy_node(Node *src);
Node steal_node(Node **src);
const char *node_to_str(Node *node);
Node *variable_node(i32 value);
Node *abstraction_node(Node *left);
Node *application_node(Node *left, Node *right);
