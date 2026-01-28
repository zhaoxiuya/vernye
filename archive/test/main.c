#include <stdio.h>
#include "zxl.h"
#include "beta.h"

#define oo __INT_MAX__

#define False L(L(V(0)))
#define True L(L(V(1)))

int main(void){
    ZXL_INIT(ZXLV_FATAL);
    Hic = newState();

    Node* in = P(2, L(P(3, V(0), False, True)), True);
    printf("INPUT : ");
    printNode(in);
    printf("================================================================\n");
    Node* out = betaReduce(in);
    printf("================================================================\n");
    printf("OUTPUT: ");
    printNode(out);

    delState();
    return 0;
}