#ifndef IAImageProgram_h
#define IAImageProgram_h

#include "IAProgram.h"

typedef struct{
    //@extend
    IAProgram program;
    //@get
    GLint positionLocation;
    //@get
    GLint texturePositionLocation;
    //@get
    GLint leftTopWidthHeight;
    //@get
    GLint multiplicatorLocation;
    //@get
    GLint textureSampler2DLocation;
    IANotificationDelegate linkingCompleteDelegate;
} IAImageProgram;


void IAImageProgram_init(IAImageProgram *);

void IAImageProgram_deinit(IAImageProgram *);

#include "IAImageProgram+Generated.h"

#endif
