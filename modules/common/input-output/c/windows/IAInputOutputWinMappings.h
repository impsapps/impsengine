#ifndef IAInputOutputWinMappings_h
#define IAInputOutputWinMappings_h

#include "IAString.h"

typedef struct{
	const char * (*IALocalisation_getLocaleId)();
	void (*IAStorage_nativeGetPrivateDataDir)(IAString * privateDataDir);
	void (*IAString_nativeInitWithAsset)(IAString * this, const char * assetName, const char * assetFileExtension);
} IAInputOutputWinMappings;


void IAInputOutputWinMappings_setMappings(IAInputOutputWinMappings mappings);

#endif
