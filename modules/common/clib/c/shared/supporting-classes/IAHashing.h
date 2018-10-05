#ifndef IAHashing_h
#define IAHashing_h

/// Simple hash. Don't use it for security purposes. The hash is subject to change, so don't safe the hash code on persistend storage.
long IAHashing_getHashCode(const char * c);

#endif
