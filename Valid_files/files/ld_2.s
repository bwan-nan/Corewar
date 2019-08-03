.name "load bis"
.comment "Loading. Please wait..."

	ld %1000, r2
	ld %2000, r3
	ld %-2000, r4
	ld %0, r5
	ld 0, r6
	ld 2000, r7
	ld -100, r8
	ld -2000, r9
	st r2, 64
	st r3, 64
	st r4, 64
	st r5, 64
	st r6, 64
	st r7, 64
	st r8, 64
	st r9, 64
