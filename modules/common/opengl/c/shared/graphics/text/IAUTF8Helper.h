#ifndef IAUTF8Helper_h
#define IAUTF8Helper_h

int IAUTF8Helper_idToUTF8(int id, char utf8[4]);
int IAUTF8Helper_getNextChar(const char * utf8String, char utf8CharOut[5]);

#endif
