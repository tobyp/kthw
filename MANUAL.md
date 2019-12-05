# How to play

 - Choose a serial number. Typically 8–10 digits long, half letters half digits, but ending in a digit.
 - [*optional/currently useless*] Randomly decide how many batteries you want to attach (if you have any)
 - [*optional/currently useless*] Decide what indicators you want (there's a list in the manual, and they can be lit or unlit)
 - [*optional/currently useless*] Decide whether to attach a parallel port.
 - Set the flags (see section below) according to the choices you made earlier, and also to select the desired strike limit (0 means first mistake → 💥) and time limit (if you choose 0, you're stupid and deserve what's coming to you.)
 - Choose and insert a random sequence of 3-6 "wires" (see Wires section of the [Assembly Notes](ASSEMBLY.md)) of red, blue, yellow, white or black for the wires module (the order matters!)
 - Insert the key.

To start playing immediately:
 - Turn the key! (and good luck to you.)

If you want to dump this monster you just configured on someone else:
 - Carefully put the device down so its weight keeps the capacitor button pressed.
 - Turn the key. (If the timer starts, the button wasn't correctly pressed. Go to step 1, do not collect $200.)
 - Carefully lure your victim to the device and get them to pick it up. 

We recommend "TickTock Mode" for use on unwitting victims, to let them immediately know they fucked up.
We also recommend making yourself scarce immediately or at least getting ear protectors.

## Flags

There are two blue banks of DIP switches on the timer module. You can use these to configure the characteristics, timer and strike limit of your device.
They're read once, immediately after turning the key, and will then be ignored. (So no, you can't cheat and increase your timer...)

Left DIP Bank: Strike/Timer configuration (left to right):

 - Timer: 8 min
 - Timer: 4 min
 - Timer: 2 min
 - Timer: 1 min
 - Timer: 30 s
 - Timer: 15 s
 - Strikes: 2
 - Strikes: 1

(To calculate the actual settings, add the strike/timer values of all switches that are ON, e.g. 010100 and 11 = 5 min, 3 strikes)

Right DIP Bank: Characteristics and other settings (left to right, Set these to match whatever ports/batteries/serial number you attach):

 - "TickTock Mode" (leave OFF if you're in a situation where ticking would make people a *liiiiitle bit too nervous...*)
 - "Merciful Mode" (if ON, there will only be a 2 second "beep" when you fail, instead of a horrifying, insufferable, neverending wail)
 - Lit `CAR` indicator (Currently unused, required by The Button)
 - Lit `FRK` indicator (Currently unused, required by The Button)
 - Parallel port attached (Currently unused, required by Complicated Wires)
 - Two or more batteries attached (Currently unused, required by Complicated Wires)
 - Serial number ends in an even digit (required by Wires and Complicated Wires)
 - Serial number contains a vowel (required by Simon Says)

## UART

To test the device, attach to the UART port on the timer panel.

Pins (top to bottom):
 - GND
 - N/C
 - TX input (currently unused by software)
 - RX output
