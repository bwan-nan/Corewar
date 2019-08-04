.name "carry"

.comment "take care !"

	#no carry
	live %-1
	live %0
	#carry
	ld %64, r3
	#ld %0, r2
	#no carry
	st r3, 64
	st r2, 64
	#carry
	and r1, r3, r5
	#and r1, r2, r4
	#carry
	or r1, r3, r7
	#or r2, r2, r6
	#carry
	xor r1, r3, r9
	#xor r2, r2, r8
	#no carry
	ldi r2, %64,  r11
	ldi r2, %0, r10
	sti r2, 64, %64
	sti r2, 0, %64
	#carry
	lld 0, r12
	#lld 1020, r13
	lldi 0, %64,  r14
	#lldi 1020, %0, r15
	#no carry
	ld %90, r16
	aff r16
	#fork %50
	fork %0
	lfork %5050
	lfork %0
	zjmp %1024
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
	st r12, 64
	st r13, 64
	st r14, 64
	st r15, 64
	st r16, 64
