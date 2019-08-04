.name "xor"

.comment "r3 = r1 ^ r2"

	xor r1, r1, r2
	xor %1020, r1, r3
	xor 1020, r1, r4
	xor 0, r1, r8
	xor r1, %64, r5
	xor %2040, %64, r6
	xor 2040, %64, r7
	xor 0, %0, r8
	xor r1, 64, r5
	xor %2040, 64, r9
	xor 2040, 64, r10
	xor 64, 0, r11
	st r1, 64
	st r2, 64
	st r3, 64
	st r4, 64
	st r5, 64
	st r6, 64
	st r7, 64
	st r8, 64
	st r9, 64
	st r10, 64
	st r11, 64
