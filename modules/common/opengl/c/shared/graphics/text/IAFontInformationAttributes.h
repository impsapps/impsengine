#ifndef IAFontInformationAttributes_h
#define IAFontInformationAttributes_h

typedef struct{
    //@set+get
    float fontSize;
    //@set+get
    float ascent;
    //@set+get
    float descent;
    //@set+get
    float lineHeight;
} IAFontInformationAttributes;


void IAFontInformationAttributes_make(IAFontInformationAttributes *);

#include "IAFontInformationAttributes+Generated.h"

#endif
