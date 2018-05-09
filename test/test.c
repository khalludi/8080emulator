#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "emu_shell.h"

int main() {

    State8080* state = malloc(sizeof(State8080));

    // Store hex value into a char *
    char * buffer = "7a"; char * pos = buffer;
    unsigned char val[1];
    for(int i = 0; i < sizeof(val); i++) {
        sscanf(pos, "%2hhx", &val[i]);
        pos += 2;
    }

    state->memory = val;
    state->sp = 0xf000;
    state->d = 0x11;
    Emulate8080Op(state);

    free(state);

    printf("%02x\n", state->l);
}
