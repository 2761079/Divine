//contient flo et algo min
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

//attention taille et robots coprime

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

int pgcd (int a, int b){
	int r;
 
  while (b != 0)
    {
      r = a%b;
      a = b;
      b = r;
    }
 
  return a;
}

char *hachage_binaire (unsigned long long n, int length, char *retour){
  int i;
  int tmp;
  //printf ("n = %lu == ",n);
  for (i = length - 1; i>=0 ; i--)
    {
      tmp = ((n >> i) & 1);
      retour[i] = tmp + '0';
      //printf ("%c %d",retour[i], retour[i]);
    }
  //printf ("\n\n\n");
  return retour;
}

void robot (int confi, int length, FILE * out, char direction){
	int i,j;
	char tab[length -1];
	hachage_binaire(confi, length -1, tab);
	if (direction=='+'){
		fprintf (out, "observe -> plus {guard Ask==0 && player==id ");
	}else{
		fprintf (out, "observe -> moins {guard Ask==0 && player==id ");
	}
	for (i=0; i <= length -1; i++){
		j = i+1;
		if(tab[i]=='1'){
			fprintf(out,"&& nb[(index+%d)%% %d]==1 ",j,length);
	   }
	}
	fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=0;},\n");
  fprintf (out, "//INV\n");
  if (direction=='+'){
		fprintf (out, "observe -> moins {guard Ask==0 && player==id ");
	}else{
		fprintf (out, "observe -> plus {guard Ask==0 && player==id");
	}
  for (i=0; i <= length -1; i++){
		j = i+1;
		if(tab[i]=='1'){
			fprintf(out,"&& nb[(index+%d)%% %d]==1 ",length-j, length);
	   }
	}   
	fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=0;},\n");
  
  fprintf (out, "observe -> observe {guard Ask==1 && player==id ");
  for (i=0; i <= length -1; i++){
	j = i+1;
	if(tab[i]=='1'){
		fprintf(out,"&& nb[(index+%d)%% %d]==1 ",j,length);
	}
  }
  fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=1, hasMover=1;},\n");
  
  fprintf (out, "observe -> observe {guard Ask==1 && player==id ");
  for (i=0; i <= length -1; i++){
	j = i+1;
	if(tab[i]=='1'){
		fprintf(out,"&& nb[(index+%d)%% %d]==1 ",length-j, length);
	}
  }
  fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=1, hasMover=1;},\n");
	
	return;
}

void idle (int confi, int length, FILE * out){
	int i,j;
	char tab[length -1];
	hachage_binaire(confi, length -1, tab);
	fprintf(out, "//tab = ");
	for (i=0; i< length -1; i++){
		fprintf(out, "%c",tab[i]);
	}
	fprintf(out, "\n");
	fprintf (out, "observe -> stop {guard Ask==0 && player==id ");
	for (i=0; i <= length -1; i++){
		j = i+1;
		if(tab[i]=='1'){
			fprintf(out,"&& nb[(index+%d)%% %d]==1 ",j,length);
	   }
	}
	fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=0;},\n");
  
  fprintf (out, "//INV\n");
 	fprintf (out, "observe -> stop {guard Ask==0 && player==id ");
  for (i=0; i <= length -1; i++){
		j = i+1;
		if(tab[i]=='1'){
			fprintf(out,"&& nb[(index+%d)%% %d]==1 ",length-j, length);
	   }
	}   
	fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=0;},\n");
  
  fprintf (out, "observe -> observe {guard Ask==1 && player==id ");
  for (i=0; i <= length -1; i++){
	j = i+1;
	if(tab[i]=='1'){
		fprintf(out,"&& nb[(index+%d)%% %d]==1 ",j,length);
	}
  }
  fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=0;},\n");
  
  fprintf (out, "observe -> observe {guard Ask==1 && player==id ");
  for (i=0; i <= length -1; i++){
	j = i+1;
	if(tab[i]=='1'){
		fprintf(out,"&& nb[(index+%d)%% %d]==1 ",length-j, length);
	}
  }
  fprintf (out, ";");
  fprintf (out, "\neffect player=0, WouldMove=0;},\n");
	
	return;
}

void idle2 (int confi, int length, FILE * out){
	int i,j;
	char tab[length -1];
	hachage_binaire(confi, length -1, tab);
	fprintf(out, "//tab = ");
	for (i=0; i< length -1; i++){
		fprintf(out, "%c",tab[i]);
	}
	fprintf(out, "\n");
	fprintf (out, "observe -> stop {guard Ask==0 && player==id ");
	for (i=0; i <= length -1; i++){
		j = i+1;
		if(tab[i]=='1'){
			fprintf(out,"&& nb[(index+%d)%% %d]==1 ",j,length);
        }
	}
	fprintf (out, ";");
    fprintf (out, "\neffect player=0, floTypeD=1;},\n");
    
    fprintf (out, "//INV\n");
 	fprintf (out, "observe -> stop {guard Ask==0 && player==id ");
    for (i=0; i <= length -1; i++){
		j = i+1;
		if(tab[i]=='1'){
			fprintf(out,"&& nb[(index+%d)%% %d]==1 ",length-j, length);
        }
	}
	fprintf (out, ";");
    fprintf (out, "\neffect player=0, floTypeD=1;},\n");
    
    fprintf (out, "observe -> observe {guard Ask==1 && player==id ");
    for (i=0; i <= length -1; i++){
        j = i+1;
        if(tab[i]=='1'){
            fprintf(out,"&& nb[(index+%d)%% %d]==1 ",j,length);
        }
    }
    fprintf (out, ";");
    fprintf (out, "\neffect player=0, WouldMove=0, floTypeD=1;},\n");
    
    fprintf (out, "observe -> observe {guard Ask==1 && player==id ");
    for (i=0; i <= length -1; i++){
        j = i+1;
        if(tab[i]=='1'){
            fprintf(out,"&& nb[(index+%d)%% %d]==1 ",length-j, length);
        }
    }
    fprintf (out, ";");
    fprintf (out, "\neffect player=0, WouldMove=0, floTypeD=1;},\n");
	
	return;
}


int factorielle( int n){
	int i;
	int fact= 1;
	for(i= 1; i <= n; i++)
		fact = fact * i ;
	return fact;
}

long NB_conf(int robots, int taille){
	//long configs1 = ( factorielle(taille-1) / ( factorielle(robots -1)* factorielle(taille - robots) ));
	// trop grand comme nombres !!! 
	
	int min, max;
	if(taille - robots > robots-1){
		max = taille - robots;
		min = robots - 1;
	}else{
		max = robots - 1;
		min = taille - robots;
	}
	long up = 1;
	int i;
	for (i = max + 1; i <=taille-1; i++){
		up = up *i;
	}
	long configs = up;
	for (i = 1; i <= min; i++){
		configs = configs / i;
	}

	
	//long retour;
	//printf("il y a %ld configs \n",configs);
	if ( (configs % 2) == 0){
		//retour = (configs >> 1) + 2;
		//printf("il y a %ld non symétriques", retour );
		return ((configs >> 1) + taille )*2;
	}
	//retour = (configs + 1) >> 1 ;
	//printf("il y a %ld non symétriques",  retour + 2);
	return (((configs + 1) >> 1) +taille )*2;
}

// a et b dans l'ordre des aiguilles d'une montre
int Dist (int a, int b, int taille){
	int retour;
	if (a > b){
		retour = a-b;
		if(b == -1)
            retour = taille -(a+1);
	}else{ 
		retour = b-a;
		if(a == -1)
            retour = b+1;
	}
	return retour;
}

