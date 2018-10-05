//@ignore

#ifndef IAStructArrayList_h
#define IAStructArrayList_h

#include "IALibrary.h"

#define IA_STRUCT_ARRAY_LIST(type) IA_STRUCT_ARRAY_LIST_IMPL(IAStructArrayList_ ## type, type)
#define IA_STRUCT_ARRAY_LIST_VOID() IA_STRUCT_ARRAY_LIST_IMPL(IAStructArrayList, void *)
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
    debugAssert(this->currentSize > 0); \
    return this->buffer[this->offset]; \
} \
\
static inline DataType ListType ## _getLast(const ListType * this){ \
    debugAssert(this->currentSize > 0); \
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
static inline DataType ListType ## _removeAtIndex(ListType * this, size_t index){ \
    debugAssert(index < this->currentSize); \
    size_t currentIndex = (this->offset + index) % this->bufferSize; \
    size_t targetIndex; \
    \
    DataType result = this->buffer[currentIndex]; \
    \
    if (index > (this->currentSize) / 2) { \
        targetIndex = (this->offset + this->currentSize - 1) % this->bufferSize; \
        \
        if (targetIndex == -1) { \
            targetIndex = this->bufferSize - 1; \
        } \
        \
        while (currentIndex != targetIndex) { \
            size_t nextIndex = currentIndex + 1; \
            if(nextIndex == this->bufferSize) nextIndex = 0; \
            this->buffer[currentIndex] = this->buffer[nextIndex]; \
            currentIndex = nextIndex; \
        } \
    }else{ \
        targetIndex = (this->offset) % this->bufferSize; \
         \
        while (currentIndex != targetIndex) { \
            size_t nextIndex = currentIndex - 1; \
            if(nextIndex == -1) nextIndex = this->bufferSize - 1; \
            this->buffer[currentIndex] = this->buffer[nextIndex]; \
            currentIndex = nextIndex; \
        } \
        this->offset ++; \
        if (this->offset >= this->bufferSize) { \
            this->offset=0; \
        } \
    } \
     \
    this->currentSize--; \
    return result; \
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

#define IA_STRUCT_ARRAY_LIST_MALLOC_MAKE(name, type, size) IA_STRUCT_ARRAY_LIST_MALLOC_MAKE_WITH_CLASSNAME(name, type, size, CLASSNAME)
#define IA_STRUCT_ARRAY_LIST_MALLOC_MAKE_WITH_CLASSNAME(name, type, size, className) IA_STRUCT_ARRAY_LIST_MALLOC_MAKE_IMPL(name, IAStructArrayList_ ## type, type, size, className)
#define IA_STRUCT_ARRAY_LIST_VOID_MALLOC_MAKE(name, size) IA_STRUCT_ARRAY_LIST_VOID_MALLOC_MAKE_WITH_CLASSNAME(name, size, CLASSNAME)
#define IA_STRUCT_ARRAY_LIST_VOID_MALLOC_MAKE_WITH_CLASSNAME(name, size, className) IA_STRUCT_ARRAY_LIST_MALLOC_MAKE_IMPL(name, IAStructArrayList, void *, size, className)
#define IA_STRUCT_ARRAY_LIST_MALLOC_MAKE_IMPL(name, ListType, DataType, size, className)\
do { \
    name = IA_mallocWithClassName(sizeof(ListType) + sizeof(DataType) * size, className); \
    ListType ## _make(name, size, (DataType *) (name + 1)); \
} while(0)


//These macros guarantee, that the list referenced by name is replaced in one operation. At no time name shall reference to an invalid list.
#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE(name, type, size) IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_WITH_CLASSNAME(name, type, size, CLASSNAME)
#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_WITH_CLASSNAME(name, type, size, className) IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IMPL(name, IAStructArrayList_ ## type, type, size, className)
#define IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE(name, size) IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_WITH_CLASSNAME(name, size, CLASSNAME)
#define IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_WITH_CLASSNAME(name, size, className) IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IMPL(name, IAStructArrayList, void *, size, className)
#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IMPL(name, ListType, DataType, newSize, className) \
do { \
    ListType * newList = IA_mallocWithClassName(sizeof(ListType) + sizeof(DataType) * (newSize), className); \
    ListType ## _make(newList, (newSize), (DataType *) (newList + 1)); \
    ListType ## _addAllFromList(newList, name); \
    ListType * oldList = name; \
    name = newList; \
    IA_freeWithClassName(oldList, className); \
} while(0)

#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED(name, type) IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(name, type, CLASSNAME)
#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(name, type, className) IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED_IMPL(name, IAStructArrayList_ ## type, type, className)
#define IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_IF_NEEDED(name) IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(name, CLASSNAME)
#define IA_STRUCT_ARRAY_LIST_VOID_REALLOC_MAKE_IF_NEEDED_WITH_CLASSNAME(name, className) IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED_IMPL(name, IAStructArrayList, void *, className)
#define IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED_IMPL(name, ListType, DataType, className) \
do { \
    if (ListType ## _getCurrentSize(name) \
        == ListType ## _getBufferSize(name)){ \
        IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IMPL(name, ListType, DataType, ListType ## _getCurrentSize(name) * 2, className); \
    } \
} while(0)

#define IA_STRUCT_ARRAY_LIST_FREE(name) IA_free(name)
#define IA_STRUCT_ARRAY_LIST_FREE_WITH_CLASSNAME(name, className) IA_freeWithClassName(name, className)
#define IA_STRUCT_ARRAY_LIST_VOID_FREE(name) IA_free(name)
#define IA_STRUCT_ARRAY_LIST_VOID_FREE_WITH_CLASSNAME(name, className) IA_freeWithClassName(name, className)

IA_STRUCT_ARRAY_LIST_VOID();

#endif
