#!/bin/sh

if [[ $# == 3 ]]
then echo "nb param ok"
else echo "pb nd param"
	exit 12;
fi
#param1 est la valeur de K de départ
if [[ $1 == "" ]]
	then echo "manque K min"
	exit 1;
fi
param1=$1

#param2 est le Kmax
if [[ $2 == "" ]]
	then echo "pb K max"
	exit 2;
fi
param2=$2

#param3 est la taille de l'anneau max
if [[ $3 == "" ]]
	then echo "pb N max"
	exit 3;
fi
param3=$3

cd ..
divine=$(pwd)
cd TEST

cd $divine/LTL
gcc gen_ltl.c -o gen_ltl
cd $divine
make

for ((K=$param1; k<=$param2; k = (($K+2))));do
    #on obtient la formule LTLé
    cd $divine/LTL
    ./gen_ltl 1 $K flo$K
    gcc -E flo$K.c > flo$K.txt
    grep -v '^#' flo$K.txt > flo$K.ltl

    cd $divine
    for((N=(($K+1)) ; $N <$param3;  N++)); do
    #for((N=28; $N < 29 ; N++));do
        echo "$K robots dans un anneau de $N\n"
        mkdir test$N$K
        ./generateur $N $K test$N$K
        cd test$N$K
        for i in conf*; do
            for((j=1 ; $j <= $K ; j = (($j+1)) )); do
                cat /tmp/StartProc$j$i >> $i
		rm /tmp/StartProc$j$i
                cat /tmp/test$N$K.dve >> $i
            done;
            echo "system async;" >> $i
	    #echo "$i" > $divine/soluce$i.txt
	    #~/ITS/its-reach -i $i  -t DVE 2>&1 >> $divine/soluce$i.txt 
	    #~/ITS/its-ltl -i $i -t DVE -ltl "(cat $divine/LTL/flo$k.ltl)" -c 2>&1 >> $divine.soluce$i.txt
      	 done;
        rm /tmp/test$N$K*
	cd $divine
	mv  test$N$K TEST/

    done;
done;