int valueB(int length, int confi, int indice, char direction){
	int i;
	int tmp=0;
	int jm = length;
	int jp = length;
	char tab[length -1];
	hachage_binaire(confi, length -1, tab);
if(indice != -1){
	if(direction == '-'){
		for (i = indice; i<length; i++){
		//printf("bli");
			if (tab[i] == '1')
				tmp += (1 << jm);
				//printf ("\t !%d,%d \t",tmp,jm);
			jm--;
		}
	}else{
		for (i = indice; i>=0; i--){
			if (tab[i] == '1')
				tmp += (1 << jp);
			//printf ("\t !%d,%d \t",tmp,jp);
			jp--;
		}
	}
	//printf("\t mid %d \t",tmp);
	// on ajoute -1
	if(direction =='-'){
		tmp +=(1 << jm);
	}else{
		tmp +=(1 << jp);
	}
	jp--;
	jm--;
	// on rajoute le reste du tableau
	if(direction == '-'){
		for (i = 0; i<indice; i++){
			if (tab[i] == '1')
				tmp += (1 << jm);
			//printf ("\t %d,%d \t",tmp,jm);
			jm--;
		}
	}else{
		for (i = length -1; i>indice; i--){
			if (tab[i] == '1')
				tmp += (1 << jp);
			//printf ("\t %d,%d \t",tmp,jp);
			jp--;
		}
	}
}else{ // pour -1
	if(direction == '-'){
	  tmp += (1 << jm);
		jm --;
		for (i = 0; i<length; i++){
		//printf("bli");
			if (tab[i] == '1')
				tmp += (1 << jm);
				//printf ("\t !%d,%d \t",tmp,jm);
			jm--;
		}
	}else{
		tmp += (1 << jm);
		jp --;
		for (i = length -1; i>=0; i--){
			if (tab[i] == '1')
				tmp += (1 << jp);
			//printf ("\t !%d,%d \t",tmp,jp);
			jp--;
		}
	}
}
	//printf ("\t !!!!!!%d \t",tmp);
	return tmp;
}

int config(int *chiffres, int robots, int taille, int length){
	//printf("Départ \n");
	int i, j, k, r, nb, conf;
  nb = 0;
  conf = 0;
  int same;
  int taillem= taille -1;
  //char chiffres[pow (2, taillem)][taille];
  //printf ("%d < %d \n",robots,(1<< taillem));
  for (i = robots; (i < (1 << taillem)) ;i++)// && (i <= length) ); i++)
    {
      char tab[taillem];
      hachage_binaire (i, taillem, tab);
      r = 0;
      //printf("i = ");
      for (j = 0; j < taille - 1; j++)
			{
			//printf("%c",tab[j]);	
	  		if (tab[j] == '1')
	    		r++;
			}
	  //printf("\n");
      if (r == robots - 1)
      //on récupère tous les chiffres en binaire formés de deux '1' représentant les robots dans l'anneau ...
		{
	  		nb++;
	  		same = 0;
	  		char tab2[taillem];
	  		for (k = 0; k < conf && same == 0; k++)
	    	{
				same = 1;
				hachage_binaire (chiffres[k], taillem, tab2);
				for (j = 0; j < taille - 1; j++){
					// on vérifie que le symétrique n'ai pas déja été pris en compte 
					if (tab[j] != tab2[(taillem) - j - 1]){
						same = 0;
						break;
		    		}
				}
				/*if (same == 1 ){
					//on est le même 
					printf("on est le même \n");
					for (j = 0; j < taille - 1; j++){
						printf("%c  =  %c",tab[j],tab2[(taillem) - j - 1]);
					}
					printf("\n");
				}*/
				
	    	}
	  		if (same == 0)
	    	{
	      	//on le garde   
	     		printf ("%d = ",i);
	     		for (k = 0; k < taillem; k++){
	     			printf("%c",tab[k]);
	     		}
	     		//printf(" conf = %d et on a  le doit a %ld confs",conf, NB_conf(robots, taille));
	     		chiffres[conf] = i;
				//	printf (" on a bien %d ",i);
				printf ("\n");
	      	conf++;
	    	}
		}
    }

  printf ("on a %d chiffres\n avec %d non symétriques et on avait le droit a %ld confs\n", nb, conf,NB_conf(robots, taille));
	return conf;
}

