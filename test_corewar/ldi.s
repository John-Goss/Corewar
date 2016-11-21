.name "ldi"
.comment "ldi"
#ldi %2, %1, r1
#prend les 2 premiers index, les aditionne et traite ca comme une taille de registre qui est mis dans le registre.

sti r2, r1, %0
#verifie que le ldi as bien fonctionne.
