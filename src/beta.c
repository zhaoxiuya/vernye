#include <stdlib.h>
#include "zxl.h"
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
        else {
            *variables=(Node**)realloc(*variables, sizeof(Node*)*(*variables_size+1));
            if (*variables == NULL) zxl_error("realloc failed");
        }
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
    if(variables != NULL) {
        for (usize i=0; i<variables_size; i++) {
            tmp = copy_node(src);
            fix_node_value(tmp, variables[i]->value, -1);
            *variables[i] = steal_node(&tmp);
        }
        free(variables);
    }
    fix_node_value(dest, -1, 0);
    redex->child[1] = NULL;
    free_node(&src);
    *redex = steal_node(&dest);
    oper->child[0] = NULL;
    free_node(&oper);
    return 0;
}
