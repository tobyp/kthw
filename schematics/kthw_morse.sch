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
Sheet 4 7
Title "KTHW Morse"
Date "2017-05-07"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 "The potentiometer (preferrably a dial) is used to set the response frequency."
Comment4 "\"On the Subject of Morse Code\""
$EndDescr
$Comp
L LTS-6980HR AFF2
U 1 1 591808A7
P 8150 2800
F 0 "AFF2" H 8150 3350 50  0000 C CNN
F 1 "LTS-6980HR" H 8150 2350 50  0000 C CNN
F 2 "" H 8150 2800 50  0001 C CNN
F 3 "" H 8150 2800 50  0001 C CNN
	1    8150 2800
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U8
U 1 1 591808AE
P 6350 2850
F 0 "U8" H 6500 3450 50  0000 C CNN
F 1 "74HC595" H 6350 2250 50  0000 C CNN
F 2 "" H 6350 2850 50  0001 C CNN
F 3 "" H 6350 2850 50  0001 C CNN
	1    6350 2850
	1    0    0    -1  
$EndComp
$Comp
L R R28
U 1 1 591808B5
P 7400 2400
F 0 "R28" V 7480 2400 50  0000 C CNN
F 1 "1K" V 7400 2400 50  0000 C CNN
F 2 "" V 7330 2400 50  0001 C CNN
F 3 "" H 7400 2400 50  0001 C CNN
	1    7400 2400
	0    1    1    0   
$EndComp
$Comp
L R R29
U 1 1 591808BC
P 7200 2500
F 0 "R29" V 7280 2500 50  0000 C CNN
F 1 "1K" V 7200 2500 50  0000 C CNN
F 2 "" V 7130 2500 50  0001 C CNN
F 3 "" H 7200 2500 50  0001 C CNN
	1    7200 2500
	0    1    1    0   
$EndComp
$Comp
L R R30
U 1 1 591808C3
P 7400 2600
F 0 "R30" V 7480 2600 50  0000 C CNN
F 1 "1K" V 7400 2600 50  0000 C CNN
F 2 "" V 7330 2600 50  0001 C CNN
F 3 "" H 7400 2600 50  0001 C CNN
	1    7400 2600
	0    1    1    0   
$EndComp
$Comp
L R R31
U 1 1 591808CA
P 7200 2700
F 0 "R31" V 7280 2700 50  0000 C CNN
F 1 "1K" V 7200 2700 50  0000 C CNN
F 2 "" V 7130 2700 50  0001 C CNN
F 3 "" H 7200 2700 50  0001 C CNN
	1    7200 2700
	0    1    1    0   
$EndComp
$Comp
L R R32
U 1 1 591808D1
P 7400 2800
F 0 "R32" V 7480 2800 50  0000 C CNN
F 1 "1K" V 7400 2800 50  0000 C CNN
F 2 "" V 7330 2800 50  0001 C CNN
F 3 "" H 7400 2800 50  0001 C CNN
	1    7400 2800
	0    1    1    0   
$EndComp
$Comp
L R R33
U 1 1 591808D8
P 7200 2900
F 0 "R33" V 7280 2900 50  0000 C CNN
F 1 "1K" V 7200 2900 50  0000 C CNN
F 2 "" V 7130 2900 50  0001 C CNN
F 3 "" H 7200 2900 50  0001 C CNN
	1    7200 2900
	0    1    1    0   
$EndComp
$Comp
L R R34
U 1 1 591808DF
P 7400 3000
F 0 "R34" V 7480 3000 50  0000 C CNN
F 1 "1K" V 7400 3000 50  0000 C CNN
F 2 "" V 7330 3000 50  0001 C CNN
F 3 "" H 7400 3000 50  0001 C CNN
	1    7400 3000
	0    1    1    0   
