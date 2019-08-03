.name "zjmp"

.comment "JUMP ! JUMP ! JUMP !"

live:	live %1
	zjmp %:live
	ld %0, r2
	zjmp %:live
