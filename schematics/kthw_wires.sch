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
LIBS:kthw_schematics-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title "KTHW Wires/Capacitor"
Date "2017-05-07"
Rev ""
Comp ""
Comment1 "While doing this, hold the capacitor button to delay initialization of the countdown."
Comment2 "Insert the wire that is to be cut BEFORE powering on, and any others after."
Comment3 "Wires are inserted as bridges from one header to the other. Every second pin is connected."
Comment4 "\"On the Subject of Wires\"/\"On the Subject of Capacitors\""
$EndDescr
$Comp
L CONN_01X15 J3
U 1 1 591730E3
P 7000 1750
F 0 "J3" H 7000 2550 50  0000 C CNN
F 1 "CONN_01X15" V 7100 1750 50  0000 C CNN
F 2 "" H 7000 1750 50  0001 C CNN
F 3 "" H 7000 1750 50  0001 C CNN
	1    7000 1750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 J4
U 1 1 591731CD
P 7500 1750
F 0 "J4" H 7500 2550 50  0000 C CNN
F 1 "CONN_01X15" V 7600 1750 50  0000 C CNN
F 2 "" H 7500 1750 50  0001 C CNN
F 3 "" H 7500 1750 50  0001 C CNN
	1    7500 1750
	-1   0    0    1   
$EndComp
$Comp
L 74HC595 U4
U 1 1 59174CF0
P 5000 1850
F 0 "U4" H 5150 2450 50  0000 C CNN
F 1 "74HC595" H 5000 1250 50  0000 C CNN
F 2 "" H 5000 1850 50  0001 C CNN
F 3 "" H 5000 1850 50  0001 C CNN
	1    5000 1850
	1    0    0    -1  
$EndComp
NoConn ~ 5700 2300
$Comp
L 1N4148 D7
U 1 1 591754D7
P 6350 1050
F 0 "D7" H 6350 1150 50  0000 C CNN
F 1 "1N4148" H 6350 950 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6350 875 50  0001 C CNN
F 3 "" H 6350 1050 50  0001 C CNN
	1    6350 1050
	-1   0    0    1   
$EndComp
$Comp
L 1N4148 D8
U 1 1 5917553E
P 6650 1250
F 0 "D8" H 6650 1350 50  0000 C CNN
F 1 "1N4148" H 6650 1150 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6650 1075 50  0001 C CNN
F 3 "" H 6650 1250 50  0001 C CNN
	1    6650 1250
	-1   0    0    1   
$EndComp
$Comp
L 1N4148 D9
U 1 1 5917568A
P 6350 1450
F 0 "D9" H 6350 1550 50  0000 C CNN
F 1 "1N4148" H 6350 1350 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6350 1275 50  0001 C CNN
F 3 "" H 6350 1450 50  0001 C CNN
	1    6350 1450
	-1   0    0    1   
$EndComp
$Comp
L 1N4148 D10
U 1 1 591756C2
P 6650 1650
F 0 "D10" H 6650 1750 50  0000 C CNN
F 1 "1N4148" H 6650 1550 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6650 1475 50  0001 C CNN
F 3 "" H 6650 1650 50  0001 C CNN
	1    6650 1650
	-1   0    0    1   
$EndComp
$Comp
L 1N4148 D11
U 1 1 591756F5
P 6350 1850
F 0 "D11" H 6350 1950 50  0000 C CNN
F 1 "1N4148" H 6350 1750 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6350 1675 50  0001 C CNN
F 3 "" H 6350 1850 50  0001 C CNN
	1    6350 1850
	-1   0    0    1   
$EndComp
$Comp
L 1N4148 D12
U 1 1 5917573E
P 6650 2050
F 0 "D12" H 6650 2150 50  0000 C CNN
F 1 "1N4148" H 6650 1950 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6650 1875 50  0001 C CNN
F 3 "" H 6650 2050 50  0001 C CNN
	1    6650 2050
	-1   0    0    1   
