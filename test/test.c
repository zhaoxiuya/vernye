#include <stdio.h>
#include "type.h"
#include "node.h"
#include "beta.h"

int main(void){
    Node *test;
    test =
        application_node(
            abstraction_node(
                application_node(
                    application_node(
                        variable_node(0),
                        abstraction_node(
                            abstraction_node(
                                variable_node(0)
                            )
                        )
                    ),
                    abstraction_node(
                        abstraction_node(
                            variable_node(1)
                        )
                    )
                )
            ),
            abstraction_node(
                abstraction_node(
                    variable_node(1)
                )
            )
        );
    printf("%s\n", node_to_str(test));
    while(!beta_reduce(test)){
        printf("%s\n", node_to_str(test));
    }
    return 0;
}