//flocchini part 1 -> on doit vérifier 
void flocchini(int robots, int taille, FILE * out){
	int c,i,j,k,tmp;
	int conf; //le nombre de configurations
	int d; //interdistance
	int taillem= taille -1;
	//printf("taillem = %d\n",taillem);
	long essai = NB_conf(robots, taille);
	printf("essai = %ld \n",essai);
	
	int block_fini=0;
	
	
	//on récupère tous les config possibles 
	int *chiffres = malloc(essai * sizeof(*chiffres));
	//for(i=0; i< essai; i++)
		//chiffres[i] = malloc(taille * sizeof(**chiffres));
	
	conf = config(chiffres, robots, taille, essai);
	//													//																	//															//
	//													//																	//															//
	//													//																	//															//
	//													//																	//															//
	//													//																	//															//
	//													//																	//															//
	//													//																	//															//
	//													//																	//															//
	//													//																	//															//
	//													//																	//

	
	for (c=0; c<conf && chiffres[c]!= 0; c ++){
		d = -1;
		tmp=1;
		block_fini=0;
		int no_init=0;
		//
	Block *block = malloc(sizeof(*block));
	block->LeadingRi='0';//-2;//NULL;
	block->taille=1;
	block->border_max=-1;
	block->border_min=-1;
	block->next=NULL;
	List *blocks = malloc(sizeof(*blocks));
	blocks->b=block; // head
	blocks->current=block; //tail
	blocks->nb_block=1;
	blocks->max_size=1;
	blocks->min_size=taille; 
		/*
		*interdistance
		*/
	char tab[taillem];
	hachage_binaire(chiffres[c],taillem,tab);
	
		printf ("la conf ");
		for (i=0; i<taillem; i++){
			printf ("%c", tab[i]);
			if(d<tmp && !block_fini && d!=-1){ //FINI
				block_fini=1; 
				if (blocks->current->taille == 1){ //c'est un isolé
				// soit c le même que b => flag no init
					if(blocks->current->border_min == blocks->b->border_min){
						no_init= 1;
					}else{ // sinon faut en enlever un ...
						Block *b = blocks->b;
						while( b->next->border_min !=	blocks->current->border_min){
							b = b-> next;
						}
						//on supprime le current
						blocks->current = b;
						blocks->current->next=NULL;				
					}
				}
			}if (tab[i] == '0'){
				tmp++;
			}else {
				if(d==tmp){
					//printf("(1)");
					blocks->current->taille ++;
					blocks->current->border_max=i;
				}
				if((d==-1) && !block_fini){
					d=tmp;
					blocks->current->taille++;
					//printf("(2)");
					blocks->current->border_max=i;
				}
				if(d > tmp && !block_fini){
					//printf("(3)");
					d=tmp;
					//nouvelle interdistance blocks a refaire
					int tmp2 = blocks->current->border_max;
						//on vide la liste et on refait le premier block
					blocks->b->taille = 2;
					blocks->b->border_max = i;
					blocks->b->border_min = tmp2;
					blocks->b->next = NULL;
					blocks->current = blocks->b;
				}	
				if(block_fini){
					//printf("(4)");
					block_fini = 0;
					Block *b;
					//si il n'ya pas de bloc initial
					if (no_init){
						b = blocks->current;
					}
					else{
						b = malloc(sizeof(*block));
					}
						//création d'un nouveau bloc
					b->LeadingRi='0';//NULL;
 					b->taille=1;
  				b->border_max=i;
  				b->border_min=i;
  				b->next=NULL;
  				blocks->current->next = b;
  				blocks->current= b;
				}
				//
				tmp=1;
			}
		}
		printf(" a comme interdistance %d",d);
		// on vérifie que l'interdistance ne soit pas une valeur absurde
		if( d > (taille - robots)+1 || d==-1 )//cas d'erreur
			printf("\t L'interdistance n'est pas bonne > %d ",taille - robots+1); 
		printf("\n");
		//
		//printf("\t %d \t",blocks->current->border_max);
		if(blocks->b->border_min==-1 && blocks->current->border_max==taillem-d && blocks->b->border_min != blocks->current->border_min){
		// on enleve le dernier et on le rajoute au premier
			//printf("ending\n");
			Block *b = blocks->b;
			b->border_min = blocks->current->border_min;
			b->taille += blocks->current->taille;
			while( b->next->border_min !=	blocks->current->border_min){
				b = b-> next;
			}
			//on supprime le current
			blocks->current = b;
			blocks->current->next=NULL;	
		}
		if (blocks-> current->taille == 1){ //le dernier est un isolé
		//faut en enlever un ...
			//printf("isolé \n ");
			Block *b = blocks->b;
			while( b->next->border_min !=	blocks->current->border_min){
				b = b-> next;
			}
			if(taillem-d == blocks->current->border_min){ //le bloc 0 s'agrandit
				blocks->b->border_min = blocks->current->border_min;
				blocks->b->taille ++;
			}// on supprime le current
			blocks->current = b;
			blocks->current->next=NULL;	

		}
		int nb_isol=robots;
		// on vérifie nos blocs
		Block *b = blocks->b;
		blocks->nb_block=0;
		while(b != NULL ){
        fprintf(out, "//bloc de taille %d commencant a %d  et finissant %d \n",b->taille, b->border_min, b->border_max);
		printf("bloc de taille %d commencant a %d  et finissant %d \n",b->taille, b->border_min, b->border_max);
		if (blocks->max_size < b->taille)
			blocks->max_size = b->taille;
		if (blocks->min_size > b->taille)
			blocks->min_size = b->taille;
		nb_isol = nb_isol - b->taille;
		b = b->next;
		blocks->nb_block ++;
		}
		printf("On a %d blocks\n",blocks->nb_block);
		//
//
/*
* CAS A
*/
// regarder si R est isolé ... => on est dans le cas A
//if( !(blocks->b->border_min==-1 || blocks->b->border_min>blocks->b->border_max))
//	printf("Je suis un isolé => on est dans le cas A\n");
	//
if( nb_isol >= 1){
	printf("A : \t");
	fprintf( out, "//CAS A \n");
    int interet = 0;
    fprintf(out, "//");
    for(i=0; i<taille; i++)
        fprintf( out, "%c \t", tab[i] );
    fprintf( out, "\n");
    if (blocks->b->border_min > blocks->b->border_max)
        goto ininterressant;
    if ( blocks->b->border_min == -1)
        goto ininterressant;
	// Je bouge si mes voisins directs sont des blocs de size max et que la distance qui me sépare de ces blocs est minimal
    interet = 1; 
	int neighbor = 0; // il existe un neighbor ???
	int dist_neighbor = taille;
	List_Ri	*R_neighbor = malloc(sizeof(List_Ri));
	R_neighbor->robot = -2;
	R_neighbor->direction = 'n';
	R_neighbor->current = R_neighbor;
	R_neighbor->next = NULL;
	char direction; 
	//printf("essai\n");
	for(i=blocks->max_size; i>=0 ; i--){
		Block *b = blocks->b;
        Block *last = blocks->b;
        neighbor =0; //////////////////////////////////////////////////////////////////////////
		while(b!=NULL){
			if (b->taille == i){
				// on trouve le neighor le plus près
				if(b->next != NULL){
					for(j=b->border_max+1; j < b->next->border_min ;j++){
						if(tab[j]=='1'){
							//printf(" %d est un voisin \n", j);
						  // on a trouvé un neighbor isolé
						  neighbor = 1;
						  if( (b->next->taille==i) && (b->next->border_min - j <= dist_neighbor) ){
						  if ((b->next->taille==i) && (b->next->border_min - j < dist_neighbor) ){
						  	dist_neighbor = b->next->border_min -j;
						  	// on supprime la liste et on la recommence
						  	R_neighbor->robot = j;
								R_neighbor->direction = '-';
								R_neighbor->next = NULL;//a freer
								R_neighbor->current = R_neighbor;
						  }else{
									// on le rajoute						  
						  		if(R_neighbor->current->robot == -2){ // on remplace 
							  		R_neighbor->current->robot = j;
							 		 	R_neighbor->current->direction = '-';
						  		}
						  		if (R_neighbor->current->robot != j){
						  			List_Ri *R = malloc(sizeof(List_Ri));
						  			R_neighbor->current->next = R;
						  			R_neighbor->current = R;
						  			R_neighbor->current->robot = j;
										R_neighbor->current->direction = '-';
										R_neighbor->current->next = NULL;
									}
						  	}
						  }
						  if(dist_neighbor >= j - b-> border_max){
						  	if (dist_neighbor > j - b-> border_max){
						  	dist_neighbor = j - b-> border_max;
						  	// on supprime la liste et on la recommence
						  	R_neighbor->robot = j;
								R_neighbor->direction = '+';
								R_neighbor->next = NULL;//a freer
								R_neighbor->current = R_neighbor;						  
						 	 }else{
						  		// on le rajoute	
						  		if (R_neighbor->current->robot == j){
										R_neighbor->current->direction = '=';// les deux directions;
									}					  
						  		if(R_neighbor->current->robot == -2){ // on remplace 
							  		R_neighbor->current->robot = j;
							  		R_neighbor->current->direction = '+';
						  		}
						  		if (R_neighbor->current->robot != j){
						  			List_Ri *R = malloc(sizeof(List_Ri));
						  			R_neighbor->current->next = R;
						  			R_neighbor->current = R;
						  			R_neighbor->current->robot = j;
										R_neighbor->current->direction = '+';
										R_neighbor->current->next = NULL;
									}
								}
						  }

						}
					}	
				}else{ // on a pas de suivant ...
                    //cas dernier bloc qui est donc de bonne taille
                    for(j = b->border_max + 1; j <= taillem ;j++){
                        if(tab[j]=='1'){
                            neighbor = 1;
                            if(j - b->border_max <= dist_neighbor){
                                if (j - b->border_max < dist_neighbor){
                                    dist_neighbor = j - b->border_max;
                                    // on supprime la liste et on la recommence
                                    R_neighbor->robot = j;
                                    R_neighbor->direction = '+';
                                    R_neighbor->next = NULL;//a freer
                                    R_neighbor->current = R_neighbor;
                                }else{
                                    // on le rajoute
                                    if (R_neighbor->current->robot == j){
                                        R_neighbor->current->direction = '=';// les deux directions;
                                    }
                                    if(R_neighbor->current->robot == -2){ // on remplace
                                        R_neighbor->current->robot = j;
                                        R_neighbor->current->direction = '+';
                                    }
                                    if (R_neighbor->current->robot != j){
                                        List_Ri *R = malloc(sizeof(List_Ri));
                                        R_neighbor->current->next = R;
                                        R_neighbor->current = R;
                                        R_neighbor->current->robot = j;
                                        R_neighbor->current->direction = '+';
                                        R_neighbor->current->next = NULL;
                                    }
                                }
                            }
                        }
                    }
                    //cas dernier bloc pour -1
                    if(dist_neighbor >= taillem - b->border_max ){
                        //printf (" + \n");
                        if (dist_neighbor > taillem - b->border_max ){
                            dist_neighbor = taillem - b->border_max;
                            // on supprime la liste et on la recommence
                            R_neighbor->robot = -1;
                            R_neighbor->direction = '+';
                            R_neighbor->next = NULL;//a freer
                            R_neighbor->current = R_neighbor;
                        }else{
                            // on le rajoute
                            if (R_neighbor->current->robot == -1){
                                R_neighbor->current->direction = '=';// les deux directions;
                            }
                            if(R_neighbor->current->robot == -2){ // on remplace
                                R_neighbor->current->robot = -1;
                                R_neighbor->current->direction = '+';
                            }
                            if (R_neighbor->current->robot != -1){
                                List_Ri *R = malloc(sizeof(List_Ri));
                                R_neighbor->current->next = R;
                                R_neighbor->current = R;
                                R_neighbor->current->robot = -1;
                                R_neighbor->current->direction = '+';
                                R_neighbor->current->next = NULL;
                            }
                        }
                    }
                }
			}
            if (b->next != NULL)
                last = b->next;
			b = b->next;
            
		}
        //le premier bloc prend ce qu'ily a a la fin
        {//cas premier bloc
            if (blocks->b->border_min >-1 && (blocks->b->border_min < blocks->b->border_max) && blocks->b->taille ==i ){
                //printf(" premier bloc avec -");
                for(j = blocks->b->border_min - 1; j>=0 ;j--){
                    if(tab[j]=='1'){
                        neighbor = 1;
                        if(blocks->b->border_min - j <= dist_neighbor){
                            if (blocks->b->border_min -j < dist_neighbor){
                                dist_neighbor = blocks->b->border_min -j;
                                // on supprime la liste et on la recommence
                                R_neighbor->robot = j;
                                R_neighbor->direction = '-';
                                R_neighbor->next = NULL;//a freer
                                R_neighbor->current = R_neighbor;
                            }else{
                                // on le rajoute
                                if (R_neighbor->current->robot == j){
                                    R_neighbor->current->direction = '=';// les deux directions;
                                }
                                if(R_neighbor->current->robot == -2){ // on remplace
                                    R_neighbor->current->robot = j;
                                    R_neighbor->current->direction = '-';
                                }
                                if (R_neighbor->current->robot != j){
                                    List_Ri *R = malloc(sizeof(List_Ri));
                                    R_neighbor->current->next = R;
                                    R_neighbor->current = R;
                                    R_neighbor->current->robot = j;
                                    R_neighbor->current->direction = '-';
                                    R_neighbor->current->next = NULL;
                                }
                            }
                        }
                    }
                }
                //
                //on rajoute le - 1 pour le premier bloc
                if(blocks->b->border_min + 1 <= dist_neighbor){
                    neighbor = 1;
                    //printf (" - \n");
                    if ((blocks->b->taille==i) && (blocks->b->border_min + 1< dist_neighbor) ){
                        //printf (" -0 \n");
                        dist_neighbor = blocks->b->border_min + 1;
                        // on supprime la liste et on la recommence
                        R_neighbor->robot = -1;
                        R_neighbor->direction = '-';
                        R_neighbor->next = NULL;//a freer
                        R_neighbor->current = R_neighbor;
                    }else{  //printf (" -1 \n");
                        // on le rajoute
                        if (R_neighbor->current->robot == -1){
                            R_neighbor->current->direction = '=';// les deux directions;
                        }
                        if(R_neighbor->current->robot == -2){ // on remplace
                            //printf (" -11 \n");
                            R_neighbor->current->robot = -1;
                            R_neighbor->current->direction = '-';
                        }
                        if (R_neighbor->current->robot != -1){
                            //printf (" -12 \n");
                            List_Ri *R = malloc(sizeof(List_Ri));
                            R_neighbor->current->next = R;
                            R_neighbor->current = R;
                            R_neighbor->current->robot = -1;
                            R_neighbor->current->direction = '-';
                            R_neighbor->current->next = NULL;
                        }
                    }
                }
            }	
        }
		if( neighbor== 1)
			break;
    }
ininterressant:
    //printf("bli\n");
    {
    int move = 0;
    if (interet == 1){
        List_Ri *b = R_neighbor;
        //printf("avec une distance de %d \n",dist_neighbor);
        while(b != NULL){
			//printf(" robot %d est en %c \n",b->robot,b->direction);
			if (b->robot == -1){
				move = 1;
				printf("GOGOGOGO !!!!!!!!!!!!!!!!!! \n");
				if (b-> direction == '+'){
					robot(chiffres[c], taille, out, '-');
				}else{
					robot(chiffres[c], taille, out, '+');
				}
                break;
			}
			b = b->next;
		}
    }
    if( !move ){
        printf("STOP\n");
        idle(chiffres[c], taille, out);
    }
    }
}
//
/*
*
* AUTRE CAS 
*
*/	
if( nb_isol < 1){
//
	//définir dans quel cas on est
	//si tous les blocs sont leading et d=1 => D
	// si d>1 et tous leading => C
	//a moins un bloc non-leading => B
	//
	//
	////////////////////////////////////////     C     /////////////////////////////////////////////
	if( ((blocks->nb_block == 2 && blocks->b->taille == blocks->b->next->taille)||(blocks->nb_block == 1)) && d>=2){
		printf(" CC : \t");
		fprintf(out, "// CC : \t");
		if (blocks->nb_block == 2){
			fprintf(out, "// CC2 \n");
			printf("CC2 \n");
			printf("on est dans le cas nb_block == 2 \n");
			//printf("max = %d ",blocks->b->border_max);
			//printf("\tmin + 1=%d \n",blocks->b->next->border_min);
			int F1 = blocks->b->next->border_min - blocks->b->border_max;
			//printf("F1 = %d\n",F1);
			int F2 = 0;
			if(blocks->b->next->border_max < blocks->b->next->border_min){
				F2 = blocks->b->border_min - blocks->b->next->border_max;
			}else{ //R est toujours dans le premier bloc
				F2 = taillem - blocks->b->next->border_max;
				//printf("here !!!!\n");
			}
			//printf("F2 = %d\n",F2);
			if( F1 < F2){
				blocks->b->LeadingRi='-';//b->bordermin se déplace en plus
				//printf(" %d et ",blocks->b->border_min);
				if(blocks->b->border_min == -1){
					printf("GOGOGO !!!!!!!!!!!!!!!\n");
					robot(chiffres[c], taille, out, '+');
				}else{
					printf("STOP\n");
					idle(chiffres[c], taille, out);
				}
				blocks->b->next->LeadingRi='+';	//b->next->bordermax se déplace en moins	
				printf("%d se déplacent vers l'intérieur de leurs blocs\n",blocks->b->next->border_max);		
			}else{//cas F1 > F2 car F1 = F2 pas possible si n et k coprime
				blocks->b->LeadingRi='+';//b->bordermax se déplace vers intérieur
				printf(" %d et ",blocks->b->border_max);
				blocks->b->next->LeadingRi='-';	//b->next->bordermin se déplace vers interieur
				printf("%d se déplacent vers l'intérieur de leurs blocs\n",blocks->b->next->border_min);
				if(blocks->b->border_max == -1 || blocks->b->next->border_min == -1 || blocks->b->next->border_max == -1)
					printf("ERROR \t ERROR \t -1 \t ERROR \t ERROR\n");
				printf("STOP\n");
				idle(chiffres[c], taille, out);
			}
		}else{
			fprintf(out,"// CC1 \n");
			// LES BORDER SE DÉPLACENT VERS L'INTÉRIEUR DE LEUR PROPRE BLOC!!!!
			blocks->b->LeadingRi='=';
			printf("les deux border %d %d se déplacent vers l'intérieur\n",blocks->b->border_min, blocks->b->border_max);
			if(blocks->b->border_min == -1){
				printf("GOGOGO !!!!!!!!!!!!!!!\n");
				robot(chiffres[c], taille, out, '+');
			}else{
				printf("STOP\n");
				idle(chiffres[c], taille, out);
			}
			if(blocks->b->border_max == -1 )
				printf("ERROR \t ERROR \t -1 \t ERROR \t ERROR\n");
			if(blocks->b->next != NULL && blocks->b->next->border_min == -1)
				printf("ERROR \t ERROR \t -1 \t ERROR \t ERROR\n");
			if(blocks->b->next != NULL && blocks->b->next->border_max == -1)
					printf("ERROR \t ERROR \t -1 \t ERROR \t ERROR\n");
		}
		//
	//////////////////////////////////////      D      ////////////////////////////////////////////
	}else if( ((blocks->nb_block == 2 && blocks->b->taille == blocks->b->next->taille)||(blocks->nb_block == 1)) && d==1){
		printf("on est dans le cas D \n");
		fprintf(out, "//D \n");
		idle2(chiffres[c],taille,out);
		//PERSONNE NE FAIT RIEN
	}else{
	//////////////////////////////////////      B      ////////////////////////////////////////////
		//vérifier qu'on a bien au moin un leading block
		fprintf(out, "//B \n");
		int B=1;
		Block *b = blocks->b;
		int size = blocks->max_size;
		while(b!=NULL){
			if(size != b->taille){
				B=2;		
				break;
			}
			b = b->next;
		}
		if(B==1){ /////////// B1 /////////
		// tous les blocks ont la même taille
			printf("B1 : \t");
			fprintf(out, "//B1 \t"); 
			Block *b = blocks->b;
			int size = blocks->max_size;
			int min, max;
			Leader *leader = malloc(sizeof(*leader));
			leader->value =0;
			leader->R1 = leader->R2 = -2;
			leader->R1_pos = leader->R2_pos = '0';
			while(b!=NULL){
				if(size == b->taille){
					// on calcul la value pour min et max 
 					min = valueB(taillem,chiffres[c],b->border_min,'-');
 					max = valueB(taillem,chiffres[c],b->border_max,'+');
					// value = max(min,max)
					if(((max == leader->value)||(min == leader->value))&& leader-> R2 != -2){
						printf("ERROR \t ERROR \t ERROR \n");
						printf("valeur pour les leader = %d\n",leader->value);
						printf(" les deux leader sont %d%c %d%c et moi %d %d \n",leader->R1,leader->R1_pos,leader->R2, leader->R2_pos,b->border_min, b->border_max);
						//return;
                        idle(chiffres[c], taille, out);
                        break;
					}
					if(max == leader->value){
						leader->R2 = b->border_max;
						leader->R2_pos = '+';
					}
					if(min == leader->value){
						leader->R2 = b->border_min;
						leader->R2_pos = '-';
					}
					if(max > leader->value){
						leader->value = max;
						leader->R1 = b->border_max;
						leader->R2 = -2;
						leader->R1_pos = '+';
						leader->R2_pos = '0';
					}
					if(min > leader->value){
						leader->value = min;
						leader->R1 = b->border_min;
						leader->R2 = -2;
						leader->R1_pos = '-';
						leader->R2_pos = '0';
					}
				}
				b = b->next;
			}
			//printf("les leader sont %d%c %d%c \n",leader->R1,leader->R1_pos,leader->R2, leader->R2_pos);
			if(leader->R2 == -2){
				fprintf(out, " un leader \n");
				printf("le leader = %d sort de son block\n",leader->R1);
				if (leader->R1 == -1){
					printf("GOGOGOGO !!!!!!!!!!!!!!!!!! \n");
					robot(chiffres[c], taille, out, leader->R1_pos);
				}else{
					idle(chiffres[c], taille, out);
				} 
			}else{
				fprintf( out, "//2 leaders \t");
				if(blocks->max_size == 2){
					fprintf(out, " blocs de taille 2 \n");
					if(blocks->nb_block < 9)
						printf("EERROOOORR !!! \n");
					// -1 fait forcément parti 
					int SYM = 0;
					char premierSym = '-';
					int val = valueB(taille-1, chiffres[c],blocks->b->border_min , '-');
					if(val < valueB(taille-1, chiffres[c],blocks->b->border_max , '+') ){
						Block *b= blocks->b->next->next->next->next;
						if (b==NULL)
							printf("ERRRORRR !!!\n");
						while(b->next != NULL && b->next->next != NULL && b->next->next->next!= NULL){
							if(val == valueB(taille-1, chiffres[c],b->border_max , '+')){
								//ils sont symétriques
								//printf("-1 est symétriques avec %d \t",b->border_max );
								
								robot(chiffres[c], taille, out, '-');
								SYM = 1;
								break;							
							}						
							b = b->next;
						}
					}else{
					//printf("0 avait une valueB  plus petite\n");
					}
					if(!SYM){
						printf("STOP \n");
						idle(chiffres[c], taille, out);
					}					
					printf("mouvement =  ? !\n");
					
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
					
				}else{
					fprintf(out, " blocs de taille > 2 \n");
					int dist = taille;
					Block *b = blocks->b;
					Leader *sym = malloc(sizeof(*sym));
					sym->value = taille;
					sym->R1 = sym->R2 = -2;
					sym->R1_pos = sym->R2_pos = '0';
					while(b != NULL){//pour tous les blocs
						min = valueB(taillem,chiffres[c],b->border_min,'-');
 						max = valueB(taillem,chiffres[c],b->border_max,'+');
 						//printf("min = %d et max = %d\n",min, max);
 						
 						if(min == max){
							dist = Dist (b->border_min, b->border_max, taille);
							//printf("min = max et Dist = %d \n",dist);
							if(sym->value > dist){
 								sym->value = dist;
 								sym->R1 = b->border_max;
 								sym->R1_pos = '+';
 								sym->R2 = b->border_min;
 								sym->R2_pos = '-';
 							}
						}
 						Block *n = b->next;
 						while(n != NULL){
 							if (valueB(taillem,chiffres[c],n->border_min,'+') == max){
 								dist = Dist (n->border_min , b->border_max, taille);
 								if((sym->value > dist) && (b->next->border_min != n->border_min)){
 									sym->value = dist;
 									sym->R1 = b->border_max;
 									sym->R1_pos = '+';
 									sym->R2 = n->border_min;
 									sym->R2_pos = '-';
 								}
 							}
 							if (valueB(taillem,chiffres[c],n->border_max,'+') == min){
 								dist = Dist (n->border_max , b->border_min, taille);
 								if((sym->value > dist) && (b->next->border_max != n->border_max) ){
 									sym->value = dist ;
 									sym->R1 = b->border_min;
 									sym->R1_pos = '-';
 									sym->R2 = n->border_max;
 									sym->R2_pos = '+';
 								}
 							}
 							n = n->next;
 						}
						b = b->next;
					}
					printf("ce sont R1=%d et R2=%d qui bougent pour sortir de leurs blocs!!!!\n",sym->R1,sym->R2);
					if(sym->R1 == -1){
						robot(chiffres[c], taille, out, sym->R1_pos);
					}else if(sym->R2 == -1){
						robot(chiffres[c], taille, out, sym->R2_pos);
					}else{
						printf("STOP \n");
						idle(chiffres[c], taille, out);
					}
				}
			}
		}else{ ////////// B2 //////////
			fprintf(out, "//B2 \t tab =");
            for(i=0; i<taillem; i++)
                fprintf( out, "%c", tab[i] );
			printf("B2 : \t");
            fprintf(out, "\n //et on a blocks->b->taille = %d \n", blocks->b->taille);
            if(blocks->b->border_min != -1 || blocks->b->taille != blocks->min_size){
                fprintf(out, "//pas moi \n");
                goto ininterressantB2;
            }
			//printf(" la taille min d'un block est %d\n",blocks->min_size);
			int view = 0;
			int dist = taille;
			//Block *sb = malloc(sizeof(sb));
			List *s= malloc(sizeof(*s)); //maliste
			Block *sb = malloc(sizeof(*sb)); //block courant de la liste
			s->b=NULL; // head
            s->current=NULL; //tail
            blocks->nb_block=0;
			int block_fini=0;
			sb= s->b;
			i= blocks->max_size; //va représenter le taille la plus grande
            int S_ok = 0; //la taille la plus grande trouvé
			while( i > blocks->min_size && !S_ok){
                Block *b = blocks->b;
				while(b!=NULL){
					if(b->next != NULL){
						if (b->taille == blocks->min_size){ //block de taille s notre max bouge si il la vue max
							fprintf(out, "// block de taille s \n");
							if(b->next->taille == i && dist >= Dist(b->border_max, b->next->border_min, taille)){
								if(dist == Dist(b->border_max, b->next->border_min, taille) ){
									if(view <= valueB(taille-1, chiffres[c],b->border_max , '+')){
                                        if (view < valueB(taille-1, chiffres[c],b->border_max , '+')){
                                            //on crée une nouvelle liste...
                                            fprintf(out, "// on ajoute %d \n", b->border_max);
                                            S_ok = 1;
                                            dist = b->next->border_min - b->border_max;
                                            view = valueB(taille-1, chiffres[c],b->border_max , '+');
                                            s = malloc(sizeof(*s));
                                            s->nb_block = 1;
                                            s->b = malloc(sizeof(*sb));
                                            s->b->LeadingRi='+';//c'est le max qui est proche d'un bloc de taille S
                                            s->b->taille=b->taille;
                                            s->b->border_max=b->border_max;
                                            //printf("%d va bouger\n",b->next->border_max);
                                            s->b->border_min=-2;
                                            s->b->next=NULL;
                                            sb = s->b;
                                        }else {
                                            //printf("bla \n");
                                            // on m'ajoute à la liste
                                            S_ok = 1;
                                            if (sb != NULL){
                                                sb = sb->next;
                                                sb = malloc(sizeof(*sb));
                                            }
                                            sb->LeadingRi='+';//c'est le max qui est proche d'un bloc de taille S
                                            sb->taille=b->taille;
                                            sb->border_max=b->border_max;
                                            //printf("%d va bouger\n",b->next->border_max);
                                            sb->border_min=-2;
                                            sb->next=NULL;
                                            s->nb_block ++;
                                        }
                                    }
								}
                                if( (dist > Dist(b->border_max, b->next->border_min, taille)) ){
									//printf("bla2 \n");
									//on creer une nouvelle liste
									S_ok = 1;
									dist = Dist(b->border_max, b->next->border_min, taille);
									view = valueB(taille-1, chiffres[c],b->border_max , '+');
									s = malloc(sizeof(*s));
									s->nb_block = 1;
									s->b = malloc(sizeof(*sb));
									s->b->LeadingRi='+';//c'est le max qui est proche d'un bloc de taille S
                                    s->b->taille=b->taille;
                                    s->b->border_max=b->border_max;
                                    //printf("%d va bouger\n",b->next->border_max);
                                    s->b->border_min=-2;
                                    s->b->next=NULL;
                                    sb = s->b;
                                }
							}					
						}else{ // block de taille S
							//printf("bla3 \n");
							if(b->next->taille == blocks->min_size && b->taille == i  && dist >= Dist(b->next->border_min , b->border_max, taille)){
								if(dist == Dist(b->border_max, b->next->border_min, taille) ){
									if(view <= valueB(taille-1, chiffres[c],b->next->border_min , '-')){
                                        if(view < valueB(taille-1, chiffres[c],b->next->border_min , '-')){
                                            //on crée une nouvelle liste
                                            S_ok = 1;
                                            //printf("bla5 \n");
                                            dist = Dist(b->border_max, b->next->border_min, taille);
                                            view = valueB(taille-1, chiffres[c],b->next->border_min , '-');
                                            s = malloc(sizeof(*s));
                                            s->nb_block = 1;
                                            s->b = malloc(sizeof(*sb));
                                            s->b->LeadingRi='-';//c'est le min qui est proche d'un bloc de taille S
                                            s->b->taille=b->taille;
                                            s->b->border_max=-2;
                                            //printf("%d va bouger\n",b->next->border_min);
                                            s->b->border_min=b->next->border_min;
                                            s->b->next=NULL;
                                            sb = s->b;
                                        }
                                        else{
                                            // on ajouteb-> next  à la liste si je n'y suis pas déja
                                            //printf("bla4 \n");
                                            S_ok = 1;
                                            if (sb != NULL){
                                                sb = sb->next;
                                                sb = malloc(sizeof(*sb));
                                            }
                                            sb->LeadingRi='-';//c'est le min qui est proche d'un bloc de taille S
                                            sb->taille=b->next->taille;
                                            sb->border_max=-2;
                                            //printf("%d va bouger\n",b->next->border_min);
                                            sb->border_min=b->next->border_min;
                                            sb->next=NULL;
                                            s->nb_block ++;
                                        }
                                    }
								}if(dist > Dist(b->border_max, b->next->border_min, taille)) {
									//on creer une nouvelle liste
									S_ok = 1;
									//printf("bla5 \n");
									dist = Dist(b->next->border_min , b->border_max, taille);
									view = valueB(taille-1, chiffres[c],b->next->border_min , '-');
									s = malloc(sizeof(*s));
									s->nb_block = 1;
									s->b = malloc(sizeof(*sb));
									s->b->LeadingRi='-';//c'est le min qui est proche d'un bloc de taille S
  								s->b->taille=b->taille;
  								s->b->border_max=-2;
  								//printf("%d va bouger\n",b->next->border_min);
  								s->b->border_min=b->next->border_min;
  								s->b->next=NULL;
  								sb = s->b;
								}
							}
						}
					}else{
                        //faire le cas du dernier block  // *b pointe sur le dernier bloc // pour prendre en charg le premier block
                        fprintf(out, "// else dernier bloc : dist = %d et distance entre %d et %d = %d", dist, b->border_max,blocks->b->border_min, Dist(b->border_max, blocks->b->border_min, taille) );
                    	if(b->taille == i  && dist >= Dist(b->border_max, blocks->b->border_min, taille)){
                            if( dist == Dist(b->border_max, blocks->b->border_min, taille) ){
                                // on ajouteb-> next  à la liste si je n'y suis pas déja
                                if(view <= valueB(taille-1, chiffres[c],blocks->b->border_min , '-')){
                                    if (view < valueB(taille-1, chiffres[c],blocks->b->border_min , '-')){
                                        // on crée une nouvelle liste
                                        S_ok = 1;
                                        //printf("bla5 \n");
                                        dist = Dist(b->border_max, blocks->b->border_min, taille);
                                        view = valueB(taille-1, chiffres[c],blocks->b->border_min , '-');
                                        s = malloc(sizeof(*s));
                                        s->nb_block = 1;
                                        s->b = malloc(sizeof(*sb));
                                        s->b->LeadingRi='-';//c'est le min qui est proche d'un bloc de taille S
                                        s->b->taille=b->taille;
                                        s->b->border_max=-2;
                                        //printf("%d va bouger\n",b->next->border_min);
                                        s->b->border_min=blocks->b->border_min;
                                        s->b->next=NULL;
                                        sb = s->b;
                                    }else{
                                        S_ok = 1;
                                        //printf("bla4 \n");
                                        if (sb != NULL){
                                            sb = sb->next;
                                            sb = malloc(sizeof(*sb));
                                        }
                                        sb->LeadingRi='-';//c'est le min qui est proche d'un bloc de taille S
                                        sb->taille=blocks->b->taille;
                                        sb->border_max=blocks->b->border_max;
                                        //printf("%d va bouger\n",b->next->border_min);
                                        sb->border_min=blocks->b->border_min;
                                        sb->next=NULL;
                                        s->nb_block ++;
                                    }
                                }
                            }if(dist > Dist(b->border_max, blocks->b->border_min, taille)){
                                //on creer une nouvelle liste
                                S_ok = 1;
                                //printf("bla5 \n");
                                dist = Dist(blocks->b->border_min, b->border_max, taille);
                                view = valueB(taille-1, chiffres[c],blocks->b->border_min , '-');
                                s = malloc(sizeof(*s));
                                s->nb_block = 1;
                                s->b = malloc(sizeof(*sb));
                                s->b->LeadingRi='-';//c'est le min qui est proche d'un bloc de taille S
                                s->b->taille=b->taille;
                                s->b->border_max=-2;
                                //printf("%d va bouger\n",b->next->border_min);
                                s->b->border_min=blocks->b->border_min;
                                s->b->next=NULL;
                                sb = s->b;
                            }
                        }
					}
					b = b->next;
				}
			if (S_ok == 0){
				i--;	
			}else
			break;
		} // fin
            {
        fprintf(out, "//taille max = %d \n",i);
		int B2_move =0;
		while(sb != NULL){
			//printf("%c %d ou %d  bouge avec dist=%d \n",sb->LeadingRi,sb->border_min, sb->border_max,dist);
			if(sb->border_max == -1){
				B2_move = 1;
				printf("GOGOGO....\n");
				robot(chiffres[c], taille, out, '+');
			}else if(sb->border_min == -1){
				B2_move = 1;
				printf("GOGOGO....\n");
				robot(chiffres[c], taille, out, '-');
			}		
			sb = sb->next;
		}

		if(!B2_move){
			printf("STOP \n");
ininterressantB2:
			idle(chiffres[c], taille, out);
		}
        }
		//printf("bli2\n");
		}
	}//fin B
}

	printf("\n");
	}
	return;
}

