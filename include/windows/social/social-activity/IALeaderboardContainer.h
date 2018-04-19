//
//  IALeaderboardContainer.h
//  Hit Verto
//
//  Created by Konstantin Merker on 10.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IALeaderboardContainer_h
#define Hit_Verto_IALeaderboardContainer_h

#include "IALeaderboard.h"
#include "IALeaderboardContainerAttributes.h"
#include "IAHashMap.h"

typedef struct{
    //@getAsConstRef
    IAHashMap leaderboards;
    void * correspondingObject;
    void(*onLoadingFinished)(void * correspondingObject);
} IALeaderboardContainer;


void IALeaderboardContainer_init(IALeaderboardContainer *, const IALeaderboardContainerAttributes * attributes);

void IALeaderboardContainer_startLoading(IALeaderboardContainer *);

IALeaderboard * IALeaderboardContainer_getLeaderboard(const IALeaderboardContainer *, const char * leaderboardId);

void IALeaderboardContainer_releaseRegisteredLeaderboards(IALeaderboardContainer *);
void IALeaderboardContainer_deinit(IALeaderboardContainer *);

#include "IALeaderboardContainer+Generated.h"

#endif
