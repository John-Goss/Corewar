.name "sub"
.comment "sub"

ldi %20, %20, r1
ldi %20, %20, r2
sub r1, r2, r3 
#av[3] = av[1] - av[2]
sti r4, r3, r5
#test, pas le choix pour les ldi c'est pour donner une valeur aux registres
