#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct s_Block Block;
struct s_Block{
    char LeadingRi; 
    int taille;
    int border_max;
    int border_min;
    Block *next;
   
};

typedef struct s_List_Block List;
struct s_List_Block{
    Block *b; // head
    Block *current; //tail
    int nb_block;
    int max_size;
    int min_size;
};

typedef struct s_List_Ri List_Ri;
struct s_List_Ri{
		int robot;
		char direction;
		List_Ri * current;
		List_Ri * next;
};

typedef struct s_Leader Leader;
struct s_Leader{
		int value; // valeur de la plus grande vue
		int R1;
		char R1_pos; //'+' si c'est le max de son bloc ...
		int R2;
		char R2_pos;
};

int pgcd (int a, int b);

char *hachage_binaire (unsigned long long n, int length, char *retour);

void robot (int confi, int length, FILE * out, char direction);

void idle (int confi, int length, FILE * out);

int factorielle( int n);

long NB_conf(int robots, int taille);

int Dist (int a, int b, int taille);

int valueB(int length, int confi, int indice, char direction);

//génère toutes les configs sans leur symétriques...
int config(int *chiffres, int robots, int taille, int length);

void flocchini(int robots, int taille, FILE * out);

void algomin(int robots, int taille, FILE *out, int new);
