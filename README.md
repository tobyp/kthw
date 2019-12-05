This repository includes schematics, code, and instructions for building our hardware clone of the device from Steel Crate Games' game ["Keep Talking and Nobody Explodes"](http://www.keeptalkinggame.com/).

## Media

#### Demo
![Demo](https://tobyp.github.io/kthw/kthw.mkv)

#### Timer Module
![Timer Module](https://tobyp.github.io/kthw/timer.jpg)

#### Morse Code
![Morse Code](https://tobyp.github.io/kthw/morse.jpg)

#### Simon Says
![Simon Says](https://tobyp.github.io/kthw/simon_says.jpg)

#### Wires/Capacitor
![Wires/Capacitor](https://tobyp.github.io/kthw/wires_capacitor.jpg)

#### Memory
![Memory](https://tobyp.github.io/kthw/memory.jpg)

#### Password
![Password](https://tobyp.github.io/kthw/password.jpg)

## Hardware

The code is written for an STM32F4 Discovery board, which you can probably get for around 25 €.
The rest of the materials probably cost another 25 €.
A complete list of required materials can be found in the [material list](MATERIALS.md).

There are also complete KiCad schematics in the [schematics](schematics) folder, along with some [assembly tips](ASSEMBLY.md).
 v
Our cube design requires 8 corner pieces, which you can 3D print from [this STL file](3dprints/corner.stl) (Designed for 6mm M2.5 screws with nuts. I lost the OpenSCAD file but I'm sure you can remake it pretty easily).

If you want to mess with the code, take a look at the [architecture description](ARCHITECTURE.md).

Lastly, there's a [quick reference how to play the game](MANUAL.md).

## Building The Software

The code does not use any libraries and requires only a GCC compiler and linker to build (prefix `arm-none-eabi`).
It can be uploaded to the board via USB using OpenOCD and the GDB debugger.
To read the console you will also need a 3.3V UART adapter.

From the repository root folder, run

	make
	openocd&
	arm-none-eabi-gdb -x .gdbinit

Use the `reload` command (defined in the `.gdbinit` file) to upload the software.

## License/Trademark

The code, schematics and 3d models are (c) 2017 Toby P. ([tobyp.net](http://www.tobyp.net)) and Thomas H., and licensed under the terms of the GNU GPL v3, see the file [LICENSE.txt](LICENSE.txt).

The files `startup.c`, `startup.h`, `stm32f407vg.h` and `stm32f407vg.ld` are no-brainers and released into the public domain.

The photographs are Copyright (c) 2017 Thomas H., all rights reserved. Do not distribute. Make your own.

The video is Copyright (c) 2017 Toby P. ([tobyp.net](http://www.tobyp.net)), all rights reserved. Do not distribute.

We are not affiliated with Steel Crate Games. This project is not endorsed by Steel Crate Games.
Steel Crate Games, Keep Talking and Nobody Explodes, and the Keep Talking and Nobody Explodes logo are all trademarks and/or registered trademarks of Steel Crate Games, Inc.