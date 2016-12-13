Make -C ../../assembleur/
mv ../asm .
echo "\n\n\n"
echo "\033[33;41m Compilation de l'assembleur\033[0m"
echo "\n\n"
echo "\033[35m"
./asm -n Our_Corewar/ Our_Corewar/champions/Kappa.s
./asm -n Our_Corewar/ Our_Corewar/champions/Asombra.s
./asm -n Our_Corewar/ Our_Corewar/champions/Machine-gun.s
./asm -n Our_Corewar/ Our_Corewar/champions/MarineKing.s
./asm -n Our_Corewar/ Our_Corewar/champions/Rainbow_dash.s
./asm -n Our_Corewar/ Our_Corewar/champions/THUNDER.s
./asm -n Our_Corewar/ Our_Corewar/champions/Varimathras.s
./asm -n Our_Corewar/ Our_Corewar/champions/_honeybadger.s
./asm -n Our_Corewar/ Our_Corewar/champions/big_feet.s
./asm -n Our_Corewar/ Our_Corewar/champions/casimir.s
./asm -n Our_Corewar/ Our_Corewar/champions/corelol.s
./asm -n Our_Corewar/ Our_Corewar/champions/champ.s
./asm -n Our_Corewar/ Our_Corewar/champions/darksasuke.s
./asm -n Our_Corewar/ Our_Corewar/champions/dubo.s
./asm -n Our_Corewar/ Our_Corewar/champions/gedeon.s
./asm -n Our_Corewar/ Our_Corewar/champions/jinx.s
./asm -n Our_Corewar/ Our_Corewar/champions/justin_bee.s
./asm -n Our_Corewar/ Our_Corewar/champions/littlepuppy.s
./asm -n Our_Corewar/ Our_Corewar/champions/live.s
./asm -n Our_Corewar/ Our_Corewar/champions/loose.s
./asm -n Our_Corewar/ Our_Corewar/champions/mandragore.s
./asm -n Our_Corewar/ Our_Corewar/champions/meowluigi.s
./asm -n Our_Corewar/ Our_Corewar/champions/skynet.s
./asm -n Our_Corewar/ Our_Corewar/champions/terminator.s
./asm -n Our_Corewar/ Our_Corewar/champions/youforkmytralala.s
./asm -n Our_Corewar/ Our_Corewar/champions/bee_gees.s
./asm -n Our_Corewar/ Our_Corewar/champions/bigzork.s
./asm -n Our_Corewar/ Our_Corewar/champions/fluttershy.s
./asm -n Our_Corewar/ Our_Corewar/champions/helltrain.s
./asm -n Our_Corewar/ Our_Corewar/champions/turtle.s
./asm -n Our_Corewar/ Our_Corewar/champions/zork.s
./asm -n Our_Corewar/ Our_Corewar/champions/the_professor.s
echo "\033[0m\n\n"
echo "\033[34m"
./Corewar_Zaz/asm Corewar_Zaz/champions/Asombra.s
./Corewar_Zaz/asm Corewar_Zaz/champions/Kappa.s
./Corewar_Zaz/asm Corewar_Zaz/champions/Machine-gun.s
./Corewar_Zaz/asm Corewar_Zaz/champions/MarineKing.s
./Corewar_Zaz/asm Corewar_Zaz/champions/Rainbow_dash.s
./Corewar_Zaz/asm Corewar_Zaz/champions/THUNDER.s
./Corewar_Zaz/asm Corewar_Zaz/champions/Varimathras.s
./Corewar_Zaz/asm Corewar_Zaz/champions/_honeybadger.s
./Corewar_Zaz/asm Corewar_Zaz/champions/big_feet.s
./Corewar_Zaz/asm Corewar_Zaz/champions/casimir.s
./Corewar_Zaz/asm Corewar_Zaz/champions/corelol.s
./Corewar_Zaz/asm Corewar_Zaz/champions/champ.s
./Corewar_Zaz/asm Corewar_Zaz/champions/darksasuke.s
./Corewar_Zaz/asm Corewar_Zaz/champions/dubo.s
./Corewar_Zaz/asm Corewar_Zaz/champions/gedeon.s
./Corewar_Zaz/asm Corewar_Zaz/champions/jinx.s
./Corewar_Zaz/asm Corewar_Zaz/champions/justin_bee.s
./Corewar_Zaz/asm Corewar_Zaz/champions/littlepuppy.s
./Corewar_Zaz/asm Corewar_Zaz/champions/live.s
./Corewar_Zaz/asm Corewar_Zaz/champions/loose.s
./Corewar_Zaz/asm Corewar_Zaz/champions/mandragore.s
./Corewar_Zaz/asm Corewar_Zaz/champions/meowluigi.s
./Corewar_Zaz/asm Corewar_Zaz/champions/skynet.s
./Corewar_Zaz/asm Corewar_Zaz/champions/terminator.s
./Corewar_Zaz/asm Corewar_Zaz/champions/youforkmytralala.s
./Corewar_Zaz/asm Corewar_Zaz/champions/bee_gees.s
./Corewar_Zaz/asm Corewar_Zaz/champions/bigzork.s
./Corewar_Zaz/asm Corewar_Zaz/champions/fluttershy.s
./Corewar_Zaz/asm Corewar_Zaz/champions/helltrain.s
./Corewar_Zaz/asm Corewar_Zaz/champions/turtle.s
./Corewar_Zaz/asm Corewar_Zaz/champions/zork.s
./Corewar_Zaz/asm Corewar_Zaz/champions/the_professor.s

