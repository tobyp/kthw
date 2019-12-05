#!/usr/bin/env python3

# KTHW - Hardware Clone of Keep Talking and Nobody Explodes
# Copyright (C) 2019 Toby P.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import decimal
import sys

MORSE_CODE = {
	"A": ".-",
	"B": "-...",
	"C": "-.-.",
	"D": "-..",
	"E": ".",
	"F": "..-.",
	"G": "--.",
	"H": "....",
	"I": "..",
	"J": ".---",
	"K": "-.-",
	"L": ".-..",
	"M": "--",
	"N": "-.",
	"O": "---",
	"P": ".--.",
	"Q": "--.-",
	"R": ".-.",
	"S": "...",
	"T": "-",
	"U": "..-",
	"V": "...-",
	"W": ".--",
	"X": "-..-",
	"Y": "-.--",
	"Z": "--..",
}


def main():
	print("static struct morse_seq morse_seqs[] = {")
	for line in sys.stdin:
		line = line.strip()
		if not line:
			continue
		word, frequency = line.split(None, 1)

		try:
			morse_word = " ".join(MORSE_CODE[c] for c in word) + "\t"
		except LookupError:
			print("Word {word} contains unsupported characters", file=sys.stderr)
			continue

		word_bits = 0
		for morse_piece in morse_word:
			if morse_piece == '.':
				word_bits = word_bits << 2 | 0b01
			elif morse_piece == '-':
				word_bits = word_bits << 4 | 0b0111
			elif morse_piece == ' ':
				word_bits = word_bits << 2 | 0b00
			elif morse_piece == '\t':
				word_bits = word_bits << 6 | 0b000000
		if morse_piece in (' ', '\t'):  # ending on a space
			word_bits <<= 1
		word_bit_count = word_bits.bit_length()
		word_byte_count = (word_bit_count + 7) // 8
		# we need the bits left-aligned when they are put in a byte string, i.e. right-padded, not left
		word_bits <<= (word_byte_count * 8) - word_bit_count
		word_bytes = word_bits.to_bytes(word_byte_count, 'big')
		word_bytes_str = ', '.join(f'0x{c:02x}' for c in word_bytes)

		frequency_decimal = decimal.Decimal(frequency) * 1000
		if frequency_decimal % 1 != 0 or frequency_decimal < 0 or frequency_decimal > 9999:
			print(f"Frequency {frequency} is out of range", file=sys.stderr)
			continue

		print(f"\t{{\"{word}\", {{{word_bytes_str}}}, {word_bit_count}, {int(frequency_decimal)}}},")
	print("};")


if __name__ == '__main__':
	main()
