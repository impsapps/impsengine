//
//  IAStructArrayList.h
//  CLib
//
//  Created by Konstantin Merker on 18.07.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

//@ignore

#ifndef IAStructArrayList_h
#define IAStructArrayList_h

#include "IALibrary.h"

#define IA_STRUCT_ARRAY_LIST(type) IA_STRUCT_ARRAY_LIST_IMPL(IAStructArrayList_ ## type, type)
#define IA_STRUCT_ARRAY_LIST_IMPL(ListType, DataType) \
\
_Pragma("clang diagnostic push") \
_Pragma ("clang diagnostic ignored \"-Wunused-function\"") \
\
typedef struct{ \
    size_t currentSize; \
    size_t offset; \
    DataType * buffer; \
    size_t bufferSize; \
} ListType; \
\
\
static inline void ListType ## _make(ListType * this, size_t bufferSize, DataType buffer[bufferSize]){ \
    *this = (ListType){ \
        .currentSize = 0, \
        .offset = 0, \
        .buffer = buffer, \
        .bufferSize = bufferSize \
    }; \
} \
\
static inline void ListType ## _add(ListType * this, DataType data){ \
    debugAssert(this->currentSize < this->bufferSize); \
    size_t index = (this->offset + this->currentSize) % this->bufferSize; \
    this->buffer[index] = data; \
    this->currentSize++; \
} \
\
static inline size_t ListType ## _getCurrentSize(const ListType *); \
static inline DataType ListType ## _get(const ListType * this, size_t index); \
\
static inline void ListType ## _addAllFromList(ListType * this, const ListType * list){ \
    for (size_t i = 0; i < ListType ## _getCurrentSize(list); i++) { \
        DataType type = ListType ## _get(list, i); \
        ListType ## _add(this, type); \
    } \
} \
\
static inline DataType ListType ## _get(const ListType * this, size_t index){ \
    debugAssert(index < this->currentSize); \
    index = (index + this->offset) % this->bufferSize; \
    return this->buffer[index]; \
} \
\
static inline DataType ListType ## _getFirst(const ListType * this){ \
    return this->buffer[this->offset]; \
} \
\
static inline DataType ListType ## _getLast(const ListType * this){ \
    return this->buffer[(this->currentSize + this->offset - 1) % this->bufferSize]; \
} \
\
static inline size_t ListType ## _getCurrentSize(const ListType * this){ \
    return this->currentSize; \
} \
\
static inline size_t ListType ## _getBufferSize(const ListType * this){ \
    return this->bufferSize; \
} \
\
static inline DataType ListType ## _removeFirst(ListType * this){ \
    DataType element = ListType ## _getFirst(this); \
    this->offset++; \
    if (this->offset == this->bufferSize) { \
        this->offset = 0; \
    } \
    this->currentSize--; \
    return element; \
} \
\
static inline DataType ListType ## _removeLast(ListType * this){ \
    DataType element = ListType ## _getLast(this); \
    this->currentSize--; \
    return element; \
} \
\
static inline void ListType ## _clear(ListType * this){ \
    this->currentSize = 0; \
    this->offset = 0; \
} \
\
static inline bool ListType ## _isEmpty(ListType * this){ \
    return this->currentSize == 0; \
} \
\
_Pragma("clang diagnostic pop")


#define IA_STRUCT_ARRAY_LIST_MALLOC_MAKE(name, type, size) \
do { \
    name = IA_malloc(sizeof(IAStructArrayList_ ## type) + sizeof(type) * size); \
    IAStructArrayList_ ## type ## _make(name, size, (type *) (name + 1)); \
} while(0)

#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE(name, type, newSize) \
do { \
    IAStructArrayList_ ## type * newList = IA_malloc(sizeof(IAStructArrayList_ ## type) + sizeof(type) * (newSize)); \
    IAStructArrayList_ ## type ## _make(newList, (newSize), (type *) (newList + 1)); \
    IAStructArrayList_ ## type ## _addAllFromList(newList, name); \
    IAStructArrayList_ ## type * oldList = name; \
    name = newList; \
    IA_free(oldList); \
} while(0)

#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED(name, type) \
do { \
    if (IAStructArrayList_ ## type ## _getCurrentSize(name) \
        == IAStructArrayList_ ## type ## _getBufferSize(name)){ \
        IA_STRUCT_ARRAY_LIST_REALLOC_MAKE(name, type, IAStructArrayList_ ## type ## _getCurrentSize(name) * 2); \
    } \
} while(0)

#define IA_STRUCT_ARRAY_LIST_FREE(name) \
IA_free(name)

#endif
