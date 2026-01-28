typedef enum {
    EMPTY_NODE,
    ERROR_NODE,
    VARIABLE_NODE,
    ABSTRACTION_NODE,
    APPLICATION_NODE
} NodeType;

typedef struct Node {
    i32 value;
    NodeType type;
    Node *child[2];
} Node;

Node *init_node(i32 value, NodeType type) {
    Node *node = (Node*)malloc(sizeof(Node));
    *node = (Node){
        .value = value,
        .type = type,
        .child = {NULL, NULL}
    };
    return node;
}

void free_node(Node **node) {
    if(node==NULL) return;
    for(usize i=0; i<2; i++){
        if(node->child[i]==NULL) continue;
        free_node(node->child[i]);
    }
    free(node);
    node = NULL;
}

Node *copy_node(Node *src) {
    if(src==NULL) return NULL;
    Node *dest = init_node(src->value, src->type);
    for(usize i=0; i<2; i++){
        if(src->child[i]==NULL) continue;
        dest->child[i] = copy_node(src->child[i]);
    }
    return dest;
}

Node *move_node(Node **src) {
    Node *dest = *src;
    *src = NULL;
    return dest;
}
