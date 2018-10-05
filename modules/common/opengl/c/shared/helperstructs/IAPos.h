#ifndef IAPos_h
#define IAPos_h

#include <stdbool.h>

typedef struct{
    int x;
    int y;
} IAPos;

IAPos IAPos_make(int x, int y);

bool IAPos_areEqual(IAPos pos1, IAPos pos2);

#endif
