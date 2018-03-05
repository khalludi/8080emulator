#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL.h>
#include "emu_shell.h"

// Start SDL and create window
bool init();

// Loads Media
bool loadMedia();

// Frees media and shuts down SDL
void closeMedia();

// Time in microseconds
double getMicrotime();

// Other variables
State8080 state;
uint8_t shift0 = 0;
uint8_t shift1 = 0;
uint8_t shift_offset = 0;
uint8_t int_enable = 0;

// The window
SDL_Window* gWindow = NULL;
int SCREEN_WIDTH = 256;
int SCREEN_HEIGHT = 224;

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

    char *buffer = (char *)malloc((filelen+1)*sizeof(char));
    fread(buffer, filelen, 1, fileptr);
    state.sp = 0xf000;
    state.memory = (uint8_t *) buffer;

    state.sp = 0xf000;
    state.cc.cy = 0;

    return success;
}

bool loadMedia() {
    // Loading Success Flag
    bool success = true;

    /*/ Load splash image
    gImage = SDL_LoadBMP("bmw.bmp");
    if (gImage == NULL) {
        printf("Unable to load image bmw.bmp! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    */
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
    uint8_t a;
    switch(port) {
        case 0:
            return 1;
            break;
        case 1:
            return 0;
            break;

        case 3: {
            uint16_t v = (shift1 << 8) | shift0;
            a = ((v >> (8 - shift_offset)) & 0xff);
            break;
        }
    }
    return a;
}

void MachineOUT(uint8_t port, uint8_t value) {
    //uint8_t a;
    switch(port) {
        case 2:
            shift_offset = value & 0x7;
            break;
        case 4:
            shift0 = shift1;
            shift1 = value;
            break;
    }
}

double getMicrotime() {
    struct timeval cTime;
    gettimeofday(&cTime, NULL);
    return cTime.tv_sec + cTime.tv_usec;
}

int main( int argc, char* args[])
{
    // Start up SDL and create window
    if ( !init() ) {
        printf("Failed to initialize!\n");
    }
    else {
        // Main loop flag
        int quit = 0;
        // Event handler
        // SDL_Event e;

/*        State8080 *state;
        uint8_t shift0 = 0;
        uint8_t shift1 = 0;
        uint8_t shift_offset = 0;
*/
        double lastTime = 0;
        double nextInterrupt;
        int whichInterrupt;
        int cnt = 0;

        // While application is running
        while (!quit) {

            // Draw Surface using Pixels
            //unsigned char* buffer8888 = malloc(224*256);

            /*/ Fill buffer
            for (int i = 0; i < 224; i++) {
                for (int j = 0; j < 256; j+=8) {
                    unsigned char pix = state.memory[0x2400 + i * (256/8) + j / 8];
                    
                    // Vertical Flip
                    //int offset = (255-j)*(224) + (i*4);
                    buffer8888 += pix;
                }
            }*/

            //int depth = 8;
            //int pitch = 224;
            
            // Create Surface
            //SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(buffer8888, 224, 256, depth, pitch, 0, 0, 0, 0);
            //SDL_Surface* surf = malloc(4 * 256 * 224);
            SDL_Surface* surf = malloc(300*300);
            surf->pixels = malloc(256*224);
            surf->pitch = 256;
            surf->w = 256;
            surf->h = 224;
            SDL_Palette* palette = SDL_AllocPalette(2);
            SDL_Color white = {255,255,255,0};
            SDL_Color black = {0,0,0,0};
            SDL_Color colors_array[2] = {black, white};
            palette->colors = (SDL_Color *)&colors_array; 
            SDL_PixelFormat pixel_format = {SDL_PIXELFORMAT_INDEX1MSB, palette, 8, 1, 0, 0, 0, 0};
            surf->format = &pixel_format; 

            //surf->format->BytesPerPixel = 1;
            //surf->format->palette = NULL;
            int bpp = surf->format->BytesPerPixel;

            for (int i = 0; i < 224; i++) {
                for (int j = 0; j < 256; j+=8) {
                    uint8_t *pix = &state.memory[0x2400 + i * (256/8) + j / 8];
                    uint8_t *p = (uint8_t *) surf->pixels + i * surf->pitch + j* bpp;

                    //printf("%02x, %02x, %02x\n", pix[0], pix[0], pix[1]);
                    for (int k = 0; k < 8; k++) {
                        p[k] = (pix[0] >> k) & 0x01;
                    }

                    // Vertical Flip
                    //int offset = (255-j)*(224) + (i*4);
                    //buffer8888 += pix;
                }
            }

            SDL_BlitSurface(surf, NULL, SDL_GetWindowSurface(gWindow), NULL);
            printf("Blitted Surface!"); 
            SDL_UpdateWindowSurface(gWindow);

            if(surf == NULL) {
                printf("Surface not Created");
            }

            double now = getMicrotime();

            if (lastTime == 0.0) {
                lastTime = now;
                nextInterrupt = lastTime + 16000;
                whichInterrupt = 1;
            }

            if (int_enable && now > nextInterrupt) {
                if (whichInterrupt == 1) {
                    // Gen Interrupt
                    whichInterrupt = 2;
                }
                else {
                    // Gen Interrupt
                    whichInterrupt = 1;
                }
                nextInterrupt = now + 8000.0;
            }

            int num_cycles = (now - lastTime) * 2;
            int cycles = 0;
            while (num_cycles > cycles) {
                unsigned char* opcode = &state.memory[state.pc];
                if (*opcode == 0xdb) {
                    uint8_t port = opcode[1];
                    state.a = MachineIN(port);
                    state.pc++;
                    cycles += 4;
                    printf("%s HIT! \n", opcode);
                }
                else if(*opcode == 0xd3) {
                    //uint8_t port = opcode[1];
                    //MachineOUT(port);
                    state.pc += 2;
                }
                else
                    cycles += Emulate8080Op(&state);
                //printf("%02x, ", *opcode);
                
                /*
                printf("%d - ", cnt+1);
                printf("\tC=%d,P=%d,S=%d,Z=%d\n", state.cc.cy, state.cc.p,
                    state.cc.s, state.cc.z);
                printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x PC %04x SP %04x\n",
                    state.a, state.b, state.c, state.d,
                    state.e, state.h, state.l, state.pc, state.sp);
                */
                cnt += 1;
            }  

            lastTime = now;

            /*
            // Handle events on queue
            while( SDL_PollEvent( &e ) != 0 ) {
            // User requests quit
            if (e.type == SDL_QUIT) {
            quit = 1;
            }
            }*/


            // Apply the image
            //SDL_BlitSurface( gImage, NULL, gScreenSurface, NULL);

            // Update the surface
            //SDL_UpdateWindowSurface( gWindow );

        }

    }

    // Free resources and close SDL
    closeMedia();

    return 0;
}
