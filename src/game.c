#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include "emu_shell.h"

// Start SDL and create window
bool init();

// Frees media and shuts down SDL
void closeMedia();

// Time in microseconds
double getMicrotime();

// Other variables
State8080 state;
uint8_t shift0 = 0;
uint8_t shift1 = 0;
uint8_t shift_offset = 0;
long len_of_file = 0;

// The window
SDL_Window* gWindow = NULL;
int SCREEN_WIDTH = 224;
int SCREEN_HEIGHT = 256;

// The surface of window
SDL_Surface* gScreenSurface = NULL;

// The image to load on screen
SDL_Surface* gImage = NULL;

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success=false;
    }
    else {
        // Create Window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    // Initialize State8080
    // Load argument into memory
    FILE *fileptr = fopen("./res/invaders","rb");
    fseek(fileptr, 0, SEEK_END);
    long filelen = ftell(fileptr);
    rewind(fileptr);

    //char *buffer = (char *)malloc((filelen+1)*sizeof(char));
    char* buffer = (char *) malloc(64001);
    len_of_file = 64001;
    fread(buffer, filelen, 1, fileptr);
    state.sp = 0xf000;
    state.memory = (uint8_t *) buffer;

    state.int_enable = 1;
    state.cpu_diag = 0;
    state.sp = 0xf000;
    state.cc.cy = 0;

    return success;
}

void closeMedia() {
    // Deallocate Surface
    SDL_FreeSurface(gImage);
    gImage = NULL;

    // Destroy Window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystem
    SDL_Quit();
}

uint8_t MachineIN(uint8_t port) {
    uint8_t a = 0x00;
    switch(port) {
        case 0:
        {
            return 0x01;
            break;
        }
        case 1:
        {
            return 0x00;
            break;
        }

        case 3:
        {
            uint16_t v = (shift1 << 8) | shift0;
            a = ((v >> (8 - shift_offset)) & 0xff);
            break;
        }
    }
    return a;
}

void MachineOUT(uint8_t port) {
    //uint8_t a;
    switch(port) {
        case 2:
        {
            shift_offset = state.a & 0x7;
            break;
        }
        case 4:
        {
            shift0 = shift1;
            shift1 = state.a;
            break;
        }
    }
}

double getMicrotime() {
    struct timeval cTime;
    gettimeofday(&cTime, NULL);
    return cTime.tv_sec + cTime.tv_usec*0.000001;
}

void draw() {

    void* pixels = malloc(256*224);

    for (int i = 0; i < 224; i++) {
        for (int j = 0; j < 256; j+=8) {
            long x = 0x2400 + i * (256/8) + j / 8;
            if ( x >= len_of_file) {
                // write error to printf stderr
                printf("%lu, %lu, %d, %d\n", x, len_of_file, i, j);
                // exit
                exit(0);
            }

            uint8_t *pix = &state.memory[x];

            for (int k = 0; k < 8; k++) {
                uint8_t *p = (uint8_t *) pixels + (255-j-k) * 224 + i-k;
                p[k] = (pix[0] >> k) & 0x01;
                if (p[k] == 1) {
                    p[k] = 0x01;
                }
            }
        }
    }

    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(pixels, 224, 256, 4, 224, 0x60, 0x18, 0x06, 0x80);

    SDL_Palette* palette = SDL_AllocPalette(2);
    SDL_Color white = {255,255,255,0};
    SDL_Color black = {0,0,0,0};
    SDL_Color colors_array[4] = {black, white};
    palette->colors = (SDL_Color *)&colors_array;
    SDL_PixelFormat pixel_format = {SDL_PIXELFORMAT_INDEX1LSB, palette, 8, 1, {0, 0}, 0x60, 0x18, 0x04, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL};
    surf->format = &pixel_format;

    SDL_BlitSurface(surf, NULL, SDL_GetWindowSurface(gWindow), NULL);
    SDL_UpdateWindowSurface(gWindow);
}

void GenerateInterrupt(int interrupt) {
    // Push
    state.sp -= 2;
    state.pc -= 1;
    state.memory[state.sp] = (state.pc & 0xff);
    state.memory[state.sp+1] = (state.pc & 0xff00) >> 8;


    //printf("\n%02x\n", state.pc);

    state.pc = 8 * interrupt - 1;
    state.int_enable = 0;
}

