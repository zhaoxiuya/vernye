<<<<<<< HEAD
#include <stdbool.h>
#include <stddef.h>
#include "zxl.h"
#include "state.h"
#include "node.h"
#include "beta.h"

Node* getBetaMain_unhic_impl(Hic, Node* node, int lCnt, bool isHead){
    static Node* rNode = NULL;
    static int lMin = __INT_MAX__;
    if(isHead){
        ZXL_DEBUG("AT HEAD");
        lMin = __INT_MAX__;
        rNode = NULL;
    }
    ZXL_TRACE("getMain >>> %d %d", lCnt, isHead);
    if(node == NULL) ZXL_FATAL("NULL at wrong place");
    switch (node->kind){
    case VAR_NODE:
        break;
    case LAM_NODE:
        getBetaMain_unhic_impl(hic, node->sons[0], lCnt+1, false);
        break;
    case APP_NODE:
        getBetaMain_unhic_impl(hic, node->sons[0], lCnt, false);
        getBetaMain_unhic_impl(hic, node->sons[1], lCnt, false);
        ZXL_TRACE("cnt:%d min:%d", lCnt, lMin);
        if(node->sons[0]->kind == LAM_NODE){
            if(lCnt < lMin){
                ZXL_DEBUG("여기이써요!!!!");
                // printNode(node->sons[1]);
                lMin = lCnt;
                rNode = node;
            }
        }
        break;
    case OOO_NODE:
        ZXL_DEBUG("Empty Node Found!");
        break;
    default: ZXL_FATAL("Unexpected node kind %d", node->kind);
    }
    return rNode;
}

void updateBeta_unhic_impl(Hic, Node* node, Node* oNode, int lCnt){
    if(node == NULL || oNode == NULL) ZXL_FATAL("NULL at wrong place");
    switch (node->kind){
    case VAR_NODE:
        if(lCnt == node->value){
            Node* nNode = copyNode(oNode);
            moveNode(node, nNode);
        }
        else if(lCnt < node->value) node->value--;
        break;
    case LAM_NODE:
        updateBeta_unhic_impl(hic, node->sons[0], oNode, lCnt+1);
    break;
    case APP_NODE:
        updateBeta_unhic_impl(hic, node->sons[0], oNode, lCnt);
        updateBeta_unhic_impl(hic, node->sons[1], oNode, lCnt);
        break;
    case OOO_NODE:
        ZXL_DEBUG("Empty Node Found!");
        break;
    default: ZXL_FATAL("Unexpected node kind %d", node->kind);
    }
}

Node* betaReduce_unhic_impl(Hic, Node* node, bool* isRedex){
    Node* rootNode = L(node);
    ZXL_DEBUG("finding time!");
    Node* cNode = getBetaMain(rootNode);
    // printNode(cNode->sons[1]);
    if(cNode == NULL){
        ZXL_DEBUG("END!");
        *isRedex = true;
        return rootNode->sons[0];
    }
    Node* lNode = cNode->sons[0];
    Node* rNode = cNode->sons[1];
    Node* jNode = lNode->sons[0];
    ZXL_DEBUG("update time!");
    if(rNode == NULL) ZXL_WARN("우측 공석");
    if(lNode == NULL) ZXL_WARN("좌측 공석");
    updateBeta(jNode, rNode);
    moveNode(cNode, jNode);
    node = rootNode->sons[0];
    return node;
}
Node* betaReduce_unhic(Hic, Node* node){
    State* innerState = newState();
    Node* inNode = copyNode_unhic(innerState, node);
    bool isRedex = false;
    while(!isRedex){
        printNode(inNode);
        betaReduce_unhic_impl(innerState, inNode, &isRedex);
    }
    Node* outNode = copyNode_unhic(hic, inNode);
    delState_unhic(innerState);
    return outNode;
=======
#include <stdlib.h>
#include "type.h"
#include "node.h"
#include "beta.h"

void get_redex_node(Node *node, Node **redex) {
    Node *left, *right;
    if (node == NULL || *redex != NULL) return;
    left = node->child[0];
    right = node->child[1];
    if (node->type == APPLICATION_NODE) {
        if(left != NULL && left->type==ABSTRACTION_NODE){
            *redex=node;
            return;
        }
    }
    get_redex_node(left, redex);
    if (*redex != NULL) return;
    get_redex_node(right, redex);
}

void get_variable_nodes(Node *node, Node ***variables, i32* variables_size, i32 depth) {
    if (node == NULL) return;
    if (node->type == VARIABLE_NODE && node->value == depth) {
        if (*variables_size == 0) *variables=(Node**)malloc(sizeof(Node*));
        else *variables=(Node**)realloc(*variables, sizeof(Node*)*(*variables_size+1));
        (*variables)[*variables_size]=node;
        (*variables_size)++;
    }
    if (node->type == ABSTRACTION_NODE) depth++;
    for (usize i=0; i<2; i++) {
        if (node->child[i] == NULL) continue;
        get_variable_nodes(node->child[i], variables, variables_size, depth);
    }
}

void fix_node_value(Node *node, i32 var_depth, i32 depth) {
    if (node == NULL) return;
    if (node->type == VARIABLE_NODE) {
        if (depth < node->value) {
            node->value += var_depth;
        }
        return;
    }
    if (node->type == ABSTRACTION_NODE) depth++;
    for (usize i=0; i<2; i++) {
        if (node->child[i] == NULL) continue;
        fix_node_value(node->child[i], var_depth, depth);
    }
}

i32 beta_reduce(Node *root) {
    Node *redex=NULL, *oper=NULL, *src=NULL, *dest=NULL, *tmp=NULL;
    Node **variables=NULL;
    i32 variables_size=0;
    get_redex_node(root, &redex);
    if (redex==NULL) return 1;
    oper = redex->child[0];
    dest = oper->child[0];
    src = redex->child[1];
    get_variable_nodes(dest, &variables, &variables_size, 0);
    for (usize i=0; i<variables_size; i++) {
        tmp = copy_node(src);
        fix_node_value(tmp, variables[i]->value, -1);
        *variables[i] = steal_node(&tmp);
    }
    fix_node_value(dest, -1, 0);
    free(variables);
    redex->child[1] = NULL;
    free_node(&src);
    *redex = steal_node(&dest);
    oper->child[0] = NULL;
    free_node(&oper);
    return 0;
>>>>>>> master
}
