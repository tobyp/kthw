EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:74xgxx
LIBS:ac-dc
LIBS:actel
LIBS:allegro
LIBS:Altera
LIBS:analog_devices
LIBS:battery_management
LIBS:bbd
LIBS:bosch
LIBS:brooktre
LIBS:cmos_ieee
LIBS:dc-dc
LIBS:diode
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:ir
LIBS:Lattice
LIBS:leds
LIBS:logo
LIBS:maxim
LIBS:mechanical
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic24mcu
LIBS:microchip_pic32mcu
LIBS:modules
LIBS:motor_drivers
LIBS:motors
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:Oscillators
LIBS:powerint
LIBS:Power_Management
LIBS:pspice
LIBS:references
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:silabs
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:transf
LIBS:triac_thyristor
LIBS:ttl_ieee
LIBS:video
LIBS:wiznet
LIBS:Worldsemi
LIBS:Xicor
LIBS:zetex
LIBS:Zilog
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title "KTHW"
Date "2017-05-07"
Rev ""
Comp ""
Comment1 ""
Comment2 "and the buzzer and beeper."
Comment3 "Will be encased inside the cube, together with the 9V battery, the power regulator,"
Comment4 "The Hub board, with female headers for the STM32F4Discovery Board."
$EndDescr
Text GLabel 2900 3100 0    60   Output ~ 0
TX
Text GLabel 3400 3100 2    60   Input ~ 0
RX
Text GLabel 2900 3000 0    60   Output ~ 0
SRCLK
Text GLabel 3400 3000 2    60   Output ~ 0
RCLK
Text GLabel 3400 2900 2    60   Input ~ 0
MO_ADC
Text GLabel 2900 3200 0    60   Output ~ 0
TI_TIM0
Text GLabel 2900 3300 0    60   Output ~ 0
TI_TIM1
Text GLabel 2900 3400 0    60   Output ~ 0
TI_TIM2
Text GLabel 2900 3500 0    60   Output ~ 0
TI_TIM3
Text GLabel 2900 3600 0    60   Output ~ 0
TI_BUZZ
Text GLabel 3400 3600 2    60   Output ~ 0
TI_STRCMP
Text GLabel 3400 4300 2    60   Output ~ 0
TI_FLAG0
Text GLabel 3400 4400 2    60   Output ~ 0
TI_FLAG1
Text GLabel 3400 4500 2    60   Input ~ 0
TI_FLAG0_IN
Text GLabel 3400 4600 2    60   Input ~ 0
TI_FLAG1_IN
$Sheet
S 8550 4650 1200 200 
U 59165D5E
F0 "KTHW Password" 60
F1 "kthw_password.sch" 60
$EndSheet
$Sheet
S 8550 3850 1200 200 
U 59172DBA
F0 "KTHW Wires" 60
F1 "kthw_wires.sch" 60
$EndSheet
$Sheet
S 8554 3446 1200 200 
U 5917EE44
F0 "KTHW Morse" 60
F1 "kthw_morse.sch" 60
$EndSheet
$Sheet
S 8550 3050 1200 200 
U 5917EE53
F0 "KTHW Simon Says" 60
F1 "kthw_simonsays.sch" 60
$EndSheet
Text GLabel 3400 3800 2    60   Input ~ 0
SS_BTN_IN
Text GLabel 3400 4200 2    60   Input ~ 0
WI_WIRE_IN
NoConn ~ 2900 2900
$Comp
L VDD #PWR2
U 1 1 59188F0E
P 5350 2250
F 0 "#PWR2" H 5350 2100 50  0001 C CNN
F 1 "VDD" H 5350 2400 50  0000 C CNN
F 2 "" H 5350 2250 50  0001 C CNN
F 3 "" H 5350 2250 50  0001 C CNN
	1    5350 2250
	1    0    0    -1  
$EndComp
NoConn ~ 3400 2800
NoConn ~ 2900 3800
NoConn ~ 2900 4300
NoConn ~ 2900 4400
NoConn ~ 2900 4600
NoConn ~ 2900 4800
NoConn ~ 2900 4900
$Comp
L CONN_02X25 J1
U 1 1 59189054
P 3150 3800
F 0 "J1" H 3150 5100 50  0000 C CNN
F 1 "CONN_02X25" V 3150 3800 50  0000 C CNN
F 2 "" H 3150 3050 50  0001 C CNN
F 3 "" H 3150 3050 50  0001 C CNN
	1    3150 3800
	1    0    0    -1  
$EndComp
NoConn ~ 3400 4900
NoConn ~ 3400 4800
NoConn ~ 3400 4700
NoConn ~ 3400 3700
NoConn ~ 3400 3200
NoConn ~ 3400 3300
NoConn ~ 3400 3400
NoConn ~ 3400 3500
$Comp
L GND #PWR8
U 1 1 59189124
P 2900 3700
F 0 "#PWR8" H 2900 3450 50  0001 C CNN
F 1 "GND" H 2900 3550 50  0000 C CNN
F 2 "" H 2900 3700 50  0001 C CNN
F 3 "" H 2900 3700 50  0001 C CNN
	1    2900 3700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR7
