#pragma once
#include <stdbool.h>
#include "state.h"
#include "node.h"

#define getBetaMain_unhic(hic, node) getBetaMain_unhic_impl(hic, node, 0, true)
#define getBetaMain(node) getBetaMain_unhic(hic, node)
#define updateBeta_unhic(hic, now, oNode) updateBeta_unhic_impl(hic, now, oNode, 0)
#define updateBeta(now, oNode) updateBeta_unhic(hic, now, oNode)
#define betaReduce(node) betaReduce_unhic(hic, node)

Node* getBetaMain_unhic_impl(Hic, Node* node, int lCnt, bool isHead);
void updateBeta_unhic_impl(Hic, Node* node, Node* oNode, int lCnt);
Node* betaReduce_unhic_impl(Hic, Node* node, bool* isRedex);
Node* betaReduce_unhic(Hic, Node* node);
