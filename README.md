# Noteblock Tuner

Noteblock Tuner is a tool that allows you to tune noteblocks in Minecraft with a MIDI keyboard. To use it, start the program and select your input device. Then, in the game, simply point your crosshair at an untuned noteblock and press a valid note on your keyboard. It should translate that keypress to the number of right clicks required to tune to that note.

## Building

### Linux (Debian/Ubuntu)

First install dependencies:
```console
sudo apt install libx11-dev
sudo apt install librtmidi-dev
```

Next, open a terminal in the root directory of the project and run the makefile with the ```make``` command.

### Windows (MSYS2)

Install dependencies:
```console
pacman -S mingw-w64-x86_64-rtmidi
```

Next, open an MSYS2 terminal in the root directory of the project and run the makefile with the ```make``` command.