mkdir Corewar_Zaz/hexdump
mkdir Corewar_Zaz/result
mkdir Our_Corewar/result
mkdir Our_Corewar/hexdump
mv Corewar_Zaz/champions/*.cor Corewar_Zaz/result/
mv Our_Corewar/*.cor Our_Corewar/result/
echo "\033[0m\n\n\n"

echo "\033[38;42m//                fait des hexdumps               \\\\\\\\\\033[0m"

hexdump -vC Our_Corewar/result/Asombra.cor > Our_Corewar/hexdump/Asombra
hexdump -vC Our_Corewar/result/Kappa.cor > Our_Corewar/hexdump/Kappa
hexdump -vC Our_Corewar/result/Machine-gun.cor > Our_Corewar/hexdump/Machine-gun
hexdump -vC Our_Corewar/result/MarineKing.cor > Our_Corewar/hexdump/MarineKing
hexdump -vC Our_Corewar/result/Rainbow_dash.cor > Our_Corewar/hexdump/Rainbow_dash
hexdump -vC Our_Corewar/result/THUNDER.cor > Our_Corewar/hexdump/THUNDER
hexdump -vC Our_Corewar/result/Varimathras.cor > Our_Corewar/hexdump/Varimathras
hexdump -vC Our_Corewar/result/_honeybadger.cor > Our_Corewar/hexdump/_honeybadger
hexdump -vC Our_Corewar/result/big_feet.cor > Our_Corewar/hexdump/big_feet
hexdump -vC Our_Corewar/result/casimir.cor > Our_Corewar/hexdump/casimir
hexdump -vC Our_Corewar/result/corelol.cor > Our_Corewar/hexdump/corelol
hexdump -vC Our_Corewar/result/champ.cor > Our_Corewar/hexdump/champ 
hexdump -vC Our_Corewar/result/darksasuke.cor > Our_Corewar/hexdump/darksasuke
hexdump -vC Our_Corewar/result/dubo.cor > Our_Corewar/hexdump/dubo
hexdump -vC Our_Corewar/result/gedeon.cor > Our_Corewar/hexdump/gedeon
hexdump -vC Our_Corewar/result/jinx.cor > Our_Corewar/hexdump/jinx
hexdump -vC Our_Corewar/result/justin_bee.cor > Our_Corewar/hexdump/justin_bee
hexdump -vC Our_Corewar/result/littlepuppy.cor > Our_Corewar/hexdump/littlepuppy
hexdump -vC Our_Corewar/result/live.cor > Our_Corewar/hexdump/live
hexdump -vC Our_Corewar/result/loose.cor > Our_Corewar/hexdump/loose
hexdump -vC Our_Corewar/result/mandragore.cor > Our_Corewar/hexdump/mandragore
hexdump -vC Our_Corewar/result/meowluigi.cor > Our_Corewar/hexdump/meowluigi
hexdump -vC Our_Corewar/result/skynet.cor > Our_Corewar/hexdump/skynet
hexdump -vC Our_Corewar/result/terminator.cor > Our_Corewar/hexdump/terminator
hexdump -vC Our_Corewar/result/youforkmytralala.cor > Our_Corewar/hexdump/youforkmytralala
hexdump -vC Our_Corewar/result/bee_gees.cor > Our_Corewar/hexdump/bee_gees
hexdump -vC Our_Corewar/result/bigzork.cor > Our_Corewar/hexdump/bigzork
hexdump -vC Our_Corewar/result/fluttershy.cor > Our_Corewar/hexdump/fluttershy
hexdump -vC Our_Corewar/result/helltrain.cor > Our_Corewar/hexdump/helltrain
hexdump -vC Our_Corewar/result/turtle.cor > Our_Corewar/hexdump/turtle
hexdump -vC Our_Corewar/result/zork.cor > Our_Corewar/hexdump/zork
hexdump -vC Our_Corewar/result/the_professor.cor > Our_Corewar/hexdump/the_professor

hexdump -vC Corewar_zaz/result/Asombra.cor > Corewar_Zaz/hexdump/Asombra
hexdump -vC Corewar_zaz/result/Kappa.cor > Corewar_Zaz/hexdump/Kappa
hexdump -vC Corewar_zaz/result/Machine-gun.cor > Corewar_Zaz/hexdump/Machine-gun
hexdump -vC Corewar_zaz/result/MarineKing.cor > Corewar_Zaz/hexdump/MarineKing
hexdump -vC Corewar_zaz/result/Rainbow_dash.cor > Corewar_Zaz/hexdump/Rainbow_dash
hexdump -vC Corewar_zaz/result/THUNDER.cor > Corewar_Zaz/hexdump/THUNDER
hexdump -vC Corewar_zaz/result/Varimathras.cor > Corewar_Zaz/hexdump/Varimathras
hexdump -vC Corewar_zaz/result/_honeybadger.cor > Corewar_Zaz/hexdump/_honeybadger
hexdump -vC Corewar_zaz/result/big_feet.cor > Corewar_Zaz/hexdump/big_feet
hexdump -vC Corewar_zaz/result/casimir.cor > Corewar_Zaz/hexdump/casimir
hexdump -vC Corewar_zaz/result/corelol.cor > Corewar_Zaz/hexdump/corelol
hexdump -vC Corewar_zaz/result/champ.cor > Corewar_Zaz/hexdump/champ
hexdump -vC Corewar_zaz/result/darksasuke.cor > Corewar_Zaz/hexdump/darksasuke
hexdump -vC Corewar_zaz/result/dubo.cor > Corewar_Zaz/hexdump/dubo
hexdump -vC Corewar_zaz/result/gedeon.cor > Corewar_Zaz/hexdump/gedeon
hexdump -vC Corewar_zaz/result/jinx.cor > Corewar_Zaz/hexdump/jinx
hexdump -vC Corewar_zaz/result/justin_bee.cor > Corewar_Zaz/hexdump/justin_bee
hexdump -vC Corewar_zaz/result/littlepuppy.cor > Corewar_Zaz/hexdump/littlepuppy
hexdump -vC Corewar_zaz/result/live.cor > Corewar_Zaz/hexdump/live
hexdump -vC Corewar_zaz/result/loose.cor > Corewar_Zaz/hexdump/loose
hexdump -vC Corewar_zaz/result/mandragore.cor > Corewar_Zaz/hexdump/mandragore
hexdump -vC Corewar_zaz/result/meowluigi.cor > Corewar_Zaz/hexdump/meowluigi
hexdump -vC Corewar_zaz/result/skynet.cor > Corewar_Zaz/hexdump/skynet
hexdump -vC Corewar_zaz/result/terminator.cor > Corewar_Zaz/hexdump/terminator
hexdump -vC Corewar_zaz/result/youforkmytralala.cor > Corewar_Zaz/hexdump/youforkmytralala
hexdump -vC Corewar_zaz/result/bee_gees.cor > Corewar_Zaz/hexdump/bee_gees
hexdump -vC Corewar_zaz/result/bigzork.cor > Corewar_Zaz/hexdump/bigzork
hexdump -vC Corewar_zaz/result/fluttershy.cor > Corewar_Zaz/hexdump/fluttershy
hexdump -vC Corewar_zaz/result/helltrain.cor > Corewar_Zaz/hexdump/helltrain
hexdump -vC Corewar_zaz/result/turtle.cor > Corewar_Zaz/hexdump/turtle
hexdump -vC Corewar_zaz/result/zork.cor > Corewar_Zaz/hexdump/zork
hexdump -vC Corewar_zaz/result/the_professor.cor > Corewar_Zaz/hexdump/the_professor

echo "\033[31;46m                  ON FAIT DES DIFFS                 "

diff Our_Corewar/hexdump/Asombra Corewar_Zaz/hexdump/Asombra
diff Our_Corewar/hexdump/Kappa Corewar_Zaz/hexdump/Kappa
diff Our_Corewar/hexdump/Machine-gun Corewar_Zaz/hexdump/Machine-gun
diff Our_Corewar/hexdump/MarineKing Corewar_Zaz/hexdump/MarineKing
diff Our_Corewar/hexdump/Rainbow_dash Corewar_Zaz/hexdump/Rainbow_dash
diff Our_Corewar/hexdump/THUNDER Corewar_Zaz/hexdump/THUNDER
diff Our_Corewar/hexdump/Varimathras Corewar_Zaz/hexdump/Varimathras
diff Our_Corewar/hexdump/_honeybadger Corewar_Zaz/hexdump/_honeybadger
diff Our_Corewar/hexdump/big_feet Corewar_Zaz/hexdump/big_feet
diff Our_Corewar/hexdump/casimir Corewar_Zaz/hexdump/casimir
diff Our_Corewar/hexdump/champ Corewar_Zaz/hexdump/champ
diff Our_Corewar/hexdump/corelol Corewar_Zaz/hexdump/corelol
diff Our_Corewar/hexdump/darksasuke Corewar_Zaz/hexdump/darksasuke
diff Our_Corewar/hexdump/dubo Corewar_Zaz/hexdump/dubo
diff Our_Corewar/hexdump/gedeon Corewar_Zaz/hexdump/gedeon
diff Our_Corewar/hexdump/jinx Corewar_Zaz/hexdump/jinx
diff Our_Corewar/hexdump/justin_bee Corewar_Zaz/hexdump/justin_bee
diff Our_Corewar/hexdump/littlepuppy Corewar_Zaz/hexdump/littlepuppy
diff Our_Corewar/hexdump/live Corewar_Zaz/hexdump/live
diff Our_Corewar/hexdump/loose Corewar_Zaz/hexdump/loose
diff Our_Corewar/hexdump/mandragore Corewar_Zaz/hexdump/mandragore
diff Our_Corewar/hexdump/meowluigi Corewar_Zaz/hexdump/meowluigi
diff Our_Corewar/hexdump/skynet Corewar_Zaz/hexdump/skynet
diff Our_Corewar/hexdump/terminator Corewar_Zaz/hexdump/terminator
diff Our_Corewar/hexdump/youforkmytralala Corewar_Zaz/hexdump/youforkmytralala
diff Our_Corewar/hexdump/bee_gees Corewar_Zaz/hexdump/bee_gees
diff Our_Corewar/hexdump/bigzork Corewar_Zaz/hexdump/bigzork
diff Our_Corewar/hexdump/fluttershy Corewar_Zaz/hexdump/fluttershy
diff Our_Corewar/hexdump/helltrain Corewar_Zaz/hexdump/helltrain
diff Our_Corewar/hexdump/turtle Corewar_Zaz/hexdump/turtle
diff Our_Corewar/hexdump/zork Corewar_Zaz/hexdump/zork
diff Our_Corewar/hexdump/the_professor Corewar_Zaz/hexdump/the_professor