$EndComp
$Comp
L 1N4148 D13
U 1 1 59175777
P 6350 2250
F 0 "D13" H 6350 2350 50  0000 C CNN
F 1 "1N4148" H 6350 2150 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6350 2075 50  0001 C CNN
F 3 "" H 6350 2250 50  0001 C CNN
	1    6350 2250
	-1   0    0    1   
$EndComp
$Comp
L 1N4148 D14
U 1 1 591757B1
P 6650 2450
F 0 "D14" H 6650 2550 50  0000 C CNN
F 1 "1N4148" H 6650 2350 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_Horizontal_RM10" H 6650 2275 50  0001 C CNN
F 3 "" H 6650 2450 50  0001 C CNN
	1    6650 2450
	-1   0    0    1   
$EndComp
Text GLabel 3750 1400 0    60   Input ~ 0
WI_WIRE
Text GLabel 7950 2600 2    60   Output ~ 0
WI_WIRE_IN
NoConn ~ 6800 1150
NoConn ~ 6800 1350
NoConn ~ 6800 1550
NoConn ~ 6800 1750
NoConn ~ 6800 1950
NoConn ~ 6800 2150
NoConn ~ 6800 2350
NoConn ~ 7700 2350
NoConn ~ 7700 2150
NoConn ~ 7700 1950
NoConn ~ 7700 1750
NoConn ~ 7700 1550
NoConn ~ 7700 1350
NoConn ~ 7700 1150
$Comp
L GND #PWR20
U 1 1 59176263
P 4700 2500
F 0 "#PWR20" H 4700 2250 50  0001 C CNN
F 1 "GND" H 4700 2350 50  0000 C CNN
F 2 "" H 4700 2500 50  0001 C CNN
F 3 "" H 4700 2500 50  0001 C CNN
	1    4700 2500
	1    0    0    -1  
$EndComp
Text GLabel 3750 1600 0    60   Input ~ 0
SRCLK
Text GLabel 3750 1900 0    60   Input ~ 0
RCLK
$Comp
L 74HC595 U6
U 1 1 59178342
P 5000 5250
F 0 "U6" H 5150 5850 50  0000 C CNN
F 1 "74HC595" H 5000 4650 50  0000 C CNN
F 2 "" H 5000 5250 50  0001 C CNN
F 3 "" H 5000 5250 50  0001 C CNN
	1    5000 5250
	1    0    0    -1  
$EndComp
NoConn ~ 5700 5700
$Comp
L 74HC595 U5
U 1 1 59178389
P 5000 3850
F 0 "U5" H 5150 4450 50  0000 C CNN
F 1 "74HC595" H 5000 3250 50  0000 C CNN
F 2 "" H 5000 3850 50  0001 C CNN
F 3 "" H 5000 3850 50  0001 C CNN
	1    5000 3850
	1    0    0    -1  
$EndComp
NoConn ~ 5700 4300
$Comp
L LED D15
U 1 1 59178944
P 6150 3400
F 0 "D15" H 6150 3500 50  0000 C CNN
F 1 "LED" H 6150 3300 50  0000 C CNN
F 2 "" H 6150 3400 50  0001 C CNN
F 3 "" H 6150 3400 50  0001 C CNN
	1    6150 3400
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 591789CC
P 5850 3400
F 0 "R2" V 5930 3400 50  0000 C CNN
F 1 "1K" V 5850 3400 50  0000 C CNN
F 2 "" V 5780 3400 50  0001 C CNN
F 3 "" H 5850 3400 50  0001 C CNN
	1    5850 3400
	0    1    1    0   
$EndComp
$Comp
L LED D16
U 1 1 59178AD2
P 6750 3500
F 0 "D16" H 6750 3600 50  0000 C CNN
F 1 "LED" H 6750 3400 50  0000 C CNN
F 2 "" H 6750 3500 50  0001 C CNN
F 3 "" H 6750 3500 50  0001 C CNN
	1    6750 3500
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 59178AD8
P 6450 3500
F 0 "R3" V 6530 3500 50  0000 C CNN
F 1 "1K" V 6450 3500 50  0000 C CNN
F 2 "" V 6380 3500 50  0001 C CNN
F 3 "" H 6450 3500 50  0001 C CNN
	1    6450 3500
	0    1    1    0   
