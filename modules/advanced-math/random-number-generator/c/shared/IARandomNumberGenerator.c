#include "IARandomNumberGenerator.h"
#include "SFMT.h"
#include "IALibrary.h"

#define CLASSNAME "IARandomNumberGenerator"

static bool isRandomized = false;
static sfmt_t sfmt;

void IARandomNumberGenerator_randomize(uint32_t seed){
    sfmt_init_gen_rand(&sfmt, seed);
    isRandomized = true;
}

uint32_t IARandomNumberGenerator_getRandom(){
    assert(isRandomized && "IARandomNumberGenerator is not randomized yet!");
    return sfmt_genrand_uint32(&sfmt);
}

int IARandomNumberGenerator_getRandomModulo(int modulo){
    assert(isRandomized && "IARandomNumberGenerator is not randomized yet!");
    return sfmt_genrand_res53(&sfmt) * modulo;
}

int IARandomNumberGenerator_getRandomInRange(int min, int max){
    assert(isRandomized && "IARandomNumberGenerator is not randomized yet!");
    return (sfmt_genrand_res53(&sfmt) * (max - min + 1)) + min;
}

long IARandomNumberGenerator_getRandomLongInRange(long min, long max){
    assert(isRandomized && "IARandomNumberGenerator is not randomized yet!");
    return (sfmt_genrand_res53(&sfmt) * (max - min + 1)) + min;
}

double IARandomNumberGenerator_getRandomDouble(){
    assert(isRandomized && "IARandomNumberGenerator is not randomized yet!");
    return sfmt_genrand_res53(&sfmt);
}

bool IARandomNumberGenerator_doesEventOccur(double probabilityOfEvent){
    if (probabilityOfEvent > IARandomNumberGenerator_getRandomDouble()) {
        return true;
    }else{
        return false;
    }
}

