CFLAGS=-Wall
LIBS=-lcheck

all: emulator

emulator: emu_shell.o
	gcc -o emulator emu_shell.o

emu_shell.o: src/emu_shell.c
	gcc $(CFLAGS) -c src/emu_shell.c

test: emulator-test
	./emulator-test

emulator-test: emu_shell.o emu_shell_test.o
	gcc -o emulator-test emu_shell.o emu_shell_test.o $(LIBS)
	#gcc -o emulator-test -g test/new_test.c -L/usr/local/lib $(LIBS)

emu_shell_test.o: test/new_test.c
	gcc $(CFLAGS) -c test/new_test.c

clean:
	@[ -f "emulator" ] && rm emulator
	@[ -d "emulator.dSYM" ] && `rm -rf emulator.dSYM`
	@[ -f "emulator-test" ] && rm emulator-test
	@[ -d "emulator-test.dSYM" ] && `rm -rf emulator-test.dSYM`
