#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zxl.h"
#include "node.c"
#include "beta.c"

#define LET(NAME, EXPR)\
Node NAME(){return EXPR;}

Node Number_impl(int n){
    if (n == 0){
        return V(0);
    }
    return A(V(1), Number_impl(n - 1));
}
Node Number(int n) { return L(L(Number_impl(n))); }
LET(Succ, L(L(L(A(V(1), A( A(V(2), V(1)), V(0)))))))
LET(Add, L(L(L(L(A(A(V(2), V(1)), A(A(V(3),V(1)),V(0))))))))
LET(Mul, L(L(L(L(A(A(V(2), A(V(3), V(1))), V(0)))))))
LET(False, L(L(V(0))))
LET(True, L(L(V(1))))
LET(Not, L(A(A(V(0), False()), True())))
LET(And, L(L(A(A(V(1), V(0)), V(1)))))

int main(void){
    ZXL_INIT(ZXLV_TRACE);
    ZXL_INIT(ZXLV_FATAL);
    // Node test = A(A(Ycb() ,L(L(A(A(A(isZero(), V(0)), Number(1)), A(A(Mul(), V(0)), A(V(1), A(Pred(), V(0)))))))), Number(3));
    // Node test = A(A(Mul(), Number(3)), Number(2));
    Node test = A(L(L(V(1))), L(V(0)));
    test = betaReduce(test);
    printNode(test);
    return 0;
}