#include <check.h>
#include <stdio.h>
#include <stdlib.h>
//#include "emu_shell.h"

int main() {
    
//    State8080 state;
    
    char * buffer = "0138c1"; char * pos = buffer;
    unsigned char val[3];
    for(int i = 0; i < sizeof(val); i++) {
        sscanf(pos, "%2hhx", &val[i]);
        pos += 2;
    }

    printf("%2hhx, %2hhx, %2hhx \n", val[0], val[1], val[2]);
    printf("%2hhx \n", val[1]);

//    state.memory = val;
//    state.d = 0x11;
//    Emulate8080Op(&state);
//    Emulate8080Op(&state);

    return 0;
}
