#ifndef IAAppEntryPoint_h
#define IAAppEntryPoint_h

#include "IAInterfaceOrientationMask.h"
#include "IAAppAttributes.h"

void IAAppEntryPoint_setInterfaceOrientationMask(IAInterfaceOrientationMask interfaceOrientationMask);
void IAAppEntryPoint_setOnAppStart(void (*onAppStart)(IAAppAttributes * attributesOut));

#endif
