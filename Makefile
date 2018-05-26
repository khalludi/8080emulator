CFLAGS=-Wall -I./src/include -I /usr/local/Cellar/sdl2/2.0.7/include/SDL2 -g -O0 -I /usr/local/Cellar/sdl2_mixer/2.0.2_3/include/SDL2
LIBS=-lcheck -l SDL2-2.0.0 -L /usr/local/Cellar/sdl2/2.0.7/lib -l SDL2_mixer-2.0.0 -L /usr/local/Cellar/sdl2_mixer/2.0.2_3/lib

ODIR=obj

SOURCES=./src/emu_shell.c ./src/game.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=emulator

# Uncomment to run cpu_diag test
TEST_SOURCES=./test/cpu_test.c
TEST_OBJECTS=$(filter-out ./src/game.o,$(OBJECTS))
TEST_OBJECTS += ./test/cpu_test.o

# Uncomment to run check unit-tests
# TEST_SOURCES=./test/emu_shell_test.c
# TEST_OBJECTS=$(filter-out ./src/game.o,$(OBJECTS))
# TEST_OBJECTS += ./test/emu_shell_test.o


all: emulator

$(EXECUTABLE): $(OBJECTS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

#debug: $(OBJECTS)
#	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test: emulator-test $(TEST_OBJECTS)
	./emulator-test

emulator-test: $(TEST_OBJECTS)
	gcc -g -O0 -o $@ $(TEST_OBJECTS) $(CFLAGS) $(LIBS)

game:
	gcc ./src/game.c -o $@ -I /usr/local/Cellar/sdl2/2.0.7/include -L /usr/local/Cellar/sdl2/2.0.7/lib -l SDL2-2.0.0 strip --strip-debug libpthread.so.0

windows:
	x86_64-w64-mingw32-gcc -o winemulator.exe ./src/emu_shell.c ./src/game.c -I./src/include \
					   -I /usr/local/Cellar/sdl2/2.0.7/include/SDL2 \
					   -I /usr/local/Cellar/sdl2_mixer/2.0.2_3/include/SDL2 \
                       -L /usr/local/cross-tools/x86_64-w64-mingw32/lib\
                       -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

clean:
	@rm -f *.o emulator* debug
	@#[ -f "emulator" ] && rm emulator
	@#[ -d "emulator.dSYM" ] && `rm -rf emulator.dSYM`
	@#[ -f "emulator-test" ] && rm emulator-test
	@#[ -d "emulator-test.dSYM" ] && `rm -rf emulator-test.dSYM`