U 1 1 5918913C
P 2900 2800
F 0 "#PWR7" H 2900 2550 50  0001 C CNN
F 1 "GND" H 2900 2650 50  0000 C CNN
F 2 "" H 2900 2800 50  0001 C CNN
F 3 "" H 2900 2800 50  0001 C CNN
	1    2900 2800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR3
U 1 1 5918914F
P 2900 2600
F 0 "#PWR3" H 2900 2350 50  0001 C CNN
F 1 "GND" H 2900 2450 50  0000 C CNN
F 2 "" H 2900 2600 50  0001 C CNN
F 3 "" H 2900 2600 50  0001 C CNN
	1    2900 2600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR9
U 1 1 5918915F
P 2900 5000
F 0 "#PWR9" H 2900 4750 50  0001 C CNN
F 1 "GND" H 2900 4850 50  0000 C CNN
F 2 "" H 2900 5000 50  0001 C CNN
F 3 "" H 2900 5000 50  0001 C CNN
	1    2900 5000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 5918916F
P 3400 5000
F 0 "#PWR10" H 3400 4750 50  0001 C CNN
F 1 "GND" H 3400 4850 50  0000 C CNN
F 2 "" H 3400 5000 50  0001 C CNN
F 3 "" H 3400 5000 50  0001 C CNN
	1    3400 5000
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X25 J2
U 1 1 5918918A
P 4800 3800
F 0 "J2" H 4800 5100 50  0000 C CNN
F 1 "CONN_02X25" V 4800 3800 50  0000 C CNN
F 2 "" H 4800 3050 50  0001 C CNN
F 3 "" H 4800 3050 50  0001 C CNN
	1    4800 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 591891DE
P 4550 2600
F 0 "#PWR5" H 4550 2350 50  0001 C CNN
F 1 "GND" H 4550 2450 50  0000 C CNN
F 2 "" H 4550 2600 50  0001 C CNN
F 3 "" H 4550 2600 50  0001 C CNN
	1    4550 2600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR6
U 1 1 591891EF
P 5050 2600
F 0 "#PWR6" H 5050 2350 50  0001 C CNN
F 1 "GND" H 5050 2450 50  0000 C CNN
F 2 "" H 5050 2600 50  0001 C CNN
F 3 "" H 5050 2600 50  0001 C CNN
	1    5050 2600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR4
U 1 1 59189200
P 3400 2600
F 0 "#PWR4" H 3400 2350 50  0001 C CNN
F 1 "GND" H 3400 2450 50  0000 C CNN
F 2 "" H 3400 2600 50  0001 C CNN
F 3 "" H 3400 2600 50  0001 C CNN
	1    3400 2600
	0    -1   -1   0   
$EndComp
NoConn ~ 5050 2900
NoConn ~ 5050 3400
NoConn ~ 5050 3700
NoConn ~ 5050 3800
NoConn ~ 5050 3900
NoConn ~ 5050 4000
NoConn ~ 5050 4400
NoConn ~ 5050 4500
NoConn ~ 5050 4600
NoConn ~ 5050 4700
NoConn ~ 5050 4800
NoConn ~ 5050 4900
$Comp
L GND #PWR11
U 1 1 5918942E
P 4550 5000
F 0 "#PWR11" H 4550 4750 50  0001 C CNN
F 1 "GND" H 4550 4850 50  0000 C CNN
F 2 "" H 4550 5000 50  0001 C CNN
F 3 "" H 4550 5000 50  0001 C CNN
	1    4550 5000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 5918943F
P 5050 5000
F 0 "#PWR12" H 5050 4750 50  0001 C CNN
F 1 "GND" H 5050 4850 50  0000 C CNN
F 2 "" H 5050 5000 50  0001 C CNN
F 3 "" H 5050 5000 50  0001 C CNN
	1    5050 5000
	1    0    0    -1  
