#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "zxl.h"
#include "state.h"
#include "node.h"

void printNode_impl1(char ch, int color){
    printf("\033[%dm%c\033[0m", color, ch);
}
void printNode_impl0(Node* node){
    static int colorTb[] = {31, 33, 32, 36, 34, 35};
    static char exprTb[] = "<|>";
    static int aCnt = 0, lCnt = 0;
    int color;
    if(node == NULL) ZXL_ERROR("now is NULL");
    switch (node->kind){
    case VAR_NODE:
        printf("\033[%dm%d\033[0m", color, node->value);
        break;
    case LAM_NODE:
        color = colorTb[(lCnt) % 6];
        lCnt++;
        printNode_impl1(exprTb[0], color);
        printNode_impl0(node->sons[0]);
        printNode_impl1(exprTb[2], color);
        lCnt--;
        break;
    case APP_NODE:
        color = 39;
        aCnt++;
        printNode_impl1(exprTb[0], color);
        printNode_impl0(node->sons[0]);
        printNode_impl1(exprTb[2], color);
        printNode_impl1(exprTb[0], color);
        printNode_impl0(node->sons[1]);
        printNode_impl1(exprTb[2], color);
        aCnt--;
        break;
    default: ZXL_ERROR("인덱스 누수 발생 %d", node->kind);
    }
}
void printNode(Node* node){
    printNode_impl0(node);
    printf("\n");
    fflush(stdout);
}

Node* newNode_unhic(Hic, int value, NodeKind kind, Node* lNode, Node* rNode){
    Node* node = (Node*)allocState(sizeof(Node));
    node->value = value;
    node->kind = kind;
    node->sons[0] = lNode;
    node->sons[1] = rNode;
    return node;
}
Node* P_unhic(Hic, size_t n, ...){
    va_list ap; va_start(ap, n);
    Node* acc = va_arg(ap, Node*);
    for(size_t i=1; i<n; i++){
        Node* x = va_arg(ap, Node*);
        acc = A(acc, x);
    }
    va_end(ap);
    return acc;
}

void delNode_unhic(Hic, Node* node){
    node->value = -1;
    node->kind = OOO_NODE;
    node->sons[0] = NULL;
    node->sons[1] = NULL;
    node = NULL;
}

Node* copyNode_unhic(Hic, Node* node){
    if(node == NULL) ZXL_FATAL("NULL at wrong place");
    Node* lNode = NULL;
    Node* rNode = NULL;
    Node* nNode = NULL;
    switch (node->kind){
    case VAR_NODE:
        break;
    case LAM_NODE:
        lNode = copyNode(node->sons[0]);
        break;
    case APP_NODE:
        lNode = copyNode(node->sons[0]);
        rNode = copyNode(node->sons[1]);
        break;
    case OOO_NODE:
        ZXL_DEBUG("Empty Node Found!");
        break;
    default: ZXL_FATAL("Unexpected node kind %d", node->kind);
    }
    nNode = newNode(node->value, node->kind, lNode, rNode);
    return nNode;
}

Node* moveNode_unhic(Hic, Node* nNode, Node* oNode){
    if(oNode == NULL || nNode == NULL) ZXL_FATAL("NULL at wrong place");
    *nNode = *oNode;
    delNode(oNode);
    return nNode;
}