$EndComp
$Comp
L LED D17
U 1 1 59178B19
P 6150 3600
F 0 "D17" H 6150 3700 50  0000 C CNN
F 1 "LED" H 6150 3500 50  0000 C CNN
F 2 "" H 6150 3600 50  0001 C CNN
F 3 "" H 6150 3600 50  0001 C CNN
	1    6150 3600
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 59178B1F
P 5850 3600
F 0 "R4" V 5930 3600 50  0000 C CNN
F 1 "1K" V 5850 3600 50  0000 C CNN
F 2 "" V 5780 3600 50  0001 C CNN
F 3 "" H 5850 3600 50  0001 C CNN
	1    5850 3600
	0    1    1    0   
$EndComp
$Comp
L LED D18
U 1 1 59178B25
P 6750 3700
F 0 "D18" H 6750 3800 50  0000 C CNN
F 1 "LED" H 6750 3600 50  0000 C CNN
F 2 "" H 6750 3700 50  0001 C CNN
F 3 "" H 6750 3700 50  0001 C CNN
	1    6750 3700
	-1   0    0    1   
$EndComp
$Comp
L R R5
U 1 1 59178B2B
P 6450 3700
F 0 "R5" V 6530 3700 50  0000 C CNN
F 1 "1K" V 6450 3700 50  0000 C CNN
F 2 "" V 6380 3700 50  0001 C CNN
F 3 "" H 6450 3700 50  0001 C CNN
	1    6450 3700
	0    1    1    0   
$EndComp
$Comp
L LED D19
U 1 1 59178BED
P 6150 3800
F 0 "D19" H 6150 3900 50  0000 C CNN
F 1 "LED" H 6150 3700 50  0000 C CNN
F 2 "" H 6150 3800 50  0001 C CNN
F 3 "" H 6150 3800 50  0001 C CNN
	1    6150 3800
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 59178BF3
P 5850 3800
F 0 "R6" V 5930 3800 50  0000 C CNN
F 1 "1K" V 5850 3800 50  0000 C CNN
F 2 "" V 5780 3800 50  0001 C CNN
F 3 "" H 5850 3800 50  0001 C CNN
	1    5850 3800
	0    1    1    0   
$EndComp
$Comp
L LED D20
U 1 1 59178BF9
P 6750 3900
F 0 "D20" H 6750 4000 50  0000 C CNN
F 1 "LED" H 6750 3800 50  0000 C CNN
F 2 "" H 6750 3900 50  0001 C CNN
F 3 "" H 6750 3900 50  0001 C CNN
	1    6750 3900
	-1   0    0    1   
$EndComp
$Comp
L R R7
U 1 1 59178BFF
P 6450 3900
F 0 "R7" V 6530 3900 50  0000 C CNN
F 1 "1K" V 6450 3900 50  0000 C CNN
F 2 "" V 6380 3900 50  0001 C CNN
F 3 "" H 6450 3900 50  0001 C CNN
	1    6450 3900
	0    1    1    0   
$EndComp
$Comp
L LED D21
U 1 1 59178C05
P 6150 4000
F 0 "D21" H 6150 4100 50  0000 C CNN
F 1 "LED" H 6150 3900 50  0000 C CNN
F 2 "" H 6150 4000 50  0001 C CNN
F 3 "" H 6150 4000 50  0001 C CNN
	1    6150 4000
	-1   0    0    1   
$EndComp
$Comp
L R R8
U 1 1 59178C0B
P 5850 4000
F 0 "R8" V 5930 4000 50  0000 C CNN
F 1 "1K" V 5850 4000 50  0000 C CNN
F 2 "" V 5780 4000 50  0001 C CNN
F 3 "" H 5850 4000 50  0001 C CNN
	1    5850 4000
	0    1    1    0   
