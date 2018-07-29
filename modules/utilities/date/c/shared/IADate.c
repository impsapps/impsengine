//
//  Date.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 26.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IADate+Native.h"

#define CLASSNAME "IADate"


//private methods
bool IADate_isLeapYear(int year);
int IADate_getDaysOfMonth(int month, int year);
bool IADate_isCorrektDateOrder(IADate * this, IADate * date2);
void IADate_increaseMonthByOne(IADate * this);


void IADate_makeWithCurrentDate(IADate * this){
    IADate_nativeMakeWithCurrentDate(this);
}

void IADate_makeWithCurrentUTCDate(IADate * this){
    IADate_nativeMakeWithCurrentUTCDate(this);
}

void IADate_makeWithDayMonthYear(IADate * this, int day, int month, int year){
    IADate_makeWithDayMonthYearSecondMinuteHour(this, day, month, year, 0, 0, 0);
}

void IADate_makeWithDayMonthYearSecondMinuteHour(IADate * this, int day, int month, int year, int second, int minute, int hour){
    this->base = IAObject_make(this);
    this->day = day;
    this->month = month;
    this->year = year;
    this->second = second;
    this->minute = minute;
    this->hour = hour;
}

void IADate_makeCopy(IADate * this, const IADate * dateToCopy){
    *this = *dateToCopy;
    this->base = IAObject_make(this);
}

int IADate_daysDifference(IADate * this, IADate * to){
    
    if (IADate_isCorrektDateOrder(this, to)) {
        int daysDifference = 0;
        
        IADate fromCopy;
        IADate_makeCopy(&fromCopy, this);
        
        //adjust to one year
        int toYear = to->year;
        fromCopy.year = toYear;
        if (IADate_isCorrektDateOrder(&fromCopy, to) == false) {
            toYear--;
        }
        fromCopy.year = this->year;
        
        int yearToCount;
        if (fromCopy.month > 2) {
            yearToCount = 1;
        }else{
            yearToCount = 0;
        }
        
        while (fromCopy.year < toYear) {
            if (IADate_isLeapYear(fromCopy.year + yearToCount)) {
                daysDifference += 366;
            }else{
                daysDifference += 365;
            }
            fromCopy.year++;
        }
        
        //adjust to one month
        int toMonth = to->month;
        toYear = to->year;
        fromCopy.month = toMonth;
        int tempFromCopyYear = fromCopy.year;
        fromCopy.year = to->year;
        
        if (IADate_isCorrektDateOrder(&fromCopy, to) == false) {
            toMonth--;
            if (toMonth == 0) {
                toMonth = 12;
                toYear--;
            }
        }
        fromCopy.month = this->month;
        fromCopy.year = tempFromCopyYear;
        
        while (fromCopy.month != toMonth || fromCopy.year != toYear) {
            daysDifference += IADate_getDaysOfMonth(fromCopy.month, fromCopy.year);
            IADate_increaseMonthByOne(&fromCopy);
        }
        
        
        //adjust exactly
        int toDay = to->day;
        int maxDayForMonth = IADate_getDaysOfMonth(fromCopy.month, fromCopy.year);
        
        while (fromCopy.day != toDay) {
            daysDifference++;
            fromCopy.day++;
            if (maxDayForMonth < fromCopy.day) {
                fromCopy.day = 1;
                IADate_increaseMonthByOne(&fromCopy);
                maxDayForMonth = IADate_getDaysOfMonth(fromCopy.month, fromCopy.year);
            }
        }
        
        return daysDifference;
    }else{
        return -(IADate_daysDifference(to, this));
    }
}

bool IADate_isCorrektDateOrder(IADate * this, IADate * date2){
    if (this->year < date2->year) {
        return true;
    }else if(this->year > date2->year){
        return false;
    }else{
        if (this->month < date2->month) {
            return true;
        }else if(this->month > date2->month){
            return false;
        }else{
            if (this->day <= date2->day) {
                return true;
            }else{
                return false;
            }
        }
    }
}

bool IADate_isLeapYear(int year){
    if (year % 400 == 0) {
        return true;
    }else if(year % 100 == 0){
        return false;
    }else if(year % 4 == 0){
        return true;
    }else{
        return false;
    }
}

int IADate_getDaysOfMonth(int month, int year){
    switch (month) {
        case 1:
            return 31;
        case 2:
            if (IADate_isLeapYear(year)) {
                return 29;
            }else{
                return 28;
            }
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
        default:
            assert(0 && "getDaysOfMonth: invalid month");
            return 0;
    }
}

void IADate_increaseMonthByOne(IADate * this){
    this->month++;
    if (this->month == 13) {
        this->month = 1;
        this->year++;
    }
}


int IADate_isNextDay(IADate * this, IADate * next){
    if (IADate_daysDifference(this, next) == 1) {
        return true;
    }else{
        return false;
    }
}

