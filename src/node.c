#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        free_node(&((*node)->child[i]));
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

static u8 *my_strdup(const u8 *s) {
    u8 *ret = malloc(strlen(s)+1);
    if (ret == NULL) return NULL;
    return memcpy(ret, s, strlen(s)+1);
}

const u8 *node_to_str(Node *node) {
    u8 str[1024], *left, *right;
    if (node->type == VARIABLE_NODE) {
        snprintf(str, sizeof(str), "%d", node->value);
        return (u8*)my_strdup(str);
    }
    if (node->type == ABSTRACTION_NODE) {
        left = node_to_str(node->child[0]);
        snprintf(str, sizeof(str), "{\"left\":%s}", left);
        free(left);
        return (u8*)my_strdup(str);
    }
    if (node->type == APPLICATION_NODE) {
        left = node_to_str(node->child[0]);
        right = node_to_str(node->child[1]);
        snprintf(str, sizeof(str), "{\"left\":%s,\"right\":%s}", left, right);
        free(left);
        free(right);
        return (u8*)my_strdup(str);
    }
    return (u8*)my_strdup("");;
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
