# README
</br>
This project is a research project into the emulation of an 8080 chipset. The emulator is semi-functional in the sense that I can run it, but the opcodes have not been tested for accuracy yet. I am trying to write it in only C and plan to emulate the hardware using SDL. Any comments or insights are welcome :)

To run the program, clone repository, combine the four invaders files you bought into one file called invaders, and put it into the res folder. Next, open the Makefile and replace the path of those SDL2 libraries with the path on your computer. I installed SDL using brew, so the paths should be correct if you do the same. Finally run make and then ./emulator to run the program.
