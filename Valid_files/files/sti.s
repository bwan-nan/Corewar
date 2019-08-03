.name "store index"

.comment "add r1 and r2 then use it as address to store r3"

	sti r1, r2, r3
	sti r1, %64, r3
	sti r1, 64, r3
	sti r1, r2, %64
	sti r1, %64, %64
	sti r1, 64, %64
