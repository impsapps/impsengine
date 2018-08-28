//
//  <%= ClassName %>.c
//

#include "IALibrary.h"
#include "<%= ClassName %>.h"

#define CLASSNAME "<%= ClassName %>"


void <%= ClassName %>_make(<%= ClassName %> * this){
	this->base = IAObject_make(this);
}
