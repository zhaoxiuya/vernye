#include <stdlib.h>
#include <stddef.h>
#include "zxl.h"
#include "state.h"

State* newState(){
    // malloc 허용됨
    Hic = (State*)malloc(sizeof(State));
    hic->now = NULL;
    hic->prev = NULL;
    return hic;
}

void delState_unhic(Hic){
    while(hic){
        State* prev = hic->prev;
        if(hic->now != NULL) free(hic->now);
        free(hic);
        hic = prev;
    }
    hic = NULL;
    return;
};

void* allocState_unhic(Hic, size_t cap){
    State* next = newState();
    next->prev = hic;
    hic = next;
    // malloc 허용됨
    next->now = malloc(cap);
    return next->now;
}