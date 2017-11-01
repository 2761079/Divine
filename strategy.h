#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//ce fichier va nous permettre de défnir plusieurs stratégies pour des robots circulant sur un anneaux

//permet d'écrire dans le fichier fic les mouvements des robots pour que ceux-ci utilise l'algoritme avec 3 robots dans "Exclusive perpetual Ring Exploration without chirality"
void strategy_10_3(FILE *out);
void strategy_11_3(FILE *out);
void strategy_13_3(FILE *out);
void strategy_14_3(FILE *out);

void strategy_12_5(FILE *out);

void robots3(int r1, int r2, int anneau_size, FILE *out);
