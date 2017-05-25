# Architecture

## Shift Registers

The STM32F4 has limited GPIO pins, but we need a lot of I/O pins for all the displays and buttons.
The solution is shift registers - one pin on the board magically turns into 8 output pins!

In our code, we update the modules once per tick, allowing them to write new 8 bit values for the shift registers into a buffer, and at the end of the tick we apply those buffers to all shift registers in parallel, bit for bit.
To this end, the RCLK and SRCLK lines of all registers are connected, respectively.

## Buttons

For input pins, especially those for detecting button presses, it's a little more complicated.
All modules that have multiple buttons connect each of these between one shift register output pin, and connect them all to the same STM pin on the other side, with some diodes in between.
The code will then rapidly "poll" the buttons by cycling the shift register through (`0001` -> `0010` etc.).
The button polled in tick N will be read in tick N+1 (because the shift registers only get updated between logic ticks).
By caching the last-read button value and comparing it to the new value, we can detect if the button was pressed or released, and react accordingly.

## Bomb State Machine

The bomb object itself is actually a state machine.

 - `BS_READING_FLAGS` *(initial state)* The bomb stays in this state until it has read all flags.
 	The next state after that is determined by the "start" button (currently the capacitor button):
 	- if the button is down, it will enter `BS_WAITING`.
 	- otherwise, it will go straight to `BS_INITIALIZING_MODULES`.
 - `BS_WAITING` In this state, the bomb does fuck all.
 	When the start button is released, it goes to `BS_INITIALIZING_MODULES`.
 - `BS_INITIALIZING_MODULES` Here, all modules that are not yet marked as `MF_READY` are ticked until they are.
 	Typical initialization activities include filling an LCD screen, measuring initial ADC values, randomly generating the puzzles, etc.
 	When all modules are `MF_READY`, we go to `BS_COUNTDOWN`.
 - `BS_COUNTDOWN` You're in deep trouble now. The timer will keep counting down until all modules are `MF_COMPLETE` (the `MF_NEEDY` already count as complete).
 	If you make too many strikes or time runs out, the bomb will go to `BS_EXPLODED`, and god have mercy on your soul.
 	If you solve all modules, the bomb goes to `BS_DEFUSED`.
 - `BS_EXPLODED` Unless you did the smart thing and enabled mercy mode (`BF_MERCIFUL`), you now have an insufferable and incessant beeping to deal with.
 - `BS_DEFUSED` In this state, the bomb does nothing, but you've probably got a small high. Congratulations. Now try with fewer strikes or a lower timer, I dare you.

## LCD

The LCD module is very timing sensitive. Do not attempt to modify unless you have a priest present.
