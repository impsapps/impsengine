#include "IALibrary.h"
#include "IAAtlasAssets.h"

#define CLASSNAME "IAAtlasAssets"


void IAAtlasAssets_init(IAAtlasAssets * this, const IAAtlasAssetsAttributes * attr){
    this->base = IAObject_make(this);
    IAString_init(&this->name, attr->name);
    IAString_init(&this->namingTemplate, attr->namingTemplate);
    IAString_init(&this->assetNameTemp, attr->namingTemplate);
    this->count = attr->count;
    this->logoIndex = attr->logoIndex;
}

const char * IAAtlasAssets_getAssetNameForIndex(IAAtlasAssets * this, int index){
    debugAssert(index >= 0 && index < this->count);
    size_t indexOfPattern;
    size_t lengthOfPattern = 3;
    bool ret = IAString_getIndexOfFirstPatternMatch(&this->namingTemplate, "{n}", &indexOfPattern);
    assert(ret && "No valid naming template!");
    const char * namingTemplate = IAString_toCharArray(&this->namingTemplate);
    IAString_setWithLength(&this->assetNameTemp, namingTemplate, indexOfPattern);
    IAString_concatInt(&this->assetNameTemp, index);
    IAString_concat(&this->assetNameTemp, namingTemplate + indexOfPattern + lengthOfPattern);
    return IAString_toCharArray(&this->assetNameTemp);
}

void IAAtlasAssets_deinit(IAAtlasAssets * this){
    IAString_deinit(&this->name);
    IAString_deinit(&this->namingTemplate);
    IAString_deinit(&this->assetNameTemp);
}

