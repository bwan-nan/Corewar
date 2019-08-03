.name "Zkiller"
.comment "Nope, you're dead man... R.I.P"

and r1, %0, r2

loop:
		st r1, 6
		live %42
		fork %511
		zjmp %:loop
