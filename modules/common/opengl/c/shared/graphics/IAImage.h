//
//  IAImage.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 16.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineiOS_IAImage_h
#define ImpsEngineiOS_IAImage_h

#include "IAGraphicRect.h"
#include "IAImageAttributes.h"
#include "IAArrayBuffer.h"
#include "IATextureSelectionData.h"
#include "IAColor.h"
#include "IAImageProgram.h"
#include "IATrimmedRect.h"

typedef struct IAImage IAImage;


/**
 * Image class.
 */
struct IAImage{
    //@extend
    IAGraphicRect graphicRect;
    
    IATexture * texture;
    IAArrayBuffer arrayBuffer;
    
    IATrimmedRect trimmedRect;
    bool hasTrimmedRect;
    
    int alpha;
    IAColor overlayingColor;
    
    IASize originalSize;
};


void IAImage_init(IAImage *, const IAImageAttributes * attributes);
void IAImage_initCopy(IAImage *, const IAImage * imageToCopy);

void IAImage_setAlpha(IAImage *, int alpha);

void IAImage_setOverlayingColor(IAImage *, IAColor overlayingColor);

void IAImage_setSizeWithFixedHeight(IAImage *, float fixedHeight);
void IAImage_setSizeWithFixedWidth(IAImage *, float fixedWidth);

void IAImage_flipHorizontally(IAImage *);
void IAImage_flipVertically(IAImage *);

IASize IAImage_getOriginalSize(IAImage *);
IATexture * IAImage_getTexture(IAImage *);
IARect IAImage_getTrimmedRect(IAImage *);

void IAImage_deinit(IAImage *);


#include "IAImage+Generated.h"

#endif