int main( int argc, char* args[])
{
    //printf("Start Main!");

    // Start up SDL and create window
    if ( !init() ) {
        printf("Failed to initialize!\n");
    }
    else {
        // Main loop flag
        int quit = 0;
        // Event handler
        // SDL_Event e;

        double lastTime = 0;
        double leftover_cycles = 0;
        double nextInterrupt;
        int whichInterrupt;
        long cnt = 0;
        int flag = 0;
        uint16_t tmp_hex = (state.memory[0x2079] << 8) | state.memory[0x2080];

        // While application is running
        while (!quit) {

            if (lastTime == 0.0) {
                lastTime = getMicrotime();
                nextInterrupt = lastTime + .0016667;
                whichInterrupt = 1;
            }

            //printf("%d, %f, %f\n", state.int_enable, getMicrotime(), nextInterrupt);
            double now = getMicrotime();
            if (state.int_enable && now > nextInterrupt) {
                if (whichInterrupt == 1) {
                    // Gen Interrupt
                    GenerateInterrupt(1);
                    whichInterrupt = 2;
                }
                else {
                    // Gen Interrupt
                    GenerateInterrupt(2);
                    whichInterrupt = 1;
                }
                draw();
                nextInterrupt = getMicrotime() + 0.00833;
                printf("Draw!\n");
            }

            double num_cycles = 0;
            if (!flag) {
                num_cycles = (getMicrotime() - lastTime) * 2000000;
            } else {
                num_cycles = (getMicrotime() - lastTime) * 2000000;
            }
            //printf("%f, %f, %d\n", num_cycles, leftover_cycles, numCycles(&state));
            //int num_cycles = 100000;
            //int cnt = 0;
            double cycles = (double) numCycles(&state);
            //int op_run = 113000;
            if(cycles == 0) printf("%02x\n", state.memory[state.pc]);
            while (num_cycles + leftover_cycles > cycles) {
                //while (cnt <= op_run) {
                unsigned char* opcode = &state.memory[state.pc];

                // First stop point
                /*if (state.pc == 0x0ada) {
                    state.memory[0x20c0] = 0;
                    flag = 1;
                    num_cycles = 0;
                }*/

                // Second stop point
                /*if (state.pc == 0x0a9e) {
                    state.memory[0x20c0] = 1;
                }*/

                if (*opcode == 0xdb) {
                    uint8_t port = opcode[1];
                    state.a = MachineIN(port);
                    state.pc += 2;
                    //printf("%02x%02x, %02x, HIT! %ld\n", opcode[0], opcode[1], state.a, cnt);
                }
                else if(*opcode == 0xd3) {
                    uint8_t port = opcode[1];
                    MachineOUT(port);
                    state.pc += 2;
                }
                else {
                    Emulate8080Op(&state);
                }

                num_cycles = num_cycles - cycles;
                leftover_cycles = 0.0;
                //printf("%02x, ", opcode);
                /*if (cnt >= 2090000) {
                    draw();
                    sleep(5000);
                    //cnt += 1;
                }*/

                if (tmp_hex != ((state.memory[0x2079] << 8) | state.memory[0x2080])) {
                    printf("\nMEM 2079 CHANGED from %04x to %04x\n", tmp_hex, (state.memory[0x2079] << 8) | state.memory[0x2080]);
                    tmp_hex = (state.memory[0x2079] << 8) | state.memory[0x2080];
                }

                //if (cnt >= op_run ) {
                printf("%ld - %02x%02x%02x - ", cnt+1, state.memory[state.pc], state.memory[state.pc+1], state.memory[state.pc+2]);
                printf("\tC=%d,P=%d,S=%d,Z=%d\n", state.cc.cy, state.cc.p,
                state.cc.s, state.cc.z);
                printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x PC %04x SP %04x\n",
                state.a, state.b, state.c, state.d,
                state.e, state.h, state.l, state.pc, state.sp);
                //}
                cnt += 1;
            }
            if (num_cycles > 0)
                leftover_cycles += num_cycles;
            lastTime = getMicrotime();

            /*
            // Handle events on queue
            while( SDL_PollEvent( &e ) != 0 ) {
            // User requests quit
            if (e.type == SDL_QUIT) {
            quit = 1;
        }
    }*/
        }

}

// Free resources and close SDL
closeMedia();

return 0;
}