/*
int main (int argc, char **argv)
{
	int robots = 18;
	int taille = 23;
	if (pgcd ( robots, taille) != 1){ 
		printf(" le nombre de robots et la taille de l'anneau doivent etre premiers entre eux! \n");
		return 1;
	}
	FILE *out;
	out = fopen (strdup ("essai.dve"), "w+");
	flocchini(robots, taille,out);
	/*	int i, c, conf, tmp;
	int essai = (1 << (taille - 1));
	char **chiffres = malloc(essai * sizeof(*chiffres));
  for(i=0; i< essai; i++)
  	chiffres[i] = malloc(taille * sizeof(**chiffres));
	conf = config(chiffres, robots, taille);
	for (c=0; c<conf; c ++){
		printf ("la conf ");
		for (i=0; i<taille -1; i++)
			printf ("%c", chiffres[c][i]);
		tmp = valueB(taille-1, chiffres[c], -1, '-');
		printf (" - 1 = %d\n",tmp);
		tmp = valueB(taille-1, chiffres[c], -1, '+');
		printf (" + 1 = %d\n",tmp);
		printf("\n");
	} *//*
	
	//int k;
	//char tab[taille-1];
	//hachage_binaire(131,taille-1,tab);
	//for (k = 0; k < taille - 1; k++){
		//printf("%c",tab[k]);
	//}
	
	
	return 0;
}*/



