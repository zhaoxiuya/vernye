#include <stdio.h>
#include "beta.h"
#include "node.h"

int main(void){
    Node *test =
    application_node(
        abstraction_node(
            application_node(
                variable_node(0),
                variable_node(0)
            )
        ),
        abstraction_node(
            application_node(
                variable_node(0),
                variable_node(0)
            )
        )
    );

    printf("%s\n", node_to_str(test));
    while(!beta_reduce(test)){
        printf("%s\n", node_to_str(test));
    }
    return 0;
}
