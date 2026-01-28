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
}