void algomin(int robots, int taille, FILE *out, int new)
{
	int c,j;
	int R1, R2, Fx, Fy, Fz;
	int taillem= taille -1;
	int essai = (1<<taillem);
	int conf;
	long nb_conf = NB_conf(robots, taille);
	
	//on récupère tous les config possibles (même 10..01))
  int *chiffres = malloc(essai * sizeof(*chiffres));

//tab  	
  conf = config(chiffres, robots, taille, nb_conf);
  
  //on regarde pour chaque config si il est possible de la matcher avec une des règles de l'algo min
  for(c=0; c<conf; c++){
    R1 = R2 =-1;
  	Fx = Fy = Fz = 0;
  	
  	char tab[taillem];
	hachage_binaire(chiffres[c],taillem,tab);
  	
  	//ne pas utiliser R2
  	for(j=0; j<taillem;j++)
  	{
  		//printf("%c", chiffres[i][j]);
	  	if (tab[j]=='0')
  		{
  			if(R1==-1){
  				//printf("fx++ \n");
  				Fx++;
  			}else if(R2==-1){
  				//printf("fy++ \n");
  				Fy++;
  			}else{ 
  				//printf("fz++ \n");
  				Fz++;
  		  }
  		}
  		else {
  			if(R1==-1){
  				//printf("R1 ");
  				R1=j;
  				//printf("%t R1 = %d \n",R1);
  			}else{
  				//printf("R2 \n");
  				R2=j;
  		  }
  		}
  	}
  	//printf("%d %t Fx=%d ,Fy=%d ,Fz=%d, R1=%d, R2=%d \n\n",i,Fx,Fy,Fz,R1,R2);
  	
  	
  	int bouge = 0;
  // Legitimate phase
  	//regle RL1
  	if( R1==0 && Fy==2 ){
  	  // on va vers l'arriere
  	  robot(chiffres[c], taille, out, '-');

  	  printf("%d arriere par RL1 \n",c+1 );
  	  bouge=1;
  	  }
  	if( taillem== R1 && Fy==2 ){
  		// on va vers l'avant
		robot(chiffres[c], taille, out, '+');

  		printf("%d avant par RL1 \n",c+1 );
  		bouge=1;
  		}
    //regle RL2
   	if( Fx==1 && Fz==2 ){
  	  // on va vers l'avant
  	  robot(chiffres[c], taille, out, '+');
  	  
  	  printf("%d avant par RL2 \n",c+1 );
  	  bouge=1;
  	  }
  	if( Fx==2 && Fz==1 ){
  		// on va vers l'arriere
  		robot(chiffres[c], taille, out, '-');
  		
  		printf("%d arriere par RL2 \n",c+1 );
  		bouge=1;
  	  }
   	//regle RL3
   	if( 3== R1 && Fy==0 ){
  	  // on va vers l'avant
  	  robot(chiffres[c], taille, out, '+');
  	  
  	  printf("%d avant par RL3 \n",c+1 );
  	  bouge=1;
  	  }
  	if( taillem-3== R1 && Fy==0 ){
  		// on va vers l'arriere
  		robot(chiffres[c], taille, out, '-');
  		
  		printf("%d avant par RL3 \n",c+1 );
  		bouge=1;
  	  }
  		
  //convergente phase (bon algo)

  	//regle RC1
  	if(Fx>3 && Fy<1 && Fx<Fz){
  		// on va vers l'avant
  		robot(chiffres[c], taille, out, '+');
  		
  		printf("%d avant par RC1 \n",c+1 );
  		bouge=1;
  	  }
  	if(Fz>3 && Fy<1 && Fx>Fz){
  		//on va vers l'arriere
  		robot(chiffres[c], taille, out, '-');
  		
  		printf("%d arriere par RC1 \n",c+1 );
  		bouge=1;
  	  }
  	//regle RC2
  	if(Fx==Fz && Fy!=Fz && Fx >0){
  		// on peut aller dans les deux sens
  		robot(chiffres[c], taille, out, '+');
  		
  		printf("%d both par RC2 \n",c+1 );
  		bouge=1;
  	  }
  	//regle RC3{
  	if(Fx<Fz && Fz<Fy && Fx>0 ){
  		//&& (Fx!=1 && Fz!=2)
  		//on va vers l'avant
  		robot(chiffres[c], taille, out, '+');
  		
  		printf("%d avant par RC3 \n",c+1 );
  		bouge=1;
  	  }
  	if(Fz<Fx && Fx<Fy && Fz>0){
  		//on va vers l'arriere
  		robot(chiffres[c], taille, out, '-');
  		
  		printf("%d arriere par RC3 \n",c+1 );
  		bouge=1;
  	  }
  	//regle RC4
  	if(Fy==0 && Fz==0){
	  	//avant
	  	robot(chiffres[c], taille, out, '+');
	  	
	  	printf("%d avant par RC4 \n",c+1 );
	  	bouge=1;
  	  }
  	if(Fx==0 && Fy==0){
  		//arriere
  		robot(chiffres[c], taille, out, '-');
  		
  		printf("%d arriere par RC4 \n",c+1 );
  		bouge=1;
  	  }
  	//regle RC5
  	if (new){
		//regle RC5 NEW
		if(Fx==0 && Fy==1){
			//arriere
			robot(chiffres[c], taille, out, '-');
			
			printf("%d arriere par RC5 \n, avec Fx=%d ,Fy=%d ,Fz=%d, R1=%d, R2=%d \n\n",c+1,Fx,Fy,Fz,R1,R2 );
			bouge=1;
		}
		if(Fz==0 && Fy==1){
			//avant
			robot(chiffres[c], taille, out, '+');
			
			printf("%d avant par RC5 \n, avec Fx=%d ,Fy=%d ,Fz=%d, R1=%d, R2=%d \n\n",c+1,Fx,Fy,Fz,R1,R2 );
			bouge=1;
		}
	}else{
		//regle RC5 OLD
		if(Fy==0 && Fx==1){
			//arriere
			robot(chiffres[c], taille, out, '-');
			
			printf("%d arriere par RC5 \n, avec Fx=%d ,Fy=%d ,Fz=%d, R1=%d, R2=%d \n\n",c+1,Fx,Fy,Fz,R1,R2 );
			bouge=1;
		}
		if(Fy==0 && Fz==1){
			//avant
			robot(chiffres[c], taille, out, '+');
			
			printf("%d avant par RC5 \n, avec Fx=%d ,Fy=%d ,Fz=%d, R1=%d, R2=%d \n\n",c+1,Fx,Fy,Fz,R1,R2 );
			bouge=1;
		}
	}
  	
	if(bouge==0){
		//idle
		 idle(chiffres[c], taille, out);
	}
  }	
  
  printf("\n");

}

