//
//  IADrawableRect.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 11.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineiOS_IADrawableRect_h
#define ImpsEngineiOS_IADrawableRect_h

#include <stdbool.h>

#include "IADrawable.h"
#include "IAPoint.h"
#include "IASize.h"
#include "IARect.h"

typedef struct IADrawableRect IADrawableRect;

struct IADrawableRect{
    //@extend
    IADrawable drawable;
    void (*setRect)(IADrawableRect *, IARect);
    IARect rect;
};


void IADrawableRect_make(IADrawableRect *, void (*drawFunction)(const IADrawable*), void (*setRect)(IADrawableRect *, IARect));
void IADrawableRect_makeCopy(IADrawableRect *, const IADrawableRect * drawableRectToCopy);

void IADrawableRect_setLeftTopPoint(IADrawableRect *, IAPoint point);
void IADrawableRect_setCenterPoint(IADrawableRect *, IAPoint point);
void IADrawableRect_setSize(IADrawableRect *, IASize size);
void IADrawableRect_setRect(IADrawableRect *, IARect rect);
void IADrawableRect_setLeftTopRightBottom(IADrawableRect *, float left, float top, float right, float bottom);

IAPoint IADrawableRect_getLeftTopPoint(const IADrawableRect *);
IAPoint IADrawableRect_getCenterPoint(const IADrawableRect *);
float IADrawableRect_getWidth(const IADrawableRect *);
float IADrawableRect_getHeight(const IADrawableRect *);
IASize IADrawableRect_getSize(const IADrawableRect *);
IARect IADrawableRect_getRect(const IADrawableRect *);

#include "IADrawableRect+Generated.h"

#endif
