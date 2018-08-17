//
//  Date.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 26.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineCLibrary_IADate_h
#define ImpsEngineCLibrary_IADate_h

#include "IAObject.h"

typedef struct IADate_s{
    //@extend
    IAObject base;
    //@get
    int day;
    //@get
    int month;
    //@get
    int year;
    
    //@get
    int second;
    //@get
    int minute;
    //@get
    int hour;
} IADate;


void IADate_makeWithCurrentDate(IADate * this);
void IADate_makeWithCurrentUTCDate(IADate * this);
void IADate_makeWithDayMonthYear(IADate * this, int day, int month, int year);
void IADate_makeWithDayMonthYearSecondMinuteHour(IADate * this, int day, int month, int year, int second, int minute, int hour);

void IADate_makeCopy(IADate * this, const IADate * dateToCopy);

int IADate_daysDifference(IADate * this, IADate * to);
int IADate_isNextDay(IADate * this, IADate * next);

#include "IADate+Generated.h"

#endif
