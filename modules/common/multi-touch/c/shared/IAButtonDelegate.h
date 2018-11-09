//
//  IAButtonDelegate.h
//

#ifndef IAButtonDelegate_h
#define IAButtonDelegate_h

#include <stdbool.h>

typedef struct IAButton IAButton;

//@event
typedef struct {
	void * correspondingObject;
	//@exe
	void(*onClick)(void * correspondingObject, IAButton * button);
	//@exe
	void(*onIsTouchedChanged)(void * correspondingObject, IAButton * button, bool isTouched);
} IAButtonDelegate;

#include "IAButtonDelegate+Generated.h"

#endif
