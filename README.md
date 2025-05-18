# CPBoy

CPBoy is a work in progress DMG GameBoy emulator for the fx-CP400. It is based on the [Peanut-GB emulator by deltabeard](https://github.com/deltabeard/Peanut-GB) and is ported by [diddyholz](https://github.com/diddyholz/CPBoy/).

Many games run with fullspeed with only one frame being skipped. Unfortunately, to make the emulator as fast as it is on such a low performing hardware, some accuracy had to be sacrificied which may cause some unexpected bugs with some roms.

## Getting Started

You will need to have the [Hollyhock-3 CFW](https://github.com/ClasspadDev/hollyhock-3/) installed. After that, extract the CPBoy.zip file from the [latest release](https://github.com/ClasspadDev/CPBoy/releases) to the root of your calculator. You should then have the following file structure on your calculator:
```
├── run.bin (Hollyhock launcher)
├── CPBoy.bin (Main CPBoy executable)
└── CPBoy/
    └── roms/
        └── ** Put your roms in here **
``` 

To load your Gameboy ROMs, put them into the `/CPBoy/roms/` directory. They should have the file ending `.gb`. CPBoy should then automatically detect the roms.


## Controls

The controls can be changed in the "Settings" tab in CPBoy.

These are the default controls:

| GB Action | Calculator key |
| --------- | -------------- |
| A         | EXE            |
| B         | +              |
| SELECT    | SHIFT          |
| START     | CLEAR          |
| UP        | UP             |
| DOWN      | DOWN           |
| LEFT      | LEFT           |
| RIGHT     | RIGHT          |
| Open Menu | (-)          |


## Games That Don't Work

 - Gameboy Colour games that are not backwards compatible with the Gameboy
 - Pokemon Pinball
 - Metroid 2 (Samus goes invisible in some areas)
 - Turok 2 (Crashes upon death)

If you encounter any issues with games, I will add them to this list.


## Building

If you want to build the emulator from source you will need the [Hollyhock-3 SDK + Newlib](https://github.com/ClasspadDev/hollyhock-3). Then, run ´make´ in your terminal.


## License

This project is licensed under the MIT License.

## Compatability

| Game Title | Status   | Updated  |
| ---------- | -------- | -------- |
| Tetris     | Playable | 17/09/22 |
| Tetris 2   | Playable | 17/09/22 |
|Pokemon Red |Unplayable| 29/01/23 |
|Mario Land 2|Playable|29/01/23|
|Mario Land|Playable|29/01/23|
|Pokemon Blue|Playable|29/01/23|
|Turok 2|occasional crashes|29/01/23|
|Pokemon Gold/Silver|Playable|29/01/23|
|Metroid 2|Visual Bugs|29/01/23|
|The Legend of Zelda Links Awakening|Playable|29/01/23|
|Donkey Kong Land|Playable|29/01/23|
|Kirby's Dreamland|Playable|29/01/23|
|Wordle|Playable|29/01/23|
|Pokemon Blue Randomizer|Playable|29/01/23|
