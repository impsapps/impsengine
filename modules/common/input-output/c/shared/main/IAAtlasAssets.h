#ifndef IAAtlasAssets_h
#define IAAtlasAssets_h

#include "IAAtlasAssetsAttributes.h"
#include "IAString.h"

typedef struct{
    //@extend
    IAObject base;
    //@getAsCharArray
    IAString name;
    IAString namingTemplate;
    IAString assetNameTemp;
    //@get
    int count;
    
    //@get
    int logoIndex;   /// < if logo index is not set it equals -1
} IAAtlasAssets;


void IAAtlasAssets_init(IAAtlasAssets *, const IAAtlasAssetsAttributes * attr);

const char * IAAtlasAssets_getAssetNameForIndex(IAAtlasAssets *, int index);

void IAAtlasAssets_deinit(IAAtlasAssets *);

#include "IAAtlasAssets+Generated.h"

#endif