$EndComp
Text GLabel 5100 1000 0    60   Input ~ 0
MO_FREQ0
Text GLabel 5100 3800 0    60   Input ~ 0
MO_FREQ2
Text GLabel 5100 2400 0    60   Input ~ 0
MO_FREQ1
Text GLabel 5100 5200 0    60   Input ~ 0
MO_FREQ3
$Comp
L R R35
U 1 1 591808EA
P 7200 3100
F 0 "R35" V 7280 3100 50  0000 C CNN
F 1 "1K" V 7200 3100 50  0000 C CNN
F 2 "" V 7130 3100 50  0001 C CNN
F 3 "" H 7200 3100 50  0001 C CNN
	1    7200 3100
	0    1    1    0   
$EndComp
NoConn ~ 7050 3300
$Comp
L LTS-6980HR AFF1
U 1 1 591808F2
P 8150 1400
F 0 "AFF1" H 8150 1950 50  0000 C CNN
F 1 "LTS-6980HR" H 8150 950 50  0000 C CNN
F 2 "" H 8150 1400 50  0001 C CNN
F 3 "" H 8150 1400 50  0001 C CNN
	1    8150 1400
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U7
U 1 1 591808F9
P 6350 1450
F 0 "U7" H 6500 2050 50  0000 C CNN
F 1 "74HC595" H 6350 850 50  0000 C CNN
F 2 "" H 6350 1450 50  0001 C CNN
F 3 "" H 6350 1450 50  0001 C CNN
	1    6350 1450
	1    0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 59180900
P 7400 1000
F 0 "R19" V 7480 1000 50  0000 C CNN
F 1 "1K" V 7400 1000 50  0000 C CNN
F 2 "" V 7330 1000 50  0001 C CNN
F 3 "" H 7400 1000 50  0001 C CNN
	1    7400 1000
	0    1    1    0   
$EndComp
$Comp
L R R20
U 1 1 59180907
P 7200 1100
F 0 "R20" V 7280 1100 50  0000 C CNN
F 1 "1K" V 7200 1100 50  0000 C CNN
F 2 "" V 7130 1100 50  0001 C CNN
F 3 "" H 7200 1100 50  0001 C CNN
	1    7200 1100
	0    1    1    0   
$EndComp
$Comp
L R R21
U 1 1 5918090E
P 7400 1200
F 0 "R21" V 7480 1200 50  0000 C CNN
F 1 "1K" V 7400 1200 50  0000 C CNN
F 2 "" V 7330 1200 50  0001 C CNN
F 3 "" H 7400 1200 50  0001 C CNN
	1    7400 1200
	0    1    1    0   
$EndComp
$Comp
L R R22
U 1 1 59180915
P 7200 1300
F 0 "R22" V 7280 1300 50  0000 C CNN
F 1 "1K" V 7200 1300 50  0000 C CNN
F 2 "" V 7130 1300 50  0001 C CNN
F 3 "" H 7200 1300 50  0001 C CNN
	1    7200 1300
	0    1    1    0   
$EndComp
$Comp
L R R23
U 1 1 5918091C
P 7400 1400
F 0 "R23" V 7480 1400 50  0000 C CNN
F 1 "1K" V 7400 1400 50  0000 C CNN
F 2 "" V 7330 1400 50  0001 C CNN
F 3 "" H 7400 1400 50  0001 C CNN
	1    7400 1400
	0    1    1    0   
$EndComp
$Comp
L R R25
U 1 1 59180923
P 7200 1500
F 0 "R25" V 7280 1500 50  0000 C CNN
F 1 "1K" V 7200 1500 50  0000 C CNN
F 2 "" V 7130 1500 50  0001 C CNN
F 3 "" H 7200 1500 50  0001 C CNN
	1    7200 1500
	0    1    1    0   
$EndComp
$Comp
L R R26
U 1 1 5918092A
P 7400 1600
F 0 "R26" V 7480 1600 50  0000 C CNN
F 1 "1K" V 7400 1600 50  0000 C CNN
F 2 "" V 7330 1600 50  0001 C CNN
F 3 "" H 7400 1600 50  0001 C CNN
	1    7400 1600
	0    1    1    0   
$EndComp
$Comp
L R R27
U 1 1 59180931
P 7200 1700
F 0 "R27" V 7280 1700 50  0000 C CNN
F 1 "1K" V 7200 1700 50  0000 C CNN
F 2 "" V 7130 1700 50  0001 C CNN
F 3 "" H 7200 1700 50  0001 C CNN
	1    7200 1700
	0    1    1    0   
