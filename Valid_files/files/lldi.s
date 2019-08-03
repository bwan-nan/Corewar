.name "long load index"

.comment "add r1 & r2 then load into it"

	lldi r1, r2, r2
	lldi %1024, r2, r3
	lldi 1024, r2, r4
	lldi r1, %64, r5
	lldi %2048, %64, r6
	lldi 2048, %64, r7
	lldi 0, %0, r8
	st r1, 64
	st r2, 64
	st r3, 64
	st r4, 64
	st r5, 64
	st r6, 64
	st r7, 64
	st r8, 64
