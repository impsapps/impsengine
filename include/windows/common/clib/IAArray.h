//
//  IAArray.h
//  Hit Verto
//
//  Created by Konstantin Merker on 23/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAArray_h
#define Hit_Verto_IAArray_h

#include <stddef.h>

/**
 *  A simple array implementation.
 *
 *  Can be used instead of typical c arrays as an object wrapper.
 *
 */

typedef struct{
    void ** objects;
    //@get
    size_t size;
} IAArray;


/**
 * Instead of having the object to manage the array, it is possible to provide a buffer and do the memory handling by yourself.
 *
 * \param size The size of the array
 * \param buffer The buffer
 */
void IAArray_makeWithSizeAndBuffer(IAArray *, size_t size, void * buffer[size]);

/**
 * Initializes the array.
 * \param size The size of the array
 */
void IAArray_init(IAArray *, size_t size);

/**
 * Initializes the array.
 * \param size The size of the array
 */
void IAArray_initWithObjects(IAArray *, size_t size, ...);

/**
 * Initializes the array.
 * \param size The size of the array
 */
IAArray * IAArray_newWithObjects(size_t size, ...);

/**
 * Set an element at the specified index.
 * \param index The index to set. Must be >= 0 and < size
 * \param object The object to set at the specified index
 */
void IAArray_set(IAArray *, size_t index, void * object);

/**
 * Get an element at the specified index.
 * \param index The index. Must be >= 0 and < size
 * \returns The object at the specified index
 */
void * IAArray_get(const IAArray *, size_t index);

/**
 * Calls the specified function on all objects in array and stops when reaching the first NULL value or end of array.
 * \param function The function to call objects on.
 */
void IAArray_callFunctionOnAllObjects(const IAArray *, void(*function)(void * object));

/**
 * Deinitialize the array.
 */
void IAArray_deinit(IAArray *);

#include "IAArrayIterator.h"
#include "IAArray+Generated.h"

#endif
