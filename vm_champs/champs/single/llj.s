.name "live load jump"

.comment "LLJ"

live:	live %1
	ld %0, r2
	zjmp %:live