$EndComp
$Comp
L LED D22
U 1 1 59178C11
P 6750 4100
F 0 "D22" H 6750 4200 50  0000 C CNN
F 1 "LED" H 6750 4000 50  0000 C CNN
F 2 "" H 6750 4100 50  0001 C CNN
F 3 "" H 6750 4100 50  0001 C CNN
	1    6750 4100
	-1   0    0    1   
$EndComp
$Comp
L R R9
U 1 1 59178C17
P 6450 4100
F 0 "R9" V 6530 4100 50  0000 C CNN
F 1 "1K" V 6450 4100 50  0000 C CNN
F 2 "" V 6380 4100 50  0001 C CNN
F 3 "" H 6450 4100 50  0001 C CNN
	1    6450 4100
	0    1    1    0   
$EndComp
$Comp
L LED D23
U 1 1 59179700
P 6150 4800
F 0 "D23" H 6150 4900 50  0000 C CNN
F 1 "LED" H 6150 4700 50  0000 C CNN
F 2 "" H 6150 4800 50  0001 C CNN
F 3 "" H 6150 4800 50  0001 C CNN
	1    6150 4800
	-1   0    0    1   
$EndComp
$Comp
L R R10
U 1 1 59179706
P 5850 4800
F 0 "R10" V 5930 4800 50  0000 C CNN
F 1 "1K" V 5850 4800 50  0000 C CNN
F 2 "" V 5780 4800 50  0001 C CNN
F 3 "" H 5850 4800 50  0001 C CNN
	1    5850 4800
	0    1    1    0   
$EndComp
$Comp
L LED D24
U 1 1 5917970C
P 6750 4900
F 0 "D24" H 6750 5000 50  0000 C CNN
F 1 "LED" H 6750 4800 50  0000 C CNN
F 2 "" H 6750 4900 50  0001 C CNN
F 3 "" H 6750 4900 50  0001 C CNN
	1    6750 4900
	-1   0    0    1   
$EndComp
$Comp
L R R11
U 1 1 59179712
P 6450 4900
F 0 "R11" V 6530 4900 50  0000 C CNN
F 1 "1K" V 6450 4900 50  0000 C CNN
F 2 "" V 6380 4900 50  0001 C CNN
F 3 "" H 6450 4900 50  0001 C CNN
	1    6450 4900
	0    1    1    0   
$EndComp
$Comp
L LED D25
U 1 1 59179718
P 6150 5000
F 0 "D25" H 6150 5100 50  0000 C CNN
F 1 "LED" H 6150 4900 50  0000 C CNN
F 2 "" H 6150 5000 50  0001 C CNN
F 3 "" H 6150 5000 50  0001 C CNN
	1    6150 5000
	-1   0    0    1   
$EndComp
$Comp
L R R12
U 1 1 5917971E
P 5850 5000
F 0 "R12" V 5930 5000 50  0000 C CNN
F 1 "1K" V 5850 5000 50  0000 C CNN
F 2 "" V 5780 5000 50  0001 C CNN
F 3 "" H 5850 5000 50  0001 C CNN
	1    5850 5000
	0    1    1    0   
$EndComp
$Comp
L LED D26
U 1 1 59179724
P 6750 5100
F 0 "D26" H 6750 5200 50  0000 C CNN
F 1 "LED" H 6750 5000 50  0000 C CNN
F 2 "" H 6750 5100 50  0001 C CNN
F 3 "" H 6750 5100 50  0001 C CNN
	1    6750 5100
	-1   0    0    1   
$EndComp
$Comp
L R R13
U 1 1 5917972A
P 6450 5100
F 0 "R13" V 6530 5100 50  0000 C CNN
F 1 "1K" V 6450 5100 50  0000 C CNN
F 2 "" V 6380 5100 50  0001 C CNN
F 3 "" H 6450 5100 50  0001 C CNN
	1    6450 5100
	0    1    1    0   
$EndComp
$Comp
L LED D27
U 1 1 59179730
P 6150 5200
F 0 "D27" H 6150 5300 50  0000 C CNN
F 1 "LED" H 6150 5100 50  0000 C CNN
F 2 "" H 6150 5200 50  0001 C CNN
F 3 "" H 6150 5200 50  0001 C CNN
	1    6150 5200
	-1   0    0    1   
