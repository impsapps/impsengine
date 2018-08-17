//
//  IAFontInformation.h
//  Hit Verto
//
//  Created by Konstantin Merker on 30/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAFontInformation_h
#define Hit_Verto_IAFontInformation_h

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
