#pragma once
#include "type.h"
#include "node.h"

void get_redex_node(Node *node, Node **redex);
void get_variable_nodes(Node *node, Node ***variables, usize* variables_size, i32 depth);
void fix_node_value(Node *node, i32 var_depth, i32 depth);
i32 beta_reduce(Node *root);
