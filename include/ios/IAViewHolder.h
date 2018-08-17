//
//  IAViewHolder.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAViewHolder_h
#define ImpsEngineiOS_IAViewHolder_h

#include "IADrawable.h"
#include "IAView.h"
#include "IAString.h"

typedef struct{
    IAView * currentView;
    IAView * nextView;
    uint64_t switchStartTime;
    uint64_t switchDuration;
    bool isInsideAnyFunction;
} IAViewHolder;


void IAViewHolder_make(IAViewHolder *);

IAView * IAViewHolder_getLatestView(const IAViewHolder *);

void IAViewHolder_start(IAViewHolder *, IAView * view, uint64_t currentTime);

void IAViewHolder_switchView(IAViewHolder *, IAView * nextView, uint64_t currentTime, uint64_t duration, const void * viewArgs);
bool IAViewHolder_finishCurrentSwitchIfPossible(IAViewHolder *, uint64_t currentTime);

bool IAViewHolder_isSwitching(const IAViewHolder *);

void IAViewHolder_draw(IAViewHolder *, uint64_t currentTime);

void IAViewHolder_stop(IAViewHolder *, uint64_t currentTime);

#include "IAViewHolder+Generated.h"

#endif

