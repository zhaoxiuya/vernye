#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zxl.h"
#include "node.c"
#define oo __INT_MAX__

// Node findBetaMain_impl_pre(Node now, int lCnt, int aCnt, bool isHead){
//     // 람다 카운트, 적용 카운트
//     static int lMin = oo, aMax = 0;
//     // 반환 값
//     static Node ret = NULL;
//     // 최초 호출시 초기화
//     if(isHead){
//         ZXL_DEBUG("AT HEAD");
//         lMin = oo;
//         aMax = -oo;
//         ret = NULL;
//     }
//     if(now==NULL) ZXL_ERROR("now is NULL");
//     // 이 아래 볼거 없을때
//     if(lMin < lCnt){
//         ZXL_DEBUG("Nothing to see");
//         return ret;
//     }
//     ZXL_TRACE("%d", now->sonNum);
//     switch (now->sonNum){
//     // 노드 끝!
//     case 0:
//         break;
//     // 람다 노드인 경우 람다값 증가 대입값 초기화
//     case 1:
//         findBetaMain_impl(now->sons[0], lCnt+1, 0, false);
//         break;
//     // 적용 노드인 경우 람다값 유지 대입값 증가
//     case 2: {
//         bool mainable = false;
//         // 내 왼쪽 자식이 람다일 경우 즉 적용 가능할 경우
//         ZXL_TRACE("FLG 2 lCnt : %d lMin %d", lCnt, lMin);
//         ZXL_TRACE("FLG 2 aCnt : %d aMax %d", aCnt, aMax);
//         ZXL_TRACE("MY SONS: L:%d R:%d", now->sons[0]->sonNum, now->sons[1]->sonNum);
//         if((now->sons[0]->sonNum)==1){
//             ZXL_TRACE("FLG 2-0");
//             // // 람다 카운트가 람다 최소와 같으면서 적용 카운트가 더 클 때
//             // if(lCnt == lMin){
//             //     ZXL_TRACE("SH 2-0-0");
//             //     if(aMax < aCnt){
//             //         ZXL_TRACE("SH 2-0-0-0");
//             //         mainable = true;
//             //     }
//             // }
//             // 람다 카운트가 람다 최소와 같을 때
//             if(lCnt < lMin && ret == NULL){
//                 ZXL_TRACE("SH 2-0-2");
//                 mainable = true;
//             }
//         }
//         // 결과 적용
//         if(mainable){
//             ZXL_DEBUG("AT MAINABLE");
//             lMin = lCnt;
//             aMax = aCnt;
//             ZXL_TRACE("FLG 2 lCnt : %d lMin %d", lCnt, lMin);
//             ZXL_TRACE("FLG 2 aCnt : %d aMax %d", aCnt, aMax);
//             ret = now;
//         }
//         findBetaMain_impl(now->sons[0], lCnt, aCnt+1, false);
//         findBetaMain_impl(now->sons[1], lCnt, aCnt+1, false);
//         break;
//     }
//     default: ZXL_ERROR("인덱스 누수 발생 %d", now->sonNum);
//     }
//     return ret;
// }
Node findBetaMain_impl(Node now, int lCnt, bool isHead){
    // 람다 카운트;
    static int lMin = oo;
    // 반환 값
    static Node ret = NULL;
    // 최초 호출시 초기화
    if(isHead){
        ZXL_DEBUG("AT HEAD");
        lMin = oo;
        ret = NULL;
    }
    if(now==NULL) ZXL_ERROR("now is NULL");

    ZXL_TRACE("%d", now->sonNum);
    switch (now->sonNum){
    // 노드 끝!
    case 0:
        break;
    // 람다 노드인 경우 람다값 증가 대입값 초기화
    case 1:
        findBetaMain_impl(now->sons[0], lCnt+1, false);
        break;
    // 적용 노드인 경우 람다값 유지 대입값 증가
    case 2: {
        // 아래부터 탐색
        findBetaMain_impl(now->sons[0], lCnt, false);
        findBetaMain_impl(now->sons[1], lCnt, false);
        
        ZXL_DEBUG("FLG 2 lCnt : %d lMin %d", lCnt, lMin);
        ZXL_DEBUG("MY SONS: L:%d R:%d", now->sons[0]->sonNum, now->sons[1]->sonNum);

        // 내 왼쪽 자식이 람다일 경우 즉 적용 가능할 경우
        if((now->sons[0]->sonNum)==1){
            if(lCnt < lMin){
                ZXL_DEBUG("AT MAINABLE");
                lMin = lCnt;
                ret = now;
                ZXL_DEBUG("FLG 2 lCnt : %d lMin %d", lCnt, lMin);
            }
        }
        break;
    }
    default: ZXL_ERROR("인덱스 누수 발생 %d", now->sonNum);
    }
    return ret;
}
Node findBetaMain(Node now){
    return findBetaMain_impl(now, 0, true);
}

