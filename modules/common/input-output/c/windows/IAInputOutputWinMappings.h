//
//  IAInputOutputWinMappings.h
//  InputOutput
//
//  Created by Konstantin Merker on 16.03.18.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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
