#include "IALibrary.h"
#include "IACondition.h"
#include "IAAllocationTracking.h"

#define CLASSNAME "IACondition"


#ifdef IA_POSIX_AVAILABLE

void IACondition_init(IACondition * this){
    this->base = IAObject_make(this);
    pthread_condattr_t condattr;
    pthread_condattr_init(&condattr);
    pthread_cond_init(&this->condition, &condattr);
    pthread_condattr_destroy(&condattr);
    IA_incrementInitCount();
}

void IACondition_wait(IACondition * this, IALock * lock){
    pthread_mutex_t * mutex = IALock_getMutex(lock);
    pthread_cond_wait(&this->condition, mutex);
}

void IACondition_signal(IACondition * this){
    pthread_cond_signal(&this->condition);
}

void IACondition_broadcast(IACondition * this){
    pthread_cond_broadcast(&this->condition);
}

void IACondition_deinit(IACondition * this){
    pthread_cond_destroy(&this->condition);
    IA_decrementInitCount();
}

#endif