$EndComp
NoConn ~ 4550 4900
NoConn ~ 4550 4800
NoConn ~ 4550 4700
NoConn ~ 4550 4600
NoConn ~ 4550 4500
NoConn ~ 4550 4400
NoConn ~ 4550 4000
NoConn ~ 4550 3900
NoConn ~ 4550 3800
NoConn ~ 4550 3700
NoConn ~ 4550 3600
NoConn ~ 4550 2900
Text GLabel 3400 3900 2    60   Output ~ 0
MO_LED
Text GLabel 3400 4000 2    60   Input ~ 0
MO_BTN_IN
Text GLabel 3400 4100 2    60   Output ~ 0
WI_WIRE
Text GLabel 2900 3900 0    60   Output ~ 0
MO_FREQ0
Text GLabel 2900 4000 0    60   Output ~ 0
MO_FREQ1
Text GLabel 2900 4100 0    60   Output ~ 0
MO_FREQ2
Text GLabel 2900 4200 0    60   Output ~ 0
MO_FREQ3
Text GLabel 2900 4500 0    60   Output ~ 0
TI_BEEP
Text GLabel 2900 4700 0    60   Output ~ 0
SS_SER
Text GLabel 5050 3000 2    60   Output ~ 0
ME_STAGE
Text GLabel 5050 3100 2    60   Output ~ 0
ME_BTN
Text GLabel 5050 3200 2    60   Input ~ 0
ME_BTN_IN
Text GLabel 5050 3300 2    60   Input ~ 0
CP_BTN_IN
Text GLabel 5050 3500 2    60   Output ~ 0
ME_DISP
Text GLabel 5050 4100 2    60   Output ~ 0
PW_LCD
Text GLabel 5050 4200 2    60   Output ~ 0
PW_LCD_RS
Text GLabel 5050 4300 2    60   Output ~ 0
PW_LCD_EN
Text GLabel 4550 3000 0    60   Output ~ 0
ME_BTN0
Text GLabel 4550 3100 0    60   Output ~ 0
ME_BTN1
Text GLabel 4550 3200 0    60   Output ~ 0
ME_BTN2
Text GLabel 4550 3300 0    60   Output ~ 0
ME_BTN3
Text GLabel 4550 3400 0    60   Output ~ 0
CP_CAP0
Text GLabel 4550 3500 0    60   Output ~ 0
CP_CAP1
Text GLabel 4550 4100 0    60   Output ~ 0
PW_BTN
Text GLabel 4550 4300 0    60   Input ~ 0
PW_BTN_IN
NoConn ~ 4550 4200
$Sheet
S 8550 4250 1200 200 
U 5918A33D
F0 "KTHW Memory" 60
F1 "kthw_memory.sch" 60
$EndSheet
$Comp
L SW_SPST SW1
U 1 1 591B2DA5
P 4150 1650
F 0 "SW1" H 4150 1775 50  0000 C CNN
F 1 "SW_SPST" H 4150 1550 50  0000 C CNN
F 2 "" H 4150 1650 50  0001 C CNN
F 3 "" H 4150 1650 50  0001 C CNN
	1    4150 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 591B2DB4
P 3550 2050
F 0 "#PWR1" H 3550 1800 50  0001 C CNN
F 1 "GND" H 3550 1900 50  0000 C CNN
F 2 "" H 3550 2050 50  0001 C CNN
F 3 "" H 3550 2050 50  0001 C CNN
	1    3550 2050
	-1   0    0    -1  
$EndComp
Text GLabel 4900 5800 0    60   Input ~ 0
TI_BUZZ
Text GLabel 4900 5950 0    60   Input ~ 0
TI_BEEP
$Comp
L 7805 U1
U 1 1 591C609C
P 3550 1700
F 0 "U1" H 3700 1504 50  0000 C CNN
F 1 "7805" H 3550 1900 50  0000 C CNN
F 2 "" H 3550 1700 50  0001 C CNN
F 3 "" H 3550 1700 50  0001 C CNN
	1    3550 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2700 5250 2700
Wire Wire Line
	4350 2700 4550 2700
Wire Wire Line
	4350 2450 5250 2450
Wire Wire Line
	4250 2800 4550 2800
Wire Wire Line
	5350 2800 5050 2800
Wire Wire Line
	2650 2700 2900 2700
Wire Wire Line
	3400 2700 3650 2700
Wire Wire Line
	3650 2700 3650 2350
Connection ~ 3650 2350
Wire Wire Line
	2650 2700 2650 2350
Wire Wire Line
	4250 2350 4250 2800
Connection ~ 4250 2350
Wire Wire Line
	5250 2450 5250 2700
Wire Wire Line
	5350 2250 5350 3600
Connection ~ 5350 2350
Connection ~ 4350 2450
Wire Wire Line
	5350 3600 5050 3600
Connection ~ 5350 2800
Wire Wire Line
	2650 2350 5350 2350
Wire Wire Line
	4350 1650 4350 2700
Wire Wire Line
	3150 2050 3550 2050
Wire Wire Line
	3550 2050 3550 1950
Text GLabel 3950 1950 2    60   Output ~ 0
5V
Wire Wire Line
	3950 1650 3950 1950
$Sheet
S 8550 2650 1200 200 
U 590F6CA0
F0 "KTHW Timer" 60
F1 "kthw_timer.sch" 60
$EndSheet
$Comp
L Battery BT?
U 1 1 590FA86E
P 3150 1850
F 0 "BT?" H 3250 1950 50  0000 L CNN
F 1 "Battery" H 3250 1850 50  0000 L CNN
F 2 "" V 3150 1910 50  0001 C CNN
F 3 "" V 3150 1910 50  0001 C CNN
	1    3150 1850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