$EndComp
NoConn ~ 7050 1900
$Comp
L LTS-6980HR AFF4
U 1 1 59180939
P 8150 5600
F 0 "AFF4" H 8150 6150 50  0000 C CNN
F 1 "LTS-6980HR" H 8150 5150 50  0000 C CNN
F 2 "" H 8150 5600 50  0001 C CNN
F 3 "" H 8150 5600 50  0001 C CNN
	1    8150 5600
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U10
U 1 1 59180940
P 6350 5650
F 0 "U10" H 6500 6250 50  0000 C CNN
F 1 "74HC595" H 6350 5050 50  0000 C CNN
F 2 "" H 6350 5650 50  0001 C CNN
F 3 "" H 6350 5650 50  0001 C CNN
	1    6350 5650
	1    0    0    -1  
$EndComp
$Comp
L R R44
U 1 1 59180947
P 7400 5200
F 0 "R44" V 7480 5200 50  0000 C CNN
F 1 "1K" V 7400 5200 50  0000 C CNN
F 2 "" V 7330 5200 50  0001 C CNN
F 3 "" H 7400 5200 50  0001 C CNN
	1    7400 5200
	0    1    1    0   
$EndComp
$Comp
L R R45
U 1 1 5918094E
P 7200 5300
F 0 "R45" V 7280 5300 50  0000 C CNN
F 1 "1K" V 7200 5300 50  0000 C CNN
F 2 "" V 7130 5300 50  0001 C CNN
F 3 "" H 7200 5300 50  0001 C CNN
	1    7200 5300
	0    1    1    0   
$EndComp
$Comp
L R R46
U 1 1 59180955
P 7400 5400
F 0 "R46" V 7480 5400 50  0000 C CNN
F 1 "1K" V 7400 5400 50  0000 C CNN
F 2 "" V 7330 5400 50  0001 C CNN
F 3 "" H 7400 5400 50  0001 C CNN
	1    7400 5400
	0    1    1    0   
$EndComp
$Comp
L R R47
U 1 1 5918095C
P 7200 5500
F 0 "R47" V 7280 5500 50  0000 C CNN
F 1 "1K" V 7200 5500 50  0000 C CNN
F 2 "" V 7130 5500 50  0001 C CNN
F 3 "" H 7200 5500 50  0001 C CNN
	1    7200 5500
	0    1    1    0   
$EndComp
$Comp
L R R48
U 1 1 59180963
P 7400 5600
F 0 "R48" V 7480 5600 50  0000 C CNN
F 1 "1K" V 7400 5600 50  0000 C CNN
F 2 "" V 7330 5600 50  0001 C CNN
F 3 "" H 7400 5600 50  0001 C CNN
	1    7400 5600
	0    1    1    0   
$EndComp
$Comp
L R R49
U 1 1 5918096A
P 7200 5700
F 0 "R49" V 7280 5700 50  0000 C CNN
F 1 "1K" V 7200 5700 50  0000 C CNN
F 2 "" V 7130 5700 50  0001 C CNN
F 3 "" H 7200 5700 50  0001 C CNN
	1    7200 5700
	0    1    1    0   
$EndComp
$Comp
L R R50
U 1 1 59180971
P 7400 5800
F 0 "R50" V 7480 5800 50  0000 C CNN
F 1 "1K" V 7400 5800 50  0000 C CNN
F 2 "" V 7330 5800 50  0001 C CNN
F 3 "" H 7400 5800 50  0001 C CNN
	1    7400 5800
	0    1    1    0   
$EndComp
$Comp
L R R51
U 1 1 59180978
P 7200 5900
F 0 "R51" V 7280 5900 50  0000 C CNN
F 1 "1K" V 7200 5900 50  0000 C CNN
F 2 "" V 7130 5900 50  0001 C CNN
F 3 "" H 7200 5900 50  0001 C CNN
	1    7200 5900
	0    1    1    0   
