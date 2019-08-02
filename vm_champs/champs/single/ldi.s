.name "load index"

.comment "add r1 et r2 then load into it"

	ldi r1, r2, r2
	ldi %0, r2, r3
	ldi 0, r2, r4
	ldi r1, %64, r5
	ldi %0, %64, r6
	ldi 0, %64, r7
	st r1, 64
	st r2, 64
	st r3, 64
	st r4, 64
	st r5, 64
	st r6, 64
	st r7, 64
