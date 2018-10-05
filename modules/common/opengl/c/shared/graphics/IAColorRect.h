#ifndef IAColorRect_h
#define IAColorRect_h

#include "IASize.h"
#include "IARect.h"
#include "IAColor.h"
#include "IAGraphicRect.h"
#include "IAArrayBuffer.h"


typedef struct{
    //@extend
    IAGraphicRect graphicRect;
    IAArrayBuffer arrayBuffer;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
} IAColorRect;


void IAColorRect_init(IAColorRect *, IAColor color);

void IAColorRect_setColor(IAColorRect *, IAColor color);
void IAColorRect_setRed(IAColorRect *, int red);
void IAColorRect_setGreen(IAColorRect *, int green);
void IAColorRect_setBlue(IAColorRect *, int blue);
void IAColorRect_setAlpha(IAColorRect *, int alpha);

void IAColorRect_deinit(IAColorRect *);

#include "IAColorRect+Generated.h"

#endif
