#ifndef IAColorRectProgram_h
#define IAColorRectProgram_h

#include "IAProgram.h"

typedef struct{
    //@extend
    IAProgram program;
    //@get
    GLuint positionLocation;
    //@get
    GLuint leftTopWidthHeight;
    //@get
    GLuint colorLocation;
    IANotificationDelegate linkingCompleteDelegate;
} IAColorRectProgram;


void IAColorRectProgram_init(IAColorRectProgram *);

void IAColorRectProgram_deinit(IAColorRectProgram *);

#include "IAColorRectProgram+Generated.h"

#endif
