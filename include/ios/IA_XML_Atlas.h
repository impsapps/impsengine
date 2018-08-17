//
//  IA_XML_Atlas.h
//  InputOutput
//
//  Created by Konstantin Merker on 01/11/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IA_XML_Atlas_h
#define IA_XML_Atlas_h

#include "IAAtlasAssets.h"
#include "IAArrayList.h"
#include "IAString.h"

typedef struct{
    IAString assetName;
    IAArrayList objects;
} IA_XML_Atlas;


void IA_XML_Atlas_init(IA_XML_Atlas *, const char * assetName);

void IA_XML_Atlas_load(IA_XML_Atlas *);

IAAtlasAssets * IA_XML_Atlas_get(IA_XML_Atlas *, const char * name);
const IAArrayList * IA_XML_Atlas_getAllAtlasAssets(IA_XML_Atlas *);

void IA_XML_Atlas_deinit(IA_XML_Atlas *);

#include "IA_XML_Atlas+Generated.h"

#endif
