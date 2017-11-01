 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

//attention taille ne doit pas être divisible ni par robots ni par taille-robots
// pour 3 on accepte 10 11 13 14 16 17 19 20 22 ...
//10_3 => collision
//11_3 => ok
//13_3 => ok
//14_3 => ok
//16_3 => code
//voir ligne 32

char *
hachage_binaire (unsigned long long n, int length, char *retour)
{
  int i;
  int tmp;
  for (i = length - 1; i >= 0; i--)
    {
      tmp = ((n >> i) & 1);
      retour[i] = tmp + '0';
    }
  return retour;
}

int config(char **chiffres, int robots, int taille)
{
	int i, j, k, r, nb, conf;
  nb = 0;
  conf = 0;
  int same;
  int taillem= taille -1;
  //char chiffres[pow (2, taillem)][taille];
  for (i = robots; i < (1 << taillem); i++)
    {
      char tab[taillem];
      hachage_binaire (i, taillem, tab);
      r = 0;
      for (j = 0; j < taille - 1; j++)
			{
	  		if (tab[j] == '1')
	    		r++;
			}
      if (r == robots - 1)
      //on récupère tous les chiffres en binaire formés de K-1 '1' représentant les robots dans l'anneau ...
			{
	  		nb++;
	  		same = 0;
	  		for (k = 0; k < conf && same == 0; k++)
	    	{
	      	same = 1;
	      	for (j = 0; j < taille - 1; j++)
	      	// on vérifie que le symétrique n'ai pas déja été pris en compte 
					{
		  			if (tab[j] != chiffres[k][(taillem) - j - 1])
		    		{
		      		same = 0;
		      		break;
		    		}
					}
	    	}
	  		if (same == 0)
	    	{
	      	//on le garde
	     	  for (k = 0; k < taillem; k++)
					{
		  			printf ("%c", tab[k]);
		  			chiffres[conf][k] = tab[k];
					}
	      	printf ("\n");
	      	conf++;
	    	}
			}
    }

  printf ("on a %d chiffres\n avec %d non symétriques \n", nb, conf);
	return conf;
}

void algomin(int robots, int taille)
{
	int i,j;
	int R1, R2, Fx, Fy, Fz;
	int taillem= taille -1;
	int essai = (1<<taillem);
	int conf;
	
	//on récupère tous les config possibles (même 10..01))
  char **chiffres = malloc(essai * sizeof(*chiffres));
  for(i=0; i< essai; i++)
  	chiffres[i] = malloc(taille * sizeof(**chiffres));
  	
  conf = config(chiffres, robots, taille);
  
  //on regarde pour chaque config si il est possible de la matcher avec une des règles de l'algo min
  for(i=0; i<conf; i++){
    R1 = R2 =-1;
  	Fx = Fy = Fz = 0;
  	
  	
  	//ne pas utiliser R2
  	for(j=0; j<taille;j++)
  	{
  		//printf("%c", chiffres[i][j]);
	  	if (chiffres[i][j]=='0')
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
  	  printf("%d arriere par RL1 \n",i+1 );
  	  bouge=1;
  	  }
  	if( taillem== R1 && Fy==2 ){
  		// on va vers l'avant
  		printf("%d avant par RL1 \n",i+1 );
  		bouge=1;
  		}
    //regle RL2
   	if( Fx==1 && Fz==2 ){
  	  // on va vers l'avant
  	  printf("%d avant par RL2 \n",i+1 );
  	  bouge=1;
  	  }
  	if( Fx==2 && Fz==1 ){
  		// on va vers l'arriere
  		printf("%d arriere par RL2 \n",i+1 );
  		bouge=1;
  	  }
   	//regle RL3
   	if( 3== R1 && Fy==0 ){
  	  // on va vers l'avant
  	  printf("%d avant par RL3 \n",i+1 );
  	  bouge=1;
  	  }
  	if( taillem-3== R1 && Fy==0 ){
  		// on va vers l'arriere
  		printf("%d avant par RL3 \n",i+1 );
  		bouge=1;
  	  }
  		
  //convergente phase (bon algo)

  	//regle RC1
  	if(Fx>3 && Fy<1 && Fx<Fz){
  		// on va vers l'avant
  		printf("%d avant par RC1 \n",i+1 );
  		bouge=1;
  	  }
  	if(Fz>3 && Fy<1 && Fx>Fz){
  		//on va vers l'arriere
  		printf("%d arriere par RC1 \n",i+1 );
  		bouge=1;
  	  }
  	//regle RC2
  	if(Fx==Fz && Fy!=Fz && Fx >0){
  		// on peut aller dans les deux sens
  		printf("%d both par RC2 \n",i+1 );
  		bouge=1;
  	  }
  	//regle RC3{
  	if(Fx<Fz && Fz<Fy && Fx>0 ){
  		//&& (Fx!=1 && Fz!=2)
  		//on va vers l'avant
  		printf("%d avant par RC3 \n",i+1 );
  		bouge=1;
  	  }
  	if(Fz<Fx && Fx<Fy && Fz>0){
  		//on va vers l'arriere
  		printf("%d arriere par RC3 \n",i+1 );
  		bouge=1;
  	  }
  	//regle RC4
  	if(Fy==0 && Fz==0){
	  	//avant
	  	printf("%d avant par RC4 \n",i+1 );
	  	bouge=1;
  	  }
  	if(Fx==0 && Fy==0){
  		//arriere
  		printf("%d arriere par RC4 \n",i+1 );
  		bouge=1;
  	  }
  	//regle RC5
  	if(Fx==0 && Fy==1){
  		//arriere
  		printf("%d arriere par RC5 \n, avec Fx=%d ,Fy=%d ,Fz=%d, R1=%d, R2=%d \n\n",i+1,Fx,Fy,Fz,R1,R2 );
  		bouge=1;
  	  }
  	if(Fz==0 && Fy==1){
  		//avant 
  		printf("%d avant par RC5 \n, avec Fx=%d ,Fy=%d ,Fz=%d, R1=%d, R2=%d \n\n",i+1,Fx,Fy,Fz,R1,R2 );
  		bouge=1;
  	  }
  }	
  
  printf("\n");

}



