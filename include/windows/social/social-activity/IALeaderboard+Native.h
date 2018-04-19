//
//  IALeaderboard+Native.h
//  Hit Verto
//
//  Created by Konstantin Merker on 11.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IALeaderboard_Native_h
#define Hit_Verto_IALeaderboard_Native_h

#include "IALeaderboard.h"

void IALeaderboard_nativeSubmitNewScore(IALeaderboard * leaderboard, long newScore);

void IALeaderboard_nativeShow(IALeaderboard * leaderboard);

void IALeaderboard_notifyLoaded(IALeaderboard *, long highscore, long rank);

#endif