$EndComp
NoConn ~ 7050 6100
$Comp
L LTS-6980HR AFF3
U 1 1 59180980
P 8150 4200
F 0 "AFF3" H 8150 4750 50  0000 C CNN
F 1 "LTS-6980HR" H 8150 3750 50  0000 C CNN
F 2 "" H 8150 4200 50  0001 C CNN
F 3 "" H 8150 4200 50  0001 C CNN
	1    8150 4200
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U9
U 1 1 59180987
P 6350 4250
F 0 "U9" H 6500 4850 50  0000 C CNN
F 1 "74HC595" H 6350 3650 50  0000 C CNN
F 2 "" H 6350 4250 50  0001 C CNN
F 3 "" H 6350 4250 50  0001 C CNN
	1    6350 4250
	1    0    0    -1  
$EndComp
$Comp
L R R36
U 1 1 5918098E
P 7400 3800
F 0 "R36" V 7480 3800 50  0000 C CNN
F 1 "1K" V 7400 3800 50  0000 C CNN
F 2 "" V 7330 3800 50  0001 C CNN
F 3 "" H 7400 3800 50  0001 C CNN
	1    7400 3800
	0    1    1    0   
$EndComp
$Comp
L R R37
U 1 1 59180995
P 7200 3900
F 0 "R37" V 7280 3900 50  0000 C CNN
F 1 "1K" V 7200 3900 50  0000 C CNN
F 2 "" V 7130 3900 50  0001 C CNN
F 3 "" H 7200 3900 50  0001 C CNN
	1    7200 3900
	0    1    1    0   
$EndComp
$Comp
L R R38
U 1 1 5918099C
P 7400 4000
F 0 "R38" V 7480 4000 50  0000 C CNN
F 1 "1K" V 7400 4000 50  0000 C CNN
F 2 "" V 7330 4000 50  0001 C CNN
F 3 "" H 7400 4000 50  0001 C CNN
	1    7400 4000
	0    1    1    0   
$EndComp
$Comp
L R R39
U 1 1 591809A3
P 7200 4100
F 0 "R39" V 7280 4100 50  0000 C CNN
F 1 "1K" V 7200 4100 50  0000 C CNN
F 2 "" V 7130 4100 50  0001 C CNN
F 3 "" H 7200 4100 50  0001 C CNN
	1    7200 4100
	0    1    1    0   
$EndComp
$Comp
L R R40
U 1 1 591809AA
P 7400 4200
F 0 "R40" V 7480 4200 50  0000 C CNN
F 1 "1K" V 7400 4200 50  0000 C CNN
F 2 "" V 7330 4200 50  0001 C CNN
F 3 "" H 7400 4200 50  0001 C CNN
	1    7400 4200
	0    1    1    0   
$EndComp
$Comp
L R R41
U 1 1 591809B1
P 7200 4300
F 0 "R41" V 7280 4300 50  0000 C CNN
F 1 "1K" V 7200 4300 50  0000 C CNN
F 2 "" V 7130 4300 50  0001 C CNN
F 3 "" H 7200 4300 50  0001 C CNN
	1    7200 4300
	0    1    1    0   
$EndComp
$Comp
L R R42
U 1 1 591809B8
P 7400 4400
F 0 "R42" V 7480 4400 50  0000 C CNN
F 1 "1K" V 7400 4400 50  0000 C CNN
F 2 "" V 7330 4400 50  0001 C CNN
F 3 "" H 7400 4400 50  0001 C CNN
	1    7400 4400
	0    1    1    0   
$EndComp
$Comp
L R R43
U 1 1 591809BF
P 7200 4500
F 0 "R43" V 7280 4500 50  0000 C CNN
F 1 "1K" V 7200 4500 50  0000 C CNN
F 2 "" V 7130 4500 50  0001 C CNN
F 3 "" H 7200 4500 50  0001 C CNN
	1    7200 4500
	0    1    1    0   
$EndComp
NoConn ~ 7050 4700
Wire Wire Line
	7350 2500 7550 2500
Wire Wire Line
	7350 2700 7550 2700
Wire Wire Line
	7350 2900 7550 2900
Wire Wire Line
	7350 3100 7750 3100
Wire Wire Line
	7750 3100 7750 3300
Wire Wire Line
	7750 3300 8750 3300
