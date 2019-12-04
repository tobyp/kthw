#!/usr/bin/env python3

import sys


def main():
	impossibles = ["ABCDEFGHIJKLMNOPQRSTUVWXYZ" for i in range(5)]
	print("static const struct word words[] = {")
	word_count = 0
	for line in sys.stdin:
		word = line.strip()
		if not word:
			continue

		word_count += 1
		if len(word) != 5:
			print(f"Password {word!r} is the wrong length; the module requires 5 character passwords")
			return 1

		print(f"\t{{\"{word}\"}},")

		for i, c in enumerate(word):
			impossibles[i] = impossibles[i].replace(c, "")
	print("};\n")

	if word_count < 1:
		print("There must be at least one password in the file.")
		return 1

	print("static const struct slot_impossible impossibles[5]")
	for i, slot_impossible in enumerate(impossibles):
		if len(slot_impossible) < 5:  # 6 letters per slot, and up to 5 may need to be changed to make undesirable words impossible
			print(f"There are not enough characters that are impossible at slot[{i}] to guarantee a collision free random initialization of the module!")
			return 1

		print(f"\t{{{len(slot_impossible)}, \"{slot_impossible}\"}},")
	print("};\n")


if __name__ == '__main__':
	main()