$EndComp
$Comp
L R R14
U 1 1 59179736
P 5850 5200
F 0 "R14" V 5930 5200 50  0000 C CNN
F 1 "1K" V 5850 5200 50  0000 C CNN
F 2 "" V 5780 5200 50  0001 C CNN
F 3 "" H 5850 5200 50  0001 C CNN
	1    5850 5200
	0    1    1    0   
$EndComp
$Comp
L LED D28
U 1 1 5917973C
P 6750 5300
F 0 "D28" H 6750 5400 50  0000 C CNN
F 1 "LED" H 6750 5200 50  0000 C CNN
F 2 "" H 6750 5300 50  0001 C CNN
F 3 "" H 6750 5300 50  0001 C CNN
	1    6750 5300
	-1   0    0    1   
$EndComp
$Comp
L R R15
U 1 1 59179742
P 6450 5300
F 0 "R15" V 6530 5300 50  0000 C CNN
F 1 "1K" V 6450 5300 50  0000 C CNN
F 2 "" V 6380 5300 50  0001 C CNN
F 3 "" H 6450 5300 50  0001 C CNN
	1    6450 5300
	0    1    1    0   
$EndComp
$Comp
L LED D29
U 1 1 59179748
P 6150 5400
F 0 "D29" H 6150 5500 50  0000 C CNN
F 1 "LED" H 6150 5300 50  0000 C CNN
F 2 "" H 6150 5400 50  0001 C CNN
F 3 "" H 6150 5400 50  0001 C CNN
	1    6150 5400
	-1   0    0    1   
$EndComp
$Comp
L R R16
U 1 1 5917974E
P 5850 5400
F 0 "R16" V 5930 5400 50  0000 C CNN
F 1 "1K" V 5850 5400 50  0000 C CNN
F 2 "" V 5780 5400 50  0001 C CNN
F 3 "" H 5850 5400 50  0001 C CNN
	1    5850 5400
	0    1    1    0   
$EndComp
$Comp
L LED D30
U 1 1 59179754
P 6750 5500
F 0 "D30" H 6750 5600 50  0000 C CNN
F 1 "LED" H 6750 5400 50  0000 C CNN
F 2 "" H 6750 5500 50  0001 C CNN
F 3 "" H 6750 5500 50  0001 C CNN
	1    6750 5500
	-1   0    0    1   
$EndComp
$Comp
L R R17
U 1 1 5917975A
P 6450 5500
F 0 "R17" V 6530 5500 50  0000 C CNN
F 1 "1K" V 6450 5500 50  0000 C CNN
F 2 "" V 6380 5500 50  0001 C CNN
F 3 "" H 6450 5500 50  0001 C CNN
	1    6450 5500
	0    1    1    0   
$EndComp
$Comp
L GND #PWR21
U 1 1 5917B4CF
P 6900 4500
F 0 "#PWR21" H 6900 4250 50  0001 C CNN
F 1 "GND" H 6900 4350 50  0000 C CNN
F 2 "" H 6900 4500 50  0001 C CNN
F 3 "" H 6900 4500 50  0001 C CNN
	1    6900 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR22
U 1 1 5917B56A
P 6900 5900
F 0 "#PWR22" H 6900 5650 50  0001 C CNN
F 1 "GND" H 6900 5750 50  0000 C CNN
F 2 "" H 6900 5900 50  0001 C CNN
F 3 "" H 6900 5900 50  0001 C CNN
	1    6900 5900
	1    0    0    -1  
$EndComp
Text GLabel 3750 3400 0    60   Input ~ 0
CP_CAP0
Text GLabel 3750 4800 0    60   Input ~ 0
CP_CAP1
$Comp
L SW_Push SW7
U 1 1 59189BC6
P 4400 6150
F 0 "SW7" H 4450 6250 50  0000 L CNN
F 1 "SW_Push" H 4400 6090 50  0000 C CNN
F 2 "" H 4400 6350 50  0001 C CNN
F 3 "" H 4400 6350 50  0001 C CNN
	1    4400 6150
	1    0    0    -1  
