//
//  IAFontInformationAttributes.h
//  Hit Verto
//
//  Created by Konstantin Merker on 30/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAFontInformationAttributes_h
#define Hit_Verto_IAFontInformationAttributes_h

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
