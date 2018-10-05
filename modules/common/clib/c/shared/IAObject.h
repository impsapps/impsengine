#ifndef IAObject_h
#define IAObject_h

typedef void * IAObject;

static inline IAObject IAObject_make(void * object){
    return object;
}

#endif
