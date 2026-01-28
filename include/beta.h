#pragma once
<<<<<<< HEAD
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
=======
#include "type.h"
#include "node.h"

void get_redex_node(Node *node, Node **redex);
void get_variable_nodes(Node *node, Node ***variables, i32* variables_size, i32 depth);
void fix_node_value(Node *node, i32 var_depth, i32 depth);
i32 beta_reduce(Node *root);
>>>>>>> master
