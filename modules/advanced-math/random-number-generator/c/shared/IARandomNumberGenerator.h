#ifndef IARandomNumberGenerator_h
#define IARandomNumberGenerator_h

#include <stdint.h>
#include <stdbool.h>

void IARandomNumberGenerator_randomize(uint32_t seed);
uint32_t IARandomNumberGenerator_getRandom();
int IARandomNumberGenerator_getRandomModulo(int modulo);
int IARandomNumberGenerator_getRandomInRange(int min, int max);
long IARandomNumberGenerator_getRandomLongInRange(long min, long max);
double IARandomNumberGenerator_getRandomDouble();
bool IARandomNumberGenerator_doesEventOccur(double probabilityOfEvent);

#endif
