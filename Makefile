all: generateur #oldgen

generateur: generateur.o flocchini/algo.o
	gcc generateur.o flocchini/algo.o -o generateur

#oldgen: oldgen.o strategy.o flocchini/algo.o
#	gcc oldgen.o strategy.o flocchini/algo.o -o oldgen

#oldgen.o: generateur.old.c strategy.h flocchini/algo.h
#	gcc -ggdb3 -O0 -Wall -c generateur.old.c -o oldgen.o
	
generateur.o: generateurRecup.c flocchini/algo.h
	gcc -ggdb3 -O0 -Wall -c generateurRecup.c -o generateur.o
	
#strategy.o: strategy.c
#	gcc -ggdb3 -O0 -Wall -c strategy.c -o strategy.o
	
flocchini/algo.o: flocchini/algo.c
	gcc -ggdb3 -O0 -Wall -c flocchini/algo.c -o flocchini/algo.o
	
clean:
	rm *.o generateur a.out #oldgen 
	
super-clean:
	rm *.dve *.ord *.ltl *.o generateur a.out #oldgen
