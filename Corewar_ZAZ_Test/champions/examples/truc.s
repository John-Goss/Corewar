.name "truc"
.comment "truc"

biglabel: 
	live %42
	ldi %20, %30, r1
	sti r2, r1, r3
	ld %2, r1
	add r1, r2, r3
	sub r1, r2, r3
	st r1, 6
	xor r1, r2, r4
	aff r1
	ld %4, r2
	lldi %299, %1, r3
	and r1, r2, r3

smalllabel:
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;
	live %11;

zjmp %:biglabel
fork %:biglabel
lfork %:smalllabel
