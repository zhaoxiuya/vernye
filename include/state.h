#pragma once

#define Hic State* hic
#define delState() delState_unhic(hic)
#define allocState(cap) allocState_unhic(hic, cap);

typedef struct State{
    void* now;
    struct State* prev;
} State;

State* newState();
void delState_unhic(Hic);
void* allocState_unhic(Hic, size_t cap);