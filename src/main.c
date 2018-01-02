
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
    // Call Emulate
    // Repeat emulator
    while(1) {
        Emulate8080Op(&state);
    }

    return 0;
}
