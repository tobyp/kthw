# Assembly Notes

## Overall Notes

 - Drill the screw holes in the corners first. Ensure they actually line up.
 - Use a "Hub Board" with pin headers.
 	Solder the wires to the pins on one end, then stick the STM board on the other side.
 		Jumper cables will become unreliable if you connect/remove often.
 			Also, it's really hard to solder pin headers on the pad side of a perfboard.
 - Print or copy the shift register pin layout.
 	Meditate upon how you need to mirror this when you're looking at the bottom.
 		Resign yourself to the fact that you will mess it up at least once.
 		Rejoice in the fact that you will know it by heart when you're done.
 - Solder the components onto the board first.
 	Place them all nicely, hold/tape them there, then solder two pins (at two opposite corners for larger components) to keep then there.
 - Next, add flat uninsulated wire "rails" on the board for VCC and Ground.
 	Don't forget to connect OE and SCLR pins to GND/VCC respectively.
 - Add uninsulated wire "rails" for each clock signal, and connect all shift register clocks to that "rail".
 	Much easier to manage than "hopping" from register to register.
 - Solder one end of a long wire, about 30cm, for each input/output/"rail" that needs to attach to the hub board.
 	Prefer litz wire or other flexible wire for these inter-board connections.
 	You will need to bend/move them out of the way when assembling the modules, to make room for the innards.
 - Lastly, use insulated wires for the other connections.
 - Add the buzzers last to avoid your ears falling off during testing.
 - Put Wires/Capacitor opposite the timer module so you can rest the device on the button.
 - For multi-port inputs/outputs, e.g. multi-digit 7-segment displays, the port labelled 0 is the least significant.
 - Either place LEDs close to the board, or somewhere they won't be bent around a lot from handling.
 - Try to place the completion lights prominently and consistently in the top right corner.
 	They're important visual cues.
 - If the tick-tock beeper is too loud, putting a piece of tape over the hole might help.

## Hub Board

 - Use uninsulated wire "rails" for the clocks/VCC/GND. This is much nicer than soldering together 6 wire ends.

## Timer Module

 - Drill the hole for the key switch before you solder anything (but after you've decided on component placement).
 - The least significant bit of each flag shift register goes to the right switch on the DIP bank (from a player's perspective).

## Simon Says

 - Place the buttons near the center and the lights near the edge. Much harder to accidentally press a button while handling the device.
 - Use colored tape/marker/paint for the key caps if you don't have all the colors you need.

## Morse

 - If you want to mount your potentiometer through the board, drill the hole before you solder anything (but after you've decided on component placement).

## Password

 - Make sure you know whether the LCD board's pins are at the top or bottom of the screen (you may need to rotate it).
 - VCC for the LCD is on 5V, not 3.3V. Experiment wit VCC/V0/Backlight voltages. Be aware these conditions may change between battery and USB power situations.

## Memory

 - The left button is the least significant bit of the button-polling shift register.
 - The left button label display is `GP_MEM0_SER`.

## Wires/Capacitor

 - Use a button that will be pressed when the device is resting on this module's side.
 - Double check you have the bargraphs in the right order.
 - In the original, the wires are arranged vertically. The player must be able to recognize where "up" is for the wires in order to solve this module.
 - Make your "wires". These are actually resistors (see `wires.c` for values) that should be wrapped in heat-shrink tubes of the appropriate color.
 	You may need to add solder/fold the wire to ensure good contact in the pin headers.
 	Use the UART interface to see what colors the device can see.
