#include "IALibrary.h"
#include "IAInputOutputWinMappings.h"
#include "IALocalisation.h"
#include "IAStorage+Native.h"
#include "IAString+Assets+Native.h"

#define CLASSNAME "IAInputOutputWinMappings"


static IAInputOutputWinMappings mappings;

void IAInputOutputWinMappings_setMappings(IAInputOutputWinMappings mappingsTemp) {
	mappings = mappingsTemp;
}

const char * IALocalisation_getLocaleId() {
	return mappings.IALocalisation_getLocaleId();
}

void IAStorage_nativeGetPrivateDataDir(IAString * privateDataDir) {
	mappings.IAStorage_nativeGetPrivateDataDir(privateDataDir);
}

void IAString_nativeInitWithAsset(IAString * this, const char * assetName, const char * assetFileExtension) {
	mappings.IAString_nativeInitWithAsset(this, assetName, assetFileExtension);
}

