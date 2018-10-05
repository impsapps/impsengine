#include "IALibrary.h"
#include "IALock.h"

#define CLASSNAME "IALock"

#ifdef IA_POSIX_AVAILABLE

void IALock_init(IALock * this){
    this->base = IAObject_make(this);
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutex_init(&this->mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    IA_incrementInitCount();
}

bool IALock_lock(IALock * this){
    if(pthread_mutex_lock(&this->mutex) == 0){
        return true;
    }else{
        return false;
    }
}
bool IALock_unlock(IALock * this){
    if(pthread_mutex_unlock(&this->mutex) == 0){
        return true;
    }else{
        return false;
    }
}

void IALock_deinit(IALock * this){
    pthread_mutex_destroy(&this->mutex);
    IA_decrementInitCount();
}

#endif
