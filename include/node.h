#pragma once
<<<<<<< HEAD
#include <stdlib.h>
#include <stdarg.h>
#include "state.h"

#define newNode(v, n, l, r) newNode_unhic(hic, v, n, l, r)
#define V(n) newNode(n, VAR_NODE, NULL, NULL)
#define L(l) newNode(-1, LAM_NODE, l, NULL)
#define A(l, r) newNode(-1, APP_NODE, l, r)
#define P(n, ...) P_unhic(hic, (n), __VA_ARGS__)
#define delNode(node) delNode_unhic(hic, node)
#define copyNode(node) copyNode_unhic(hic, node)
#define moveNode(nNode, oNode) moveNode_unhic(hic, nNode, oNode)

typedef enum {
    VAR_NODE, // 변수
    LAM_NODE, // 람다
    APP_NODE, // 적용
    ERR_NODE, // 에러 (예외)
    OOO_NODE, // 빈 노드
} NodeKind;

typedef struct Node {
    int value;
    NodeKind kind;
    struct Node* sons[2];
} Node;

void printNode_impl1(char ch, int color);
void printNode_impl0(Node* node);
void printNode(Node* node);
Node* newNode_unhic(Hic, int value, NodeKind kind, Node* lNode, Node* rNode);
Node* P_unhic(Hic, size_t n, ...);
void delNode_unhic(Hic, Node* node);
Node* copyNode_unhic(Hic, Node* node);
Node* moveNode_unhic(Hic, Node* nNode, Node* oNode);
=======
#include "type.h"

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
static u8 *my_strdup(const u8 *s);
u8 *node_to_str(Node *node);
Node *variable_node(i32 value);
Node *abstraction_node(Node *left);
Node *application_node(Node *left, Node *right);
>>>>>>> master