void algomax(int robots, int taille, FILE *out, int id)//mettre les on part vers l'arrière
{
	int c,j;
	int F1, F2, F3, F4, F5, R1, R2, R3, R4, R5, R6;
	int taillem= taille -1;
	int essai = (1<<taillem);
	int conf;
	long nb_conf = NB_conf(robots, taille);
	
	//on récupère tous les config possibles (même 10..01))
  int *chiffres = malloc(essai * sizeof(*chiffres));

//tab  	
  conf = config(chiffres, robots, taille, nb_conf);
  
  //on regarde pour chaque config si il est possible de la matcher avec une des règles de l'algo max
  for(c=0; c<conf; c++){
    R1 = R2 = R3 = R4 = R5 = R6 = 0;
  	F1 = F2 = F3 = F4 = F5= -1;
  	
  	char tab[taillem];
	hachage_binaire(chiffres[c],taillem,tab);
  	
  	for(j=0; j<taillem;j++)
  	{
  		//printf("%c", chiffres[i][j]);
	  	if (tab[j]=='1')
  		{
  			if(F1==-1){
  				//printf("R1++ \n");
  				R1++;
  			}else if(F2==-1){
  				//printf("R2++ \n");
  				R2++;
  			}else if(F3==-1){
  				//printf("R3++ \n");
  				R3++;
  			}else if(F4==-1){
  				//printf("R4++ \n");
  				R4++;
  			}else if(F5==-1){
  				//printf("R5++ \n");
  				R5++;
  			}else{ 
  				//printf("R1+ = taille-j \n");
  				R6++;
  				break;
  		  }
  		}
  		else {
  			if(F1==-1){
  				//printf("F1 ");
  				F1=j;
  				//printf("%t F1 = %d \n",F1);
  			}else if(F2==-1){
  				//printf("F2 ");
  				F2=j;
  				//printf("%t F2 = %d \n",F2);
  			}else if(F3==-1){
  				//printf("F3 ");
  				F3=j;
  				//printf("%t F3 = %d \n",F3);
  			}else if(F4==-1){
  				//printf("F4 ");
  				F4=j;
  				//printf("%t F4 = %d \n",F4);
  			}else{
  				//printf("F5 \n");
  				F5=j;
  		  }
  		}
  	}
  	  	
  	
  	int bouge = 0;
  // Legitimate phase
  	//regle RL1
  	if( R1 == 0  && R2 == 0  && R3 == 0 && R4 == 2 && R5 == 0){
		//on va vers l'avant 
		robot(chiffres[c], taille, out, '+');
		bouge=1;
  		}
  	
    //regle RL2
  	if( R1 == 0  && R2 == 0  && R3 == 2 &&  R4 == 0 && R6 == 0){
		//on va vers l'avant 
		robot(chiffres[c], taille, out, '+');
		bouge=1;
  		}
   	//regle RL3
  	if( R1 == 0 && R2 == 2 && R3 == 0 && R5 == 0 && R6 == 0){
		//on va vers l'avant 
		robot(chiffres[c], taille, out, '+');
		bouge=1;
  		}
  	//regle RL4
  	if( R1 == 0 && R2 == 0 && R4 == 0 && R5 == 0 && R6 == 2){
		//on va vers l'avant 
		robot(chiffres[c], taille, out, '+');
		bouge=1;
  		}
  	//regle RL5
  	if( R1 == 0 && R3 == 0 && R4 == 0 && R5 == 2 && R6 == 0){
		//on va vers l'avant 
		robot(chiffres[c], taille, out, '+');
		bouge=1;
  		}
  		
  
    ////////////////////////////////////////////////////////////////////////////////////////
  	//regle RC1
  	if(R1 == 0 && R2 == 0 && R3 ==0 && R4 == 0 && R5 == 0){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;	
	}
	
//regles RC2
	//regle RC2_31
	if(R1 == 0 && R2 == 0 && R4 == 0 && R5 == 0 && R3 > R6 +1 && R6 > 1 ){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC2_32
	if(R1 == 0 && R2 == 0 && R3 == 1 && R4 == 0 && R5 == 0){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC2_41
	if(R1 == 0 && R3 == 0 && R4 == 0 && R5 == 0 && R6 > 1 && R2 > R6 +1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC2_42
	if(R1 == 0 && R2 == 0 && R3 == 0 && R4 == 0 && R6 == 1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC2_43
	if(R1 == 0 && R2 == 0 && R3 == 0 && R4 == 0 && R5 == 1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	
//regles RC3
	//regle RC3_31
	if(R1 == 0 && R4 == 0 && R5 == 0 && R3 > R6+1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC3_32/33
	if(R1 == 0 && R3 == 0 && R4 == 0 && R5 == R2){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC3_34
	if(R1 == 0 && R2 ==1 && R3 ==0 && R4 == 0 && R6 == 0){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC3_35
	if(R1 == 0 && R3 == 0 && R4 == 0 && R2 == R5-1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC3_21
	if(R1 == 0 && R3 == 0 && R5 == 0 && R2 > R6 + 1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
		}
	//regle RC3_22/23
	if(R1 == 0 && R2 == 0 && R3 == R4 && R5 == 0 && R3 == R4){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	
//regles RC4
	//regle RC4_1
	if(R1 == 0 && R5 == 0 && R4 > R6 +1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC4_2
	if(R1 == 0 && R5 == 0 && R4 == R6 +1 && R2 > R3){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC4_3
	if(R1 == 0 && R2 == 0 && R3 == R4 && R5 == 1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC4_4
	if(R1 == 0 && R4 == 0 && R6 == 0 && R3 == R2 +1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}

//regle RC5 
	//regle RC5_1 / RC5_2
	if(R1 == 0 && R2 == R3 && R4 == 1 && R6 == 0){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC5_3
	if(R1 == 0 && R2 == R4 && R3 == R5 && R6 +1 != R3 && R2 > R3 && R2 > R6 +1){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
	//regle RC5_4 RC5_5
	if(R1 == 0 && R2 == R5 && R3 == R4 && R6 +1 == R3 && R2 > R4){
		// on va vers l'avant 	
		robot(chiffres[c], taille, out, '+');
		bouge=1;
	}
		
  	
	if(bouge==0){
		//idle
		 idle(chiffres[c], taille, out);
	}
  }	
  
  printf("\n");

}








//int main(int argc, char **argv){
//    char tab[5];
//    unsigned long long n;
//    int i;
//    n=3;
//    printf("3 = ");
//    hachage_binaire( n, 5, tab);
//        for(i=0; i<5; i++){
//            printf("%c", tab[i]);
//        }
//    n=17;
//    printf("\n17 =");
//    hachage_binaire( n, 5, tab);
//        for(i=0; i<5; i++){
//            printf("%c", tab[i]);
//        }
//    printf("\n");
//}