$EndComp
Text GLabel 4800 6150 2    60   Output ~ 0
CP_BTN_IN
$Comp
L LED D31
U 1 1 5919923B
P 4350 6650
F 0 "D31" H 4350 6750 50  0000 C CNN
F 1 "LED" H 4350 6550 50  0000 C CNN
F 2 "" H 4350 6650 50  0001 C CNN
F 3 "" H 4350 6650 50  0001 C CNN
	1    4350 6650
	-1   0    0    1   
$EndComp
$Comp
L R R18
U 1 1 59199242
P 4050 6650
F 0 "R18" V 4130 6650 50  0000 C CNN
F 1 "1K" V 4050 6650 50  0000 C CNN
F 2 "" V 3980 6650 50  0001 C CNN
F 3 "" H 4050 6650 50  0001 C CNN
	1    4050 6650
	0    1    1    0   
$EndComp
$Comp
L GND #PWR23
U 1 1 5919924B
P 4600 6750
F 0 "#PWR23" H 4600 6500 50  0001 C CNN
F 1 "GND" H 4600 6600 50  0000 C CNN
F 2 "" H 4600 6750 50  0001 C CNN
F 3 "" H 4600 6750 50  0001 C CNN
	1    4600 6750
	1    0    0    -1  
$EndComp
Text GLabel 3800 6650 0    60   Input ~ 0
CMP_WI
Wire Wire Line
	4700 2400 4700 2500
Connection ~ 4700 2500
Wire Wire Line
	4700 1200 4700 1300
Wire Wire Line
	4200 1700 4300 1700
Wire Wire Line
	3750 1400 4300 1400
Connection ~ 4200 1700
Connection ~ 4200 1200
Wire Wire Line
	4300 2000 4300 2500
Wire Wire Line
	4300 2500 4700 2500
Wire Wire Line
	4200 1200 4700 1200
Wire Wire Line
	4200 1200 4200 6150
Wire Wire Line
	5700 2100 5800 2100
Wire Wire Line
	5900 2000 5700 2000
Wire Wire Line
	5800 2100 5800 2450
Wire Wire Line
	5800 2450 6500 2450
Wire Wire Line
	5900 2000 5900 2250
Wire Wire Line
	5900 2250 6200 2250
Wire Wire Line
	5700 1900 6000 1900
Wire Wire Line
	6000 1900 6000 2050
Wire Wire Line
	6000 2050 6500 2050
Wire Wire Line
	5700 1800 6100 1800
Wire Wire Line
	6100 1800 6100 1850
Wire Wire Line
	6100 1850 6200 1850
Wire Wire Line
	5700 1700 6100 1700
Wire Wire Line
	6100 1700 6100 1650
Wire Wire Line
	6100 1650 6500 1650
Wire Wire Line
	5700 1600 6000 1600
Wire Wire Line
	6000 1600 6000 1450
Wire Wire Line
	6000 1450 6200 1450
Wire Wire Line
	5700 1500 5900 1500
Wire Wire Line
	5900 1500 5900 1250
Wire Wire Line
	5900 1250 6500 1250
Wire Wire Line
	5700 1400 5800 1400
Wire Wire Line
	5800 1400 5800 1050
Wire Wire Line
	5800 1050 6200 1050
Wire Wire Line
	7700 1050 7800 1050
Wire Wire Line
	7800 1050 7800 2600
Wire Wire Line
	7800 1250 7700 1250
Wire Wire Line
	7800 1450 7700 1450
Connection ~ 7800 1250
Wire Wire Line
	7800 1650 7700 1650
Connection ~ 7800 1450
Wire Wire Line
	7800 1850 7700 1850
Connection ~ 7800 1650
Wire Wire Line
	7800 2050 7700 2050
Connection ~ 7800 1850
Wire Wire Line
	7800 2250 7700 2250