Wire Wire Line
	8750 3300 8750 3050
Wire Wire Line
	7050 2400 7250 2400
Wire Wire Line
	7050 2600 7250 2600
Wire Wire Line
	7050 2800 7250 2800
Wire Wire Line
	7050 3000 7250 3000
Wire Wire Line
	6050 3400 6050 3500
Wire Wire Line
	8850 3500 8850 2350
Wire Wire Line
	8850 2350 8750 2350
Wire Wire Line
	8750 2450 8850 2450
Connection ~ 8850 2450
Connection ~ 6050 3500
Wire Wire Line
	6050 2200 6050 2300
Wire Wire Line
	7350 1100 7550 1100
Wire Wire Line
	7350 1300 7550 1300
Wire Wire Line
	7350 1500 7550 1500
Wire Wire Line
	7350 1700 7750 1700
Wire Wire Line
	7750 1700 7750 1900
Wire Wire Line
	7750 1900 8750 1900
Wire Wire Line
	8750 1900 8750 1650
Wire Wire Line
	7050 1000 7250 1000
Wire Wire Line
	7050 1200 7250 1200
Wire Wire Line
	7050 1400 7250 1400
Wire Wire Line
	7050 1600 7250 1600
Wire Wire Line
	6050 2000 6050 2100
Wire Wire Line
	8850 2100 8850 950 
Wire Wire Line
	8850 950  8750 950 
Wire Wire Line
	8750 1050 8850 1050
Connection ~ 8850 1050
Connection ~ 6050 2100
Wire Wire Line
	6050 800  6050 900 
Wire Wire Line
	7350 5300 7550 5300
Wire Wire Line
	7350 5500 7550 5500
Wire Wire Line
	7350 5700 7550 5700
Wire Wire Line
	7350 5900 7750 5900
Wire Wire Line
	7750 5900 7750 6100
Wire Wire Line
	7750 6100 8750 6100
Wire Wire Line
	8750 6100 8750 5850
Wire Wire Line
	7050 5200 7250 5200
Wire Wire Line
	7050 5400 7250 5400
Wire Wire Line
	7050 5600 7250 5600
Wire Wire Line
	7050 5800 7250 5800
Wire Wire Line
	6050 6200 6050 6300
Wire Wire Line
	8850 6300 8850 5150
Wire Wire Line
	8850 5150 8750 5150
Wire Wire Line
	8750 5250 8850 5250
Connection ~ 8850 5250
Connection ~ 6050 6300
Wire Wire Line
	6050 5000 6050 5100
Wire Wire Line
	7350 3900 7550 3900
Wire Wire Line
	7350 4100 7550 4100
Wire Wire Line
	7350 4300 7550 4300
Wire Wire Line
	7350 4500 7750 4500
Wire Wire Line
	7750 4500 7750 4700
Wire Wire Line
	7750 4700 8750 4700
Wire Wire Line
	8750 4700 8750 4450
Wire Wire Line
	7050 3800 7250 3800
Wire Wire Line
	7050 4000 7250 4000
Wire Wire Line
	7050 4200 7250 4200
Wire Wire Line
	7050 4400 7250 4400
Wire Wire Line
	6050 4800 6050 4900
Wire Wire Line
	8850 4900 8850 3750
Wire Wire Line
	8850 3750 8750 3750
Wire Wire Line
	8750 3850 8850 3850
Connection ~ 8850 3850
Connection ~ 6050 4900
Wire Wire Line
	6050 3600 6050 3700
Wire Wire Line
	5550 800  5550 5500
Wire Wire Line
	5550 1300 5650 1300
Wire Wire Line
	5550 2200 6050 2200
Wire Wire Line
	5550 2700 5650 2700
Wire Wire Line
	5550 3600 6050 3600
Wire Wire Line
	5550 4100 5650 4100
Wire Wire Line
	5550 5000 6050 5000
Wire Wire Line
	5550 5500 5650 5500
Wire Wire Line
	5650 1200 5350 1200
Wire Wire Line
	5350 1200 5350 5400
Wire Wire Line
	5100 2600 5650 2600
