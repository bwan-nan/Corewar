.name "long load"
.comment "Loading. Please wait..."

	lld %1000, r2
	lld %2000, r3
	lld %-2000, r4
	lld %0, r5
	lld 0, r6
	lld 2000, r7
	lld -100, r8
	lld -2000, r9
	st r2, 64
	st r3, 64
	st r4, 64
	st r5, 64
	st r6, 64
	st r7, 64
	st r8, 64
	st r9, 64
