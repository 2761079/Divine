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
lmillet=$(pwd) #correpond au dosssier divine

for ((K=$param1; K<=$param2; K = (($K+2))));do
	for((N=(($K+1)) ; $N <$param3;  N++)); do
	#on fait nos fichiers LTL et on fait les metrics dans la foulée
		$lmillet/LTL/ltl_div $N $K $lmillet/TEST/test$N$K/ltl$N$K
		cd $lmillet/TEST/test$N$K
		for i in conf*test$N$K.dve; do
			echo $i
			$DIVINE combine $i -f ltl$N$K.c	
			rm $i
		done;
		for i in conf*prop1.dve; do
			$DIVINE -r metrics $i > $i.metrics
		done;
	done; 
done;

#for $i in test*; do
#	cd $i;
#	echo "$j" > states.txt
#	echo "$j" > transitions.txt
#	echo "$j" > memory.txt
#	for $j in conf*;do
#		divine -r metrics $j > sol$j
#		grep metrics sol $j >>
#			
#	done; 	
#done;
