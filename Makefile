CFLAGS=-Wall -I./src/include -g -O0
LIBS=-lcheck

ODIR=obj

SOURCES=./src/emu_shell.c ./src/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=emulator

TEST_SOURCES=./test/emu_shell_test.c
TEST_OBJECTS=$(filter-out ./src/main.o,$(OBJECTS))
TEST_OBJECTS += ./test/emu_shell_test.o

all: emulator

$(EXECUTABLE): $(OBJECTS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

#debug: $(OBJECTS)
#	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test: emulator-test $(TEST_OBJECTS)
	./emulator-test

emulator-test: $(TEST_OBJECTS)
	gcc -g -O0 -o $@ $(TEST_OBJECTS) $(FLAGS) $(LIBS) -I./src/include

clean:
	@rm -f *.o emulator* debug 
	@#[ -f "emulator" ] && rm emulator
	@#[ -d "emulator.dSYM" ] && `rm -rf emulator.dSYM`
	@#[ -f "emulator-test" ] && rm emulator-test
	@#[ -d "emulator-test.dSYM" ] && `rm -rf emulator-test.dSYM`
