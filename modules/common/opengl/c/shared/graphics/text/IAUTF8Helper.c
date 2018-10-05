#include "IAUTF8Helper.h"


int IAUTF8Helper_idToUTF8(int id, char utf8[4]){
    if (id < 0x80) {
        utf8[0] = id;
        return 1;
    }else if(id < 0x0800){
        utf8[1] = 0x80;
        int i;
        for (i = 0; i < 6; i++) {
            utf8[1] |= ((id % 2) << i);
            id >>= 1;
        }
        utf8[0] = 0xC0;
        for (i = 0; i < 5; i++) {
            utf8[0] |= (id % 2) << i;
            id >>= 1;
        }
        return 2;
    }else if(id < 0x010000){
        utf8[2] = 0x80;
        int i;
        for (i = 0; i < 6; i++) {
            utf8[2] |= (id % 2) << i;
            id >>= 1;
        }
        utf8[1] = 0x80;
        for (i = 0; i < 6; i++) {
            utf8[1] |= (id % 2) << i;
            id >>= 1;
        }
        utf8[0] = 0xE0;
        for (i = 0; i < 4; i++) {
            utf8[0] |= (id % 2) << i;
            id >>= 1;
        }
        return 3;
    }else if(id < 0x200000){
        utf8[3] = 0x80;
        int i;
        for (i = 0; i < 6; i++) {
            utf8[3] |= (id % 2) << i;
            id >>= 1;
        }
        utf8[2] = 0x80;
        for (i = 0; i < 6; i++) {
            utf8[2] |= (id % 2) << i;
            id >>= 1;
        }
        utf8[1] = 0x80;
        for (i = 0; i < 6; i++) {
            utf8[1] |= (id % 2) << i;
            id >>= 1;
        }
        utf8[0] = 0xF0;
        for (i = 0; i < 4; i++) {
            utf8[0] |= (id % 2) << i;
            id >>= 1;
        }
        return 4;
    }
    return -1;
}

int IAUTF8Helper_getNextChar(const char * utf8String, char utf8CharOut[5]){
    if(utf8String[0] == '\0'){
        utf8CharOut[0] = '\0';
        return 0;
    }else if ((utf8String[0] & 0x80) == 0) {
        utf8CharOut[0] = utf8String[0];
        utf8CharOut[1] = '\0';
        return 1;
    }else if((utf8String[0] & 0xE0) == 0xC0){
        utf8CharOut[0] = utf8String[0];
        utf8CharOut[1] = utf8String[1];
        utf8CharOut[2] = '\0';
        return 2;
    }else if((utf8String[0] & 0xF0) == 0xE0){
        utf8CharOut[0] = utf8String[0];
        utf8CharOut[1] = utf8String[1];
        utf8CharOut[2] = utf8String[2];
        utf8CharOut[3] = '\0';
        return 3;
    }else if((utf8String[0] & 0xF8) == 0xF0){
        utf8CharOut[0] = utf8String[0];
        utf8CharOut[1] = utf8String[1];
        utf8CharOut[2] = utf8String[2];
        utf8CharOut[3] = utf8String[3];
        utf8CharOut[4] = '\0';
        return 4;
    }else{
        return -1;
    }
}

