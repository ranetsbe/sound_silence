#!/bin/sh
i=0

for i in {0..13}
do
	file1="tests/sound.i${i}"
	file2="tests/sound.o${i}"

	./sound.o "$file1" "$i"

	if diff $file2 "sound.out${i}" >/dev/null; then
		echo "test file #${i}: pass"
	else
		echo "test file #${i}: fail"
	fi
done