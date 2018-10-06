#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#if defined(_WIN32)
    #include <windows.h>
#else
    #include <sys/time.h>
#endif
#include "SDL_mixer.h"
#include "SDL_pixels.h"
#include "SDL.h"
#include <unistd.h>
#include "emu_shell.h"

// Start SDL and create window
bool init();

// Frees media and shuts down SDL
void closeMedia();

// Time in microseconds
#if defined(_WIN32)
    LARGE_INTEGER getMicrotime();
#else
    double getMicrotime();
#endif

// Other variables
State8080 state;
uint8_t shift0 = 0;
uint8_t shift1 = 0;
uint8_t shift_offset = 0;
uint8_t in_port1 = 0x00;
uint8_t last_out_port3 = 0x00;
uint8_t last_out_port5 = 0x00;
uint8_t out_port5 = 0x00;
long len_of_file = 0;

// The window
SDL_Window* gWindow = NULL;
int SCREEN_WIDTH = 224 * 3;
int SCREEN_HEIGHT = 256 * 3;

// Sound Effects
Mix_Chunk *gPlayerExplosion = NULL;
Mix_Chunk *gFastInvader1 = NULL;
Mix_Chunk *gFastInvader2 = NULL;
Mix_Chunk *gFastInvader3 = NULL;
Mix_Chunk *gFastInvader4 = NULL;
Mix_Chunk *gInvaderExplosion = NULL;
Mix_Chunk *gPlayerShot = NULL;
Mix_Chunk *gUfoHighPitch = NULL;
Mix_Chunk *gUfoLowPitch = NULL;

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
        gWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    //Load sound effects
    gPlayerExplosion = Mix_LoadWAV( "res/sounds/explosion.wav" );
    if( gPlayerExplosion == NULL )
    {
        printf( "Failed to load gPlayerExplosion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gFastInvader1 = Mix_LoadWAV( "res/sounds/fastinvader1.wav" );
    if( gFastInvader1 == NULL )
    {
        printf( "Failed to load gFastInvader1 sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gFastInvader2 = Mix_LoadWAV( "res/sounds/fastinvader2.wav" );
    if( gFastInvader2 == NULL )
    {
        printf( "Failed to load gFastInvader2 sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gFastInvader3 = Mix_LoadWAV( "res/sounds/fastinvader3.wav" );
    if( gFastInvader3 == NULL )
    {
        printf( "Failed to load gFastInvader3 sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gFastInvader4 = Mix_LoadWAV( "res/sounds/fastinvader4.wav" );
    if( gFastInvader4 == NULL )
    {
        printf( "Failed to load gFastInvader4 sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gInvaderExplosion = Mix_LoadWAV( "res/sounds/invaderkilled.wav" );
    if( gInvaderExplosion == NULL )
    {
        printf( "Failed to load gInvaderExplosion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gPlayerShot = Mix_LoadWAV( "res/sounds/shoot.wav" );
    if( gPlayerShot == NULL )
    {
        printf( "Failed to load gPlayerShot sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gUfoHighPitch = Mix_LoadWAV( "res/sounds/ufo_highpitch.wav" );
    if( gUfoHighPitch == NULL )
    {
        printf( "Failed to load gUfoHighPitch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gUfoLowPitch = Mix_LoadWAV( "res/sounds/ufo_lowpitch.wav" );
    if( gUfoLowPitch == NULL )
    {
        printf( "Failed to load gUfoLowPitch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
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

    //Free the sound effects
    Mix_FreeChunk( gPlayerExplosion );
    Mix_FreeChunk( gInvaderExplosion );
    Mix_FreeChunk( gPlayerShot );
    Mix_FreeChunk( gFastInvader1 );
    Mix_FreeChunk( gFastInvader2 );
    Mix_FreeChunk( gFastInvader3 );
    Mix_FreeChunk( gFastInvader4 );
    Mix_FreeChunk( gUfoHighPitch );
    Mix_FreeChunk( gUfoLowPitch );
    gPlayerExplosion = NULL;
    gFastInvader1 = NULL;
    gFastInvader2 = NULL;
    gFastInvader3 = NULL;
    gFastInvader4 = NULL;
    gInvaderExplosion = NULL;
    gPlayerShot = NULL;
    gUfoHighPitch = NULL;
    gUfoLowPitch = NULL;

    // Destroy Window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystem
    Mix_Quit();
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
            return in_port1;
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
        case 3:
        {
            // 2094 state of port 3
            uint8_t out_port3 = state.memory[0x2094];
            if (out_port3 != last_out_port3) {
                if ((out_port3 & 0x01) == 1 && (last_out_port3 & 0x01) == 0) {
                    Mix_PlayChannel(5, gUfoLowPitch, -1);
                }
                else if ((out_port3 & 0x01) == 0 && (last_out_port3 & 0x01) == 1) {
                   Mix_HaltChannel(5);
                }
                if ((out_port3 & 0x02) >> 1 == 1 && (last_out_port3 & 0x02) >> 1 == 0) {
                    Mix_PlayChannel( -1, gPlayerShot, 0 );
                    // printf("Port change from %02x to %02x\n", last_out_port3, out_port3);
                }
                if ((out_port3 & 0x04) >> 2 == 1 && (last_out_port3 & 0x04) >> 2 == 0) {
                    Mix_PlayChannel( -1, gPlayerExplosion, 0 );
                }
                if ((out_port3 & 0x08) >> 3 == 1 && (last_out_port3 & 0x08) >> 3 == 0) {
                    Mix_PlayChannel( -1, gInvaderExplosion, 0 );
                }
                //if ((out_port3 & 0x8) && !(last_out_port3 & 0x8))
                last_out_port3 = out_port3;
            }
            break;
        }
        case 4:
        {
            shift0 = shift1;
            shift1 = state.a;
            break;
        }
        case 5:
        {
            // 2098 state of port 5
            uint8_t out_port5 = state.memory[0x2098];
            if (out_port5 != last_out_port5) {
                if ((out_port5 & 0x01) == 1 && (last_out_port5 & 0x01) == 0) {
                    Mix_PlayChannel( -1, gFastInvader1, 0 );
                    // printf("Port change from %02x to %02x\n", last_out_port3, out_port3);
                }
                if ((out_port5 & 0x02) >> 1 == 1 && (last_out_port5 & 0x02) >> 1 == 0) {
                    Mix_PlayChannel( -1, gFastInvader2, 0 );
                }
                if ((out_port5 & 0x04) >> 2 == 1 && (last_out_port5 & 0x04) >> 2 == 0) {
                    Mix_PlayChannel( -1, gFastInvader3, 0 );
                }
                if ((out_port5 & 0x08) >> 3 == 1 && (last_out_port5 & 0x08) >> 3 == 0) {
                    Mix_PlayChannel( -1, gFastInvader4, 0 );
                }
                if ((out_port5 & 0x10) >> 4 == 1 && (last_out_port5 & 0x10) >> 4 == 0) {
                    Mix_PlayChannel( -1, gUfoHighPitch, 0 );
                }
                //if ((out_port3 & 0x8) && !(last_out_port3 & 0x8))
                last_out_port5 = out_port5;
            }
            break;
        }
    }
}

#if defined(_WIN32)
    LARGE_INTEGER getMicrotime() {
        LARGE_INTEGER CurrentTime, ElapsedMicroseconds;
        // LARGE_INTEGER Frequency;
        // QueryPerformanceFrequency(&Frequency);
        QueryPerformanceCounter(&CurrentTime);
        // ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
        // ElapsedMicroseconds.QuadPart *= 1000000;
        // ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
        return CurrentTime;
    }
#else
    double getMicrotime() {
        struct timeval cTime;
        gettimeofday(&cTime, NULL);
        return cTime.tv_sec + cTime.tv_usec*0.000001;
    }
#endif

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

                // White color for default
                if (p[k] == 1) {
                    p[k] = 0x01;
                }

                // Red color under scoreboard but above aliens
                if (255-j-k > 32 && 255-j-k < 50 && p[k] == 1) {
                    p[k] = 0x02;
                }

                // Green color for shields and player
                if (255-j-k > 180 && 255-j-k < 240 && p[k] == 1) {
                    p[k] = 0x03;
                }

                // Green color for lives
                if (255-j-k >= 240 && 255-j-k <= 256 && i-k > 20 && i-k < 80 && p[k] == 1) {
                    p[k] = 0x03;
                }
            }
        }
    }

    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(pixels, 224, 256, 4, 224, 0x0, 0x0, 0x0, 0x0);

    SDL_Palette* palette = SDL_AllocPalette(4);
    SDL_Color white = {255,255,255,0};
    SDL_Color black = {0,0,0,0};
    SDL_Color red = {255,0,0,0};
    SDL_Color green = {0,255,0,0};
    SDL_Color colors_array[4] = {black, white, red, green};
    palette->colors = (SDL_Color *)&colors_array;
    //SDL_PixelFormat pixel_format = {SDL_PIXELFORMAT_INDEX1LSB, palette, 8, 1, {0, 0}, 0x60, 0x18, 0x04, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL};
    SDL_PixelFormat pixel_format = {SDL_PIXELFORMAT_INDEX1LSB, palette, 8, 1, {0, 0}, 0x0, 0x0, 0x00, 0x0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL};
    surf->format = &pixel_format;

    SDL_Surface* optimizedSurface = SDL_ConvertSurface( surf, gScreenSurface->format, 0 );

    //Apply the image stretched
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled( optimizedSurface, NULL, gScreenSurface, &stretchRect );

    //SDL_BlitSurface(surf, NULL, SDL_GetWindowSurface(gWindow), NULL);
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

int main( int argc, char* argv[])
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
        SDL_Event e;

#if defined(_WIN32)
        LARGE_INTEGER Frequency;
        QueryPerformanceFrequency(&Frequency);
        LARGE_INTEGER lastTime;
        lastTime.QuadPart = 0;
        LARGE_INTEGER nextInterrupt;
#else
        double lastTime = 0;
        double nextInterrupt;
#endif
        double leftover_cycles = 0;
        int whichInterrupt;
        long cnt = 0;
        //int flag = 0;
        //uint16_t tmp_hex = (state.memory[0x2079] << 8) | state.memory[0x2080];

        // While application is running
        while (!quit) {

#if defined(_WIN32)
            if (lastTime.QuadPart == 0.0) {
                lastTime = getMicrotime();
                nextInterrupt.QuadPart = lastTime.QuadPart + 1666;
                whichInterrupt = 1;
            }
#else
            if (lastTime == 0.0) {
                lastTime = getMicrotime();
                nextInterrupt = lastTime + .0016667;
                whichInterrupt = 1;
            }
#endif

            //printf("%d, %f, %f\n", state.int_enable, getMicrotime(), nextInterrupt);
#if defined(_WIN32)
            LARGE_INTEGER now = getMicrotime();
            if (state.int_enable && now.QuadPart > nextInterrupt.QuadPart) {
#else
            double now = getMicrotime();
            if (state.int_enable && now > nextInterrupt) {
#endif
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
#if defined(_WIN32)
                nextInterrupt.QuadPart = getMicrotime().QuadPart + 8333;
#else
                nextInterrupt = getMicrotime() + 0.00833;
#endif
                //printf("Draw!\n");
            }

#if defined(_WIN32)
            long num_cycles = (((getMicrotime().QuadPart - lastTime.QuadPart) * 1000000) / Frequency.QuadPart) * 2.7;// 2
#else
            long num_cycles = (getMicrotime() - lastTime) * 2000000;
#endif
            // if (!flag) {
            //     num_cycles = (getMicrotime() - lastTime) * 2000000;
            // } else {
            // }
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

                /*if (tmp_hex != ((state.memory[0x2079] << 8) | state.memory[0x2080])) {
                    printf("\nMEM 2079 CHANGED from %04x to %04x\n", tmp_hex, (state.memory[0x2079] << 8) | state.memory[0x2080]);
                    tmp_hex = (state.memory[0x2079] << 8) | state.memory[0x2080];
                }*/

                //if (cnt >= op_run ) {
                // printf("%ld - %02x%02x%02x - ", cnt+1, state.memory[state.pc], state.memory[state.pc+1], state.memory[state.pc+2]);
                // printf("\tC=%d,P=%d,S=%d,Z=%d\n", state.cc.cy, state.cc.p,
                // state.cc.s, state.cc.z);
                // printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x PC %04x SP %04x\n",
                // state.a, state.b, state.c, state.d,
                // state.e, state.h, state.l, state.pc, state.sp);
                //}
                cnt += 1;
            }
            if (num_cycles > 0)
                leftover_cycles += num_cycles;
            lastTime = getMicrotime();


            // Handle events on queue
            while( SDL_PollEvent( &e ) != 0 ) {
                // User requests quit
                if (e.type == SDL_QUIT) {
                    quit = 1;
                }
            }

            // Update Key States
            // Controls: z, x = left, right; c = coin; 1 = 1 player; . = shoot
            const uint8_t* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_Z]) {
                in_port1 = in_port1 | 0x20;
            } else {
                in_port1 = in_port1 & ~(0x20);
            }
            if (currentKeyStates[SDL_SCANCODE_X]) {
                in_port1 = in_port1 | 0x40;
            } else {
                in_port1 = in_port1 & ~(0x40);
            }
            if (currentKeyStates[SDL_SCANCODE_PERIOD]) {
                in_port1 = in_port1 | 0x10;
            } else {
                in_port1 = in_port1 & ~(0x10);
            }
            if (currentKeyStates[SDL_SCANCODE_C]) {
                in_port1 = in_port1 | 0x01;
            } else {
                in_port1 = in_port1 & ~(0x01);
            }
            if (currentKeyStates[SDL_SCANCODE_1]) {
                in_port1 = in_port1 | 0x04;
            } else {
                in_port1 = in_port1 & ~(0x04);
            }
        }
    }

    // Free resources and close SDL
    closeMedia();

    return 0;
}
