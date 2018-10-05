#include "IALibrary.h"
#include "IAKeyValueElementAttributes.h"

#define CLASSNAME "IAKeyValueElementAttributes"

static const bool trueValue = true;

void IAKeyValueElementAttributes_make(IAKeyValueElementAttributes * this, void * value, void (*applyStringToValue)(void * value, IAString * string), void (*setString)(void * value, IAString * string)){
    *this = (IAKeyValueElementAttributes){
        .value = value,
        .applyStringToValue = applyStringToValue,
        .setString = setString,
        .shouldSave = &trueValue
    };
}


