#include "node.h"
#include "type.h"

Node *get_redex_node(Node *node) {

}

Node **get_variable_nodes(Node *node) {

}

void fix_node_value(Node *node, i32 var_depth, i32 depth) {
    if (node == NULL) return;
    if (node->type == VARIABLE_NODE) {

    }
    if (node->type == ABSTRACTION_NODE) depth++;
    for (usize i=0; i<2; i++) {
        if (node->child[i] == NULL) continue;
        fix_node_value(node->child[i], var_depth, depth);
    }
}

i32 beta_reduce(Node *root) {
    Node *redex=NULL, *oper=NULL, *src=NULL, *dest=NULL, *tmp=NULL;
    Node **var_nodes=NULL;
    redex = get_redex_node(root);
    if (redex==NULL) return 1;
    oper = redex->child[0];
    dest = oper->child[0];
    src = redex->child[1];
    var_nodes = get_variable_nodes(oper);
    for (usize i=0; var_nodes[i]!=NULL; i++) {
        tmp = copy_node(src);
        fix_node_value(tmp, var_nodes[i]->value, 0);
        *var_nodes[i] = steal_node(&tmp);
    }
    redex->child[1] = NULL;
    free_node(&src);
    *redex = steal_node(&dest);
    oper->child[0] = NULL;
    free_node(&oper);
    return 0;
}
