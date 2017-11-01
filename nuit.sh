#!/bin/sh

lmillet=$(pwd)

#cd ..
mkdir testBMPT
./generateur -s FULL 10 3 test 0 1 2 
mv *.dve test103
sh script_metrics.sh 10 3
#cd testBMPT
#mv *.dve test103
#/$lmillet/LTL/ltl_div 10 3 /$lmillet/test103/ltl103
cd test103
#$DIVINE combine conf_test.dve -f ltl103.c ok pour flo
$DIVINE combine conf_test.dve -f /$lmillet/LTL/all10.ltl
$DIVINE -r metrics conf_test.prop1.dve > metrics.txt
#~/ITS/its-reach -i conf_test.prop1.dve -t DVE 2>&1 >> soluce.txt

#cd ..
#./generateur -s SEMI 10 3 test 0 1 2 
#sh script_metrics.sh 10 3
#cd testBMPT
#mv *.dve test103
#~/ITS/its-reach -i conf_test.dve -t DVE 2>&1 >> soluce.txt

#cd ..
#./generateur 10 3 test 0 1 2 
#sh script_metrics.sh 10 3
#cd testBMPT
#mv *.dve test103
#~/ITS/its-reach -i conf_test.dve -t DVE 2>&1 >> soluce.txt