Wire Wire Line
	5350 4000 5650 4000
Connection ~ 5350 2600
Wire Wire Line
	5350 5400 5650 5400
Connection ~ 5350 4000
Wire Wire Line
	5650 1500 5250 1500
Wire Wire Line
	5250 1500 5250 5700
Wire Wire Line
	5100 2900 5650 2900
Wire Wire Line
	5250 4300 5650 4300
Connection ~ 5250 2900
Wire Wire Line
	5250 5700 5650 5700
Connection ~ 5250 4300
Wire Wire Line
	5100 1000 5650 1000
Wire Wire Line
	5100 2400 5650 2400
Wire Wire Line
	5650 3800 5100 3800
Wire Wire Line
	5100 5200 5650 5200
Connection ~ 5550 2200
Connection ~ 5550 1300
Connection ~ 5550 3600
Connection ~ 5550 2700
Connection ~ 5550 5000
Connection ~ 5550 4100
Connection ~ 5550 800 
$Comp
L VDD #PWR24
U 1 1 59180A34
P 5550 800
F 0 "#PWR24" H 5550 650 50  0001 C CNN
F 1 "VDD" H 5550 950 50  0000 C CNN
F 2 "" H 5550 800 50  0001 C CNN
F 3 "" H 5550 800 50  0001 C CNN
	1    5550 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 800  6050 800 
$Comp
L GND #PWR26
U 1 1 59180A3B
P 8850 2100
F 0 "#PWR26" H 8850 1850 50  0001 C CNN
F 1 "GND" H 8850 1950 50  0000 C CNN
F 2 "" H 8850 2100 50  0001 C CNN
F 3 "" H 8850 2100 50  0001 C CNN
	1    8850 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR29
U 1 1 59180A41
P 8850 3500
F 0 "#PWR29" H 8850 3250 50  0001 C CNN
F 1 "GND" H 8850 3350 50  0000 C CNN
F 2 "" H 8850 3500 50  0001 C CNN
F 3 "" H 8850 3500 50  0001 C CNN
	1    8850 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR31
U 1 1 59180A47
P 8850 4900
F 0 "#PWR31" H 8850 4650 50  0001 C CNN
F 1 "GND" H 8850 4750 50  0000 C CNN
F 2 "" H 8850 4900 50  0001 C CNN
F 3 "" H 8850 4900 50  0001 C CNN
	1    8850 4900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR33
U 1 1 59180A4D
P 8850 6300
F 0 "#PWR33" H 8850 6050 50  0001 C CNN
F 1 "GND" H 8850 6150 50  0000 C CNN
F 2 "" H 8850 6300 50  0001 C CNN
F 3 "" H 8850 6300 50  0001 C CNN
	1    8850 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1600 5650 2100
Wire Wire Line
	5650 2100 8850 2100
Wire Wire Line
	5650 3000 5650 3500
Wire Wire Line
	5650 3500 8850 3500
Wire Wire Line
	5650 4400 5650 4900
Wire Wire Line
	5650 4900 8850 4900
Wire Wire Line
	5650 5800 5650 6300
Wire Wire Line
	5650 6300 8850 6300
$Comp
L LED D32
U 1 1 59180D31
P 3550 1450
F 0 "D32" H 3550 1550 50  0000 C CNN
F 1 "LED" H 3550 1350 50  0000 C CNN
F 2 "" H 3550 1450 50  0001 C CNN
F 3 "" H 3550 1450 50  0001 C CNN
	1    3550 1450
	-1   0    0    1   
$EndComp
$Comp
L R R24
U 1 1 59180E8C
P 3250 1450
F 0 "R24" V 3330 1450 50  0000 C CNN
F 1 "1K" V 3250 1450 50  0000 C CNN
F 2 "" V 3180 1450 50  0001 C CNN
F 3 "" H 3250 1450 50  0001 C CNN
	1    3250 1450
	0    1    1    0   
$EndComp
$Comp
L GND #PWR25
U 1 1 591819F5
P 3800 1550
F 0 "#PWR25" H 3800 1300 50  0001 C CNN
F 1 "GND" H 3800 1400 50  0000 C CNN
F 2 "" H 3800 1550 50  0001 C CNN
F 3 "" H 3800 1550 50  0001 C CNN
	1    3800 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1450 3800 1450