int findBetaLeaf_impl(Node now, int lCnt, Node** logger, bool isHead){
    // 배열 크기
    static int size = 0;
    // 초기화
    if(isHead){
        ZXL_INFO("AT HEAD");
        size = 0;
        (*logger) = NULL;
    }
    if(now==NULL) ZXL_ERROR("now is NULL");
    ZXL_TRACE("%d", now->sonNum);
    switch (now->sonNum){
    case 0:
        // 람다 카운트가 value와 같다면 로거 확장, now를 기록
        if(now->value == lCnt){
            ZXL_DEBUG("EXTENDING: %d", size+1);
            size++;
            (*logger) = (Node*)realloc(*logger, size * sizeof(Node));
            if((*logger) == NULL) ZXL_FATAL("MEMORY BOOM");
            (*logger)[size-1] = now;
        }
        break;
    case 1: 
        // 아래 노드 탐색, 람다 카운트 증가
        findBetaLeaf_impl(now->sons[0], lCnt+1, logger, false);
        break;
    case 2:
        // 아래 노드 탐색
        findBetaLeaf_impl(now->sons[0], lCnt, logger, false);
        findBetaLeaf_impl(now->sons[1], lCnt, logger, false);
        break;
    default: ZXL_ERROR("인덱스 누수 발생 %d", now->sonNum);
    }
    return size;
}
int findBetaLeaf(Node lNode, Node** logger){
    Node llNode = lNode->sons[0];
    *logger = NULL;
    return findBetaLeaf_impl(llNode, 0, logger, true);
}

Node betaReduce_impl(Node now, bool *isRedex){
    // 절대 루트 노드 정의
    Node rootNode = makeNode(-1, 1, now, NULL);

    // 연산에 대한 중앙 노드 정의
    ZXL_INFO("Entering findBeataMain");
    Node cNode = findBetaMain(rootNode);

    // redex일때 돌아가기
    if(cNode == NULL){
        ZXL_INFO("IS_REDEX");
        free(rootNode);
        *isRedex = true;
        return now;
    }
    else *isRedex = false;
    
    // 피연산자 트리 && 연산자 노드
    Node lNode = cNode->sons[0];
    Node rNode = cNode->sons[1];

    // 피연산자 찾기
    Node* oprnds = NULL;
    ZXL_INFO("Entering findBetaLeaf");
    int size = findBetaLeaf(lNode, &oprnds);
    ZXL_DEBUG("oprnd size: %d", size);
    // 피연산자에 연산자 복사
    for(int i=0; i<size; i++){
        ZXL_TRACE("Copying... %d", i);
        Node nNode = copyNode(rNode);
        (*(oprnds[i])) = *nNode;
        free(nNode);
        nNode = NULL;
    }
    free(oprnds);

    // 중앙 노드를 피연산자 트리 루트의 자식으로 대체
    // l이 반드시 람다임 (조건상)
    Node llNode = lNode->sons[0];
    free(lNode);

    (*cNode) = (*llNode);
    free(llNode);
    llNode = NULL;

    now = rootNode->sons[0];
    free(rootNode);
    // 와! 버그의 원인 (아직 못 고침) [2025-08-19 22:36:25]
    // 응 고쳤어 ㅋㅋㅋㅋㅋ
    delNode(rNode);
    return now;
}
Node betaReduce(Node now){
    bool isRedex = false;
    Node newNode = copyNode(now);
    while(!isRedex){
        printNode(newNode);
        betaReduce_impl(newNode, &isRedex);
        ZXL_INFO("IN ITER");
    }
    return newNode;
}