Connection ~ 7800 2050
Wire Wire Line
	7800 2450 7700 2450
Connection ~ 7800 2250
Wire Wire Line
	6500 2250 6800 2250
Wire Wire Line
	6500 1850 6800 1850
Wire Wire Line
	6500 1450 6800 1450
Wire Wire Line
	6500 1050 6800 1050
Wire Wire Line
	7800 2600 7950 2600
Connection ~ 7800 2450
Wire Wire Line
	3750 1600 4300 1600
Wire Wire Line
	3750 1900 4300 1900
Wire Wire Line
	4700 5800 4700 5900
Connection ~ 4700 5900
Wire Wire Line
	4700 4600 4700 4700
Wire Wire Line
	4700 4400 4700 4500
Connection ~ 4700 4500
Wire Wire Line
	4700 3200 4700 3300
Wire Wire Line
	4200 3700 4300 3700
Wire Wire Line
	4200 4600 4700 4600
Wire Wire Line
	4200 5100 4300 5100
Wire Wire Line
	4300 3600 4000 3600
Wire Wire Line
	4000 5000 4300 5000
Wire Wire Line
	4300 3900 3900 3900
Wire Wire Line
	3900 5300 4300 5300
Connection ~ 3900 5300
Wire Wire Line
	3750 3400 4300 3400
Wire Wire Line
	3750 4800 4300 4800
Connection ~ 4200 4600
Connection ~ 4200 3700
Connection ~ 4200 5100
Connection ~ 4200 3200
Wire Wire Line
	4300 4000 4300 4500
Wire Wire Line
	4300 5400 4300 5900
Wire Wire Line
	6300 3400 6900 3400
Wire Wire Line
	6900 3400 6900 4500
Wire Wire Line
	6900 3600 6300 3600
Wire Wire Line
	6900 3800 6300 3800
Wire Wire Line
	6900 4000 6300 4000
Wire Wire Line
	5700 4100 6300 4100
Wire Wire Line
	6300 3900 5700 3900
Wire Wire Line
	5700 3700 6300 3700
Wire Wire Line
	6300 3500 5700 3500
Connection ~ 6900 3600
Connection ~ 6900 3500
Connection ~ 6900 3800
Connection ~ 6900 3700
Connection ~ 6900 4000
Connection ~ 6900 3900
Wire Wire Line
	6300 4800 6900 4800
Wire Wire Line
	6900 4800 6900 5900
Wire Wire Line
	6900 5000 6300 5000
Wire Wire Line
	6900 5200 6300 5200
Wire Wire Line
	6900 5400 6300 5400
Wire Wire Line
	5700 5500 6300 5500
Wire Wire Line
	6300 5300 5700 5300
Wire Wire Line
	5700 5100 6300 5100
Wire Wire Line
	6300 4900 5700 4900
Connection ~ 6900 5000
Connection ~ 6900 4900
Connection ~ 6900 5200
Connection ~ 6900 5100
Connection ~ 6900 5400
Connection ~ 6900 5300
Wire Wire Line
	6900 4500 4300 4500
Wire Wire Line
	6900 5900 4300 5900
Connection ~ 6900 4100
Connection ~ 6900 5500
Wire Wire Line
	3900 1900 3900 5300
Wire Wire Line
	4000 1600 4000 5000
Connection ~ 4000 1600
Connection ~ 4000 3600
Connection ~ 3900 3900
Connection ~ 3900 1900
Wire Wire Line
	4200 3200 4700 3200
Wire Wire Line
	4800 6150 4600 6150
Wire Wire Line
	4500 6650 4600 6650
Wire Wire Line
	4600 6650 4600 6750
Wire Wire Line
	3800 6650 3900 6650
$Comp
L VDD #PWR19
U 1 1 591E7128
P 4200 1200
F 0 "#PWR19" H 4200 1050 50  0001 C CNN
F 1 "VDD" H 4200 1350 50  0000 C CNN
F 2 "" H 4200 1200 50  0001 C CNN
F 3 "" H 4200 1200 50  0001 C CNN
	1    4200 1200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