Wire Wire Line
	3800 1450 3800 1550
Text GLabel 3000 1450 0    60   Input ~ 0
MO_LED
Wire Wire Line
	3000 1450 3100 1450
$Comp
L POT RV2
U 1 1 59182162
P 3250 3050
F 0 "RV2" V 3075 3050 50  0000 C CNN
F 1 "POT" V 3150 3050 50  0000 C CNN
F 2 "" H 3250 3050 50  0001 C CNN
F 3 "" H 3250 3050 50  0001 C CNN
	1    3250 3050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR28
U 1 1 59182335
P 3250 3300
F 0 "#PWR28" H 3250 3050 50  0001 C CNN
F 1 "GND" H 3250 3150 50  0000 C CNN
F 2 "" H 3250 3300 50  0001 C CNN
F 3 "" H 3250 3300 50  0001 C CNN
	1    3250 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3300 3250 3200
$Comp
L VDD #PWR27
U 1 1 59182470
P 3250 2800
F 0 "#PWR27" H 3250 2650 50  0001 C CNN
F 1 "VDD" H 3250 2950 50  0000 C CNN
F 2 "" H 3250 2800 50  0001 C CNN
F 3 "" H 3250 2800 50  0001 C CNN
	1    3250 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2800 3250 2900
Text GLabel 3000 3050 0    60   Output ~ 0
MO_ADC
Wire Wire Line
	3000 3050 3100 3050
$Comp
L SW_Push SW8
U 1 1 59183526
P 3450 4800
F 0 "SW8" H 3500 4900 50  0000 L CNN
F 1 "SW_Push" H 3450 4740 50  0000 C CNN
F 2 "" H 3450 5000 50  0001 C CNN
F 3 "" H 3450 5000 50  0001 C CNN
	1    3450 4800
	1    0    0    -1  
$EndComp
Text GLabel 3000 4800 0    60   Output ~ 0
MO_BTN_IN
Wire Wire Line
	3000 4800 3250 4800
$Comp
L VDD #PWR30
U 1 1 5918374A
P 3800 4700
F 0 "#PWR30" H 3800 4550 50  0001 C CNN
F 1 "VDD" H 3800 4850 50  0000 C CNN
F 2 "" H 3800 4700 50  0001 C CNN
F 3 "" H 3800 4700 50  0001 C CNN
	1    3800 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4700 3800 4800
Wire Wire Line
	3800 4800 3650 4800
Text GLabel 5100 2600 0    60   Input ~ 0
SRCLK
Text GLabel 5100 2900 0    60   Input ~ 0
RCLK
$Comp
L LED D33
U 1 1 59198F2C
P 3600 6000
F 0 "D33" H 3600 6100 50  0000 C CNN
F 1 "LED" H 3600 5900 50  0000 C CNN
F 2 "" H 3600 6000 50  0001 C CNN
F 3 "" H 3600 6000 50  0001 C CNN
	1    3600 6000
	-1   0    0    1   
$EndComp
$Comp
L R R52
U 1 1 59198F33
P 3300 6000
F 0 "R52" V 3380 6000 50  0000 C CNN
F 1 "1K" V 3300 6000 50  0000 C CNN
F 2 "" V 3230 6000 50  0001 C CNN
F 3 "" H 3300 6000 50  0001 C CNN
	1    3300 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	3750 6000 3850 6000
Wire Wire Line
	3850 6000 3850 6100
$Comp
L GND #PWR32
U 1 1 59198F3C
P 3850 6100
F 0 "#PWR32" H 3850 5850 50  0001 C CNN
F 1 "GND" H 3850 5950 50  0000 C CNN
F 2 "" H 3850 6100 50  0001 C CNN
F 3 "" H 3850 6100 50  0001 C CNN
	1    3850 6100
	1    0    0    -1  
$EndComp
Text GLabel 3050 6000 0    60   Input ~ 0
CMP_MO
Wire Wire Line
	3050 6000 3150 6000
$EndSCHEMATC