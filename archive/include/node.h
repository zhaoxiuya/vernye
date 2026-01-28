#pragma once
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
