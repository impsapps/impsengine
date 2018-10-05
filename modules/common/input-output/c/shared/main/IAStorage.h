#ifndef IAStorage_h
#define IAStorage_h


/**
 * Get the name of the dir where the app can store private data. It is guarenteed to end with '/'.
 * \returns the name of the dir
 */

const char * IAStorage_getPrivateDataDir();

#endif
