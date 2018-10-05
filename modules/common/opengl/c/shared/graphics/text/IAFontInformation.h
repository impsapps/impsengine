#ifndef IAFontInformation_h
#define IAFontInformation_h

#include "IAFontInformationAttributes.h"
#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    //@get
    float fontSize;
    //@get
    float ascent;
    //@get
    float descent;
    //@get
    float lineHeight;
} IAFontInformation;


void IAFontInformation_make(IAFontInformation *, const IAFontInformationAttributes * attributes);

#include "IAFontInformation+Generated.h"

#endif
