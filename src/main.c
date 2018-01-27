
#include <stdlib.h>
#include <stdio.h>

#include "emu_shell.h"

int main() {
    printf("IT COMPILED !!!\n");
    // Create a state
    State8080 state;

    // Load argument into memory
    FILE *fileptr = fopen("./res/invaders","rb");
    fseek(fileptr, 0, SEEK_END);
    long filelen = ftell(fileptr);
    rewind(fileptr);

    char *buffer = (char *)malloc((filelen+1)*sizeof(char));
    fread(buffer, filelen, 1, fileptr);
    state.memory = (uint8_t *) buffer;
    
    state.sp = 0xf000;
    state.cc.cy = 0;
    // Call Emulate
    // Repeat emulator
    int cnt = 0;
    while (cnt < 42440) {
        Emulate8080Op(&state);
        if (cnt >= 42430-1) {
            printf("%d - ", cnt+1);
            printf("\tC=%d,P=%d,S=%d,Z=%d\n", state.cc.cy, state.cc.p,
                state.cc.s, state.cc.z);
            printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x PC %04x SP %04x\n",
                state.a, state.b, state.c, state.d,
                state.e, state.h, state.l, state.pc, state.sp);
        }
        cnt++;
    }
    /*/
    printf("\tC=%d,P=%d,S=%d,Z=%d\n", state.cc.cy, state.cc.p,
            state.cc.s, state.cc.z);
    printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x PC %04x SP %04x\n",
            state.a, state.b, state.c, state.d,
            state.e, state.h, state.l, state.pc, state.sp);
    *///
    return 0;
}
