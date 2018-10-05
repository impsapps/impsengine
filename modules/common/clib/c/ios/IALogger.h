#ifndef IALogger_h
#define IALogger_h

#include <stdio.h>


#define logError(...) printf("!!!ERROR!!! %s: ", CLASSNAME); printf (__VA_ARGS__); printf("\n")
#define logWarning(...) printf("Warning %s: ", CLASSNAME); printf (__VA_ARGS__); printf("\n")
#define logInfo(...) printf("Info %s: ", CLASSNAME); printf (__VA_ARGS__); printf("\n")

#endif
