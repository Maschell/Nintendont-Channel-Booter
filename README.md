Nintendont Channel Booter
=====================
When this homebrew is run through the Wii U Homebrew Launcher, it will boot the [Nintendont Channel](https://gbatemp.net/threads/nintendont.349258/#Setup) in Wii Mode, skipping controller and screen option prompts. It will also only show the screen on the TV, the GamePad can be turned on when necessary.

## Usage
1. Download the package from [Releases](https://github.com/Brawl345/Nintendont-Channel-Booter/releases)
2. Put it on your SD card
3. Launch through the homebrew launcher... but that is not the intended usage!

### Coldboot Haxchi
The intended usage is to use this via Coldboot Haxchi so that you can boot Nintendont without having to use the GamePad or connect any wiimotes and just use e.g. your GameCube controllers! It also has the side effect that it doesn't turn on the GamePad.
1. Rename the ELF to "mocha.elf"
2. Put it in SD://wiiu/apps/mocha/mocha.elf
3. Boot "Mocha CFW" through Coldboot Haxchi (you can navigate the menu via the SYNC button: one press = go down, two presses rapidly = boot)

## Changing the title id
1. Change the title id in "main.c" on line 58 (if you don't know it, convert the ASCII representation to HEX, e.g. DWFA for WiiFlow = 0x44574641)
2. Optionally, you can also set the screen type on line 40
3. Compile it with devkitPPC


## Building

For building you need: 
- [dynamic_libs](https://github.com/Maschell/dynamic_libs/tree/lib) for access to the functions.
- [libutils](https://github.com/Maschell/libutils) for common functions.

Install them (in this order) according to their README's. Don't forget the dependencies of the libs itself.

## Building with Docker
Without setting up a developing envrionment on your host machine you are still able to build this application via Docker.

```
# Run this command once to get the builder.
docker build . -t nintendontbooter-builder

# Run this command to compile the project.
docker run -it --rm -v ${PWD}:/project nintendontbooter-builder make
```

## Credits
Slightliy modified version of [hbl2hbc](https://github.com/FIX94/hbl2hbc) by FIX94.
