//
//  <%= ClassName %>.c
//

#include "IALibrary.h"
#include "<%= ClassName %>.h"

#define CLASSNAME "<%= ClassName %>"


void <%= ClassName %>_init(<%= ClassName %> * this){
	this->base = IAObject_make(this);
	IA_incrementInitCount();
}

void <%= ClassName %>_deinit(<%= ClassName %> * this){
	IA_decrementInitCount();
}
