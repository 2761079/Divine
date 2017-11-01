 #!/bin/sh


 #param1 = $1 = N
 if [[ $1 == "" ]]
	 then echo "manque N"
	 exit 1;
fi
 N=$1


 #param2 = $2 = K

 K=$2

 cd test$N$K

cat conf.dve >> conf_test.dve

 for((j=1 ; $j <= $K; j = (($j+1)) ));do
	# echo "/tmp/StartProc${j}conf0_test.dve"
	echo $(pwd)
	 cat StartProc${j}.dve >> conf_test.dve
	# rm StartProc${j}.dve 
	 cat test.dve >> conf_test.dve
done;

rm test.dve
echo "system async;" >>conf_test.dve

echo $(pwd)
../LTL/ltl_div $N $K ltl


cd -
