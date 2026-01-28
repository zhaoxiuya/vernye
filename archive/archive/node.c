#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "zxl.h"

typedef struct Node_impl{
    int value, sonNum;
    struct Node_impl* sons[2];
} Node_impl;
typedef Node_impl* Node;

// 기본 생성자
Node makeNode(int value, int sonNUm, Node a, Node b){
    Node now = (Node)malloc(sizeof(Node_impl));
    now->value = value;
    now->sonNum = sonNUm;
    now->sons[0] = a;
    now->sons[1] = b;
    return now;
}

// 수정자
Node changeNode(Node now, int value, int sonNUm, Node a, Node b){
    now->value = value;
    now->sonNum = sonNUm;
    now->sons[0] = a;
    now->sons[1] = b;
    return now;
}

Node A(Node a, Node b) { return makeNode(-1, 2, a, b); }
Node L(Node a) { return makeNode(-1, 1, a, NULL); }
Node V(int value) { return makeNode(value, 0, NULL, NULL); }

// 복사 생성자
Node copyNode(Node oldNode){
    Node newNode;
    switch (oldNode->sonNum){
    case 0:
        newNode = V(oldNode->value);
        break;
    case 1:{
        Node lNode = copyNode(oldNode->sons[0]);
        newNode = L(lNode);
        break;
    }
    case 2:{
        Node lNode = copyNode(oldNode->sons[0]);
        Node rNode = copyNode(oldNode->sons[1]);
        newNode = A(lNode, rNode);
        break;
    }
    default: ZXL_ERROR("인덱스 누수 발생 %d", oldNode->sonNum);
    }
    return newNode;
}

// 소멸자
void delNode(Node oldNode){
    ZXL_DEBUG("IN delnode");
    ZXL_DEBUG("%d", oldNode->sonNum);
    switch (oldNode->sonNum){
    case 0: 
        break;
    case 1:
        delNode(oldNode->sons[0]);
        break;
    case 2:
        delNode(oldNode->sons[0]);
        delNode(oldNode->sons[1]);
        break;
    default: ZXL_ERROR("인덱스 누수 발생 %d", oldNode->sonNum);
    }
    free(oldNode);
}

void printNode_impl1(char ch, int color){
    printf("\033[%dm%c\033[0m", color, ch);
}
void printNode_impl0(Node now){
    static int colorTb[] = {31, 33, 32, 36, 34, 35};
    static char exprTb[] = "<|>";
    static int aCnt = 0, lCnt = 0;
    int color;
    if(now==NULL) ZXL_ERROR("now is NULL");
    switch (now->sonNum){
    case 0:
        color = colorTb[((lCnt - now->value - 1) + 6) % 6];
        // for (int i = 0; i <= now->value; i++){
        //     printNode_impl1(exprTb[1], color);
        // }
        printf("\033[%dm%d\033[0m", color, now->value);
        break;
    case 1:
        color = colorTb[(lCnt) % 6];
        lCnt++;
        printNode_impl1(exprTb[0], color);
        printNode_impl0(now->sons[0]);
        printNode_impl1(exprTb[2], color);
        lCnt--;
        break;
    case 2:
        // color = colorTb[(aCnt * 2 + 1) % 6];
        color = 39;
        aCnt++;
        printNode_impl1(exprTb[0], color);
        printNode_impl0(now->sons[0]);
        printNode_impl1(exprTb[2], color);
        printNode_impl1(exprTb[0], color);
        printNode_impl0(now->sons[1]);
        printNode_impl1(exprTb[2], color);
        aCnt--;
        break;
    default: ZXL_ERROR("인덱스 누수 발생 %d", now->sonNum);
    }
}
void printNode(Node now){
    printNode_impl0(now);
    printf("\n");
    fflush(stdout);
}