#ifndef IADate_h
#define IADate_h

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
