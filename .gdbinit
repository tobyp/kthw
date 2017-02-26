define reload
	monitor reset halt
	load main.elf
	monitor reset init
	monitor reset halt
end

define restart
	monitor reset init
	monitor reset halt
	continue
end

define flash
	monitor reset halt
	monitor flash probe 0
	monitor flash write_image erase main.bin 0x08000000
	monitor reset run
end

target remote :3333
monitor reset halt
