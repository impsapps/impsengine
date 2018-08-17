//
//  IAKeyValueHashMap.h
//  Hit Verto
//
//  Created by Konstantin Merker on 05/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAKeyValueHashMap_h
#define Hit_Verto_IAKeyValueHashMap_h

#include "IAHashMap.h"
#include "IAKeyValueElement.h"

/** 
 * Load all values from data into the corresponding key value delegates. If the hash map does not contain a delegate for a key, the key value set will be skipped.
 *
 * \param elements Must only include key value delegates.
 * \param data The data to get load into the key value delegates. This must be created via "IAKeyValueHashMap_save()". However, the data object can be extended. The additional extension is ignored. This is useful if you want to use a cryptographic encryption algorithm where padding is needed.
 * \returns Returns true if the data is valid and well formatted, false otherwise.
 */

bool IAKeyValueHashMap_load(const IAHashMap * elements, const IAString * data);


/**
 * Write all values from the hash map into data.
 *
 * \param elements Must only include key value delegates.
 * \param data The data to get overwritten. This object must be initialized, but the content doesn't matter.
 */

void IAKeyValueHashMap_save(const IAHashMap * elements, IAString * data);

#endif
