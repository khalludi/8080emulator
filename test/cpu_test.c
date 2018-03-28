#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "emu_shell.h"

State8080 state;

int init() {

    // Initialize State8080
    // Load argument into memory
    FILE *fileptr = fopen("./res/cpudiag.bin","rb");
    fseek(fileptr, 0, SEEK_END);
    long filelen = ftell(fileptr);
    rewind(fileptr);

    //char *buffer = (char *)malloc((filelen+1)*sizeof(char));
    //printf("%ld", filelen);
    char* buffer = (char *) malloc(filelen+150);
    fread(buffer+256, filelen, 1, fileptr);
    state.sp = 0xf000;
    state.memory = (uint8_t *) buffer;

    state.int_enable = 1;
    state.cpu_diag = 1;
    state.sp = 0xf000;
    state.cc.cy = 0;

    return 1;
}

int main() {

    init();

    //Fix the first instruction to be JMP 0x100
    state.memory[0]=0xc3;
    state.memory[1]=0;
    state.memory[2]=0x01;

    //Fix the stack pointer from 0x6ad to 0x7ad
    // this 0x06 byte 112 in the code, which is
    // byte 112 + 0x100 = 368 in memory
    state.memory[368] = 0x7;

    //Skip DAA test
    //state->memory[0x59c] = 0xc3; //JMP
    //state->memory[0x59d] = 0xc2;
    //state->memory[0x59e] = 0x05;
    int cnt = 0;
    while (cnt < 700) {
        printf("%ld - %02x%02x%02x - ", cnt+1, state.memory[state.pc], state.memory[state.pc+1], state.memory[state.pc+2]);
        printf("\tC=%d,P=%d,S=%d,Z=%d\n", state.cc.cy, state.cc.p,
        state.cc.s, state.cc.z);
        printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x PC %04x SP %04x\n",
        state.a, state.b, state.c, state.d,
        state.e, state.h, state.l, state.pc, state.sp);
        Emulate8080Op(&state);
        cnt++;
    }

    return 1;
}
