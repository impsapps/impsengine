//
//  IALeaderboard.h
//  Hit Verto
//
//  Created by Konstantin Merker on 04.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IALeaderboard_h
#define Hit_Verto_IALeaderboard_h

#include "IAString.h"
#include "IALock.h"

typedef struct{
    //@getAsCharArray
    IAString * leaderboardId;
    long highscore;
    long rank;
    IALock lock;
} IALeaderboard;


void IALeaderboard_init(IALeaderboard *, const char * leaderboardId);
void IALeaderboard_initWithInitialHighscore(IALeaderboard *, const char * leaderboardId, long initialHighscore);

void IALeaderboard_submitNewScore(IALeaderboard *, long newScore);
long IALeaderboard_getHighscore(IALeaderboard *);
bool IALeaderboard_getRank(IALeaderboard *, long * rankOut);

void IALeaderboard_show(IALeaderboard *);

void IALeaderboard_deinit(IALeaderboard *);

#include "IALeaderboard+Generated.h"

#endif
