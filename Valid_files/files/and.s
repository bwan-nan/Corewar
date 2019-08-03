.name "and"

.comment "r3 = r1 & r2"

	and r1, r1, r2
	and %1020, r1, r3
	and 1020, r1, r4
	and 0, r1, r8
	and r1, %64, r5
	and %2040, %64, r6
	and 2040, %64, r7
	and 0, %0, r8
	and r1, 64, r5
	and %2040, 64, r9
	and 2040, 64, r10
	and 64, 0, r11
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
