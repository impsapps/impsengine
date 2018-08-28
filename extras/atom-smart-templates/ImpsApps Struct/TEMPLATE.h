//
//  <%= ClassName %>.h
//

#ifndef <%= ClassName %>_h
#define <%= ClassName %>_h

#include "IAObject.h"

typedef struct{
	//@extend
	IAObject base;
	
	
} <%= ClassName %>;


void <%= ClassName %>_make(<%= ClassName %> *);

#include "<%= ClassName %>+Generated.h"

#endif
