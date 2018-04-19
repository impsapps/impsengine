//
//  IALeaderboardContainerAttributes.h
//  GameCenter
//
//  Created by Konstantin Merker on 03/01/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IALeaderboardContainerAttributes_h
#define IALeaderboardContainerAttributes_h

#include "IALeaderboard.h"

typedef struct{
    //@set+get
    void * correspondingObject;
    //@set+get
    void(*onLoadingFinished)(void * correspondingObject);
    //@getAsConstRef
    IAArrayList leaderboards;
} IALeaderboardContainerAttributes;


void IALeaderboardContainerAttributes_init(IALeaderboardContainerAttributes *);

void IALeaderboardContainerAttributes_addLeaderboard(IALeaderboardContainerAttributes *, IALeaderboard * leaderboard);

void IALeaderboardContainerAttributes_deinit(IALeaderboardContainerAttributes *);

#include "IALeaderboardContainerAttributes+Generated.h"

#endif
