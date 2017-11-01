#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h> //pour le isprint de getopt
#include "flocchini/algo.h"

//collision=0 on n'en veut pas !!!
//#define collision 0
//SYm 0=>CORDA 1=>SYm
//#define SYM 1
// Si SYm = 1      1 => Fully  0=>Semi
//#define FULL 0

//ALGO_min=1 si on veut utiliser l'algorithme de "Exclusive Perpetual Ring Exploration without Chirality" pour un nombre minimal de robots
#define ALGO_min 1
// NEW=1 si on veut la version vérifiée (qui marche)
#define NEW 0 
//FLO=1 si on veut utiliser l'algorithme de flocchini... 
//priorité donné a cet algo!!!!
#define FLO 0


int N, K, Obs, i, proc;
char *name;
FILE *confout;
FILE *rulesout;
FILE *procout;
FILE *order;


struct option {
  int SYM;
  int FULL;
  int collision;
} option = {.SYM = 0, .FULL = -1, .collision = 0};




int
main (int argc, char **argv)
{
/** ARGS **/

  if (argc < 4)
    {
      printf
	("Usage : generateur N K Output C o n f i g u r a t i o n\n\n");
			printf ("N \t taille de l'anneau\n");
			printf ("K \t nombres de robots\n");
			printf ("Output \t fichier de sortie = Outut.dve\n");
			printf ("Configuration \t indice des robots sur l'anneau\n\n");
			printf ("Permet de créer un fichier de sortie output.dve qui représente\nK robots sur un anneau de taille N dans le model CORDA par défaut,\nayant comme configuration initiale les différentes valeurs\npassées dans C o n f i g u r a t i o n\n\n");
			printf ("options: \n");
			printf ("\t-s pour SYM comme parametre FULLY ou SEMI\n");
			printf ("\t-c pour authoriser les collisions\n\n");
      exit (0);
    }
    
  int i;
  char o;
  char* svalue = NULL;
 /*
 -s FULL          pour SYM FULL
 -c pour les collisions
 */
 	i = getopt (argc, argv, "s:c");

   while(i != -1)
  {
//printf("blablabalbkeflj\n");
         switch (i)
           {
           case 's':
             option.SYM = 1;
             svalue = optarg;
             break;
           case 'c':
             option.collision = 1;
             break;
           case '?':
             if (optopt == 's')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n", optopt);
             return 1;
           default:
             abort ();
           }
           i = getopt (argc, argv, "s:c");
   }        
 	if ( svalue && (strcmp("FULL", svalue)) == 0)
 		option.FULL = 1; 		
 	else if (svalue && (strcmp("SEMI",svalue)) == 0)
 		option.FULL = 0; 
 	else if (svalue)
 		fprintf (stderr,"unknown value %s for option -s `\\x%x'.\n", svalue, optopt);
  
           
  N = atoi (argv[optind]);
  K = atoi (argv[optind + 1]);
  
  if (K >= N)
	printf(" Le nombre de robots doit être inférieur a la taille de l'anneau !!!\n");
/*  Obs = atoi (argv[optind + 2]);
//le robot ne s'observe pas lui même et ne peut pas observer plus que ce qui existe
  if (Obs >= N)
    Obs = N - 1;
*/

  name = strdup (argv[optind + 2]);
  char tmp[32];
  char tmp2[32];
  sprintf(tmp,"%s.dve",name);
  rulesout = fopen ( tmp, "w+");
  sprintf(tmp,"order_%s.dve",name);
  order = fopen (tmp, "w+");
//out=fopen("/dev/tty","w+"); // for debugging purposes

    
    
    
    //map=array[N] describe the ring where each robot is represented by his index
    int map[N], indexes[K];
    for (i = 0; i < N; i++)
        map[i] = 0;
    


    int r,c,j, k;
    int taillem= N -1;
	int essai = (1<<taillem);
	int conf;
	long nb_conf = NB_conf(K, N);//ne sert plus à rien
	
	//on récupère tous les config possibles (même 10..01))
    int *chiffres = malloc(essai * sizeof(*chiffres));
    
    //tab
    conf = config(chiffres, K, N, nb_conf);
    
     
    
   
    if (argc != optind + 3 + K)
        {
        printf ("On fait toutes mes configurations possibles\n");
        //on regarde pour chaque config
        for(c=0; c<conf; c++){
            sprintf(tmp2,"conf.dve");
            confout = fopen ( tmp2, "w+");
            char tab[taillem];
            hachage_binaire(chiffres[c],taillem,tab);
            map[0] = 1;
            indexes[0]=0;
            k = 0;
            r = 1;
            printf("Pour la configuration : ");
            for(j=0; j<taillem;j++){
                if(tab[j] == '1'){
                    map[j+1]= 1;
                    indexes[r]=j+1;
                    r++;
                }
                printf("%d", (int)(tab[j]));
            }
            printf("\n");
            conffile(confout, N, K, map, indexes);
            for (proc = 1; proc <= K; proc++){
                PROC(proc, N, K, indexes[proc-1]);
            }
        }
    
      
    }
  else{
      for (i = 1; i <= K; i++)
      {
          indexes[i - 1] = atoi (argv[optind + 2 + i]);
          map[atoi (argv[optind + 2 + i])] = i;
      }
      sprintf(tmp2,"conf.dve");
      confout = fopen ( tmp2, "w+");
      conffile(confout, N, K, map, indexes);
      for (proc = 1; proc <= K; proc++){
          PROC(proc, N, K, indexes[proc-1]);
      }
  }
    
//    fprintf (order,"#TYPE %s.dve \n",name);
//    //fprintf (order,"chir\nN\nK\nP_Env.state\nP_Env.transient\nP_Env.toplay\nplayer\n");
//    fprintf (order,"N\nK\nP_Env.state\nP_Env.transient\nP_Env.toplay\nplayer\n");
//    //for(i = 1; i <=K ; i++)
//	//fprintf (order,"P_Rbt%d.id\n",i);
//    //for(i = 0; i< N ; i++)
//	//fprintf (order,"map[%d]\n",i);
//    for(i = 0; i< N ; i++)
//        fprintf (order,"nb[%d]\n",i);
//    for(i = 1; i <=K ; i++){
//        fprintf (order,"P_Rbt%d.index\n",i);
//        fprintf (order,"P_Rbt%d.state\n",i);
//    }
//    fprintf (order,"#END\n");
//    
//    fclose (order);
    
    
    
    
    rulesfile(rulesout, N, K, map, indexes);
    
    
    return 0; 
}
    

void conffile(FILE * out, int N, int K, int * map, int * indexes){


/* DECLARATIONS */
    
  fprintf (out, "byte N=%d;\n", N);
  fprintf (out, "byte K=%d;\n", K);
  //fprintf (out, "byte map[%d]={", N);
  //for (i = 0; i < N; i++)
    //{
      //fprintf (out, "%d", map[i]);
      //if (i != N - 1)
	//fprintf (out, ",");
    //}
  //fprintf (out, "};\n");

  fprintf (out, "byte nb[%d]={", N);
  for (i = 0; i < N; i++)
    {
      fprintf (out, "%d", (map[i] == 0 ? 0 : 1));
      if (i != N - 1)
	fprintf (out, ",");
    }
  fprintf (out, "};\n");

  if (option.SYM && !option.FULL)
    {
      fprintf (out, "byte semi[%d]={", K);
      for (i = 0; i < K; i++){
		fprintf (out, "0");
		if (i != K - 1)
			fprintf (out, ",");
	  }
      fprintf (out, "};\n");
    }

  fprintf (out, "byte player=0;\n");
  //fprintf (out, "byte chir=0;\n\n\n");
  fprintf (out, "byte WouldMove=0;\n");
  fprintf (out, "byte Ask=0;\n");
  fprintf (out, "byte hasMover=0;\n");
  
    
/* ENVIRONNEMENT */
 
  fprintf (out, "process P_Env{\n");
  fprintf (out, "byte toplay=0;\n");
  fprintf (out, "byte transient=1;\n");
  fprintf (out, "byte hasElectMover=0;\n");
  fprintf (out, "state step, trans_step");
  if (!option.collision)
    fprintf (out, " ,bad");
  fprintf (out," , FAIL");//les cas ou on a sélectionné personne.....
  fprintf (out, ";\ninit trans_step;\n");
  fprintf (out, "trans\n\n");
  
  fprintf (out, "FAIL->FAIL{},\n\n");
  fprintf (out, "bad->bad{},\n\n");
  
  fprintf (out, "step->trans_step {guard hasMover== 0 || (hasMover == 1 && hasElectMover == 1) ;");
  fprintf (out, "\n effect transient=1, hasMover=0, hasElectMover=0 ;},\n\n");
  fprintf (out, "step->FAIL{guard hasMover==1 && hasElectMover==0;},\n\n");
  fprintf (out, "trans_step->step {guard Ask==0 && player==0 && (toplay %% K)+1 ==1 && transient==0;}");

  if (option.SYM && !option.FULL)
    /*****semi-synchrone*****/
	{
		///////////////////////////////// à faire avec  le nouvel algo ou seul ceux qui peuvent bouger sont selectionnés!!!! 

		fprintf (out,"trans_step ->trans_step {guard player==0 &&  semi[(toplay %% K)]==0 && ((toplay %% K)+1 !=1 || transient==1) ");
		if (!option.collision){
			for (i = 0; i < N; i++){
				fprintf (out, " && nb[%d]<2", i);
			}
		}
		fprintf (out,
	       ";\neffect toplay=(toplay %%K)+1, player=toplay, semi[toplay-1]=1, transient=0;},\n\n");
	       
		fprintf (out,
	       "trans_step ->trans_step {guard player==0 &&  semi[(toplay %% K)]==1 && ((toplay %% K)+1 !=1 || transient==1)");
		if (!option.collision){
		for (i = 0; i < N; i++){
			fprintf (out, " && nb[%d]<2", i);
			}
		}
		fprintf (out,
	       ";\neffect toplay=(toplay %% K )+1, player=toplay, semi[toplay -1]=0, transient=0;},\n\n");

		fprintf (out,
	       "trans_step->trans_step {	guard player==0 &&  semi[(toplay %% K)]==0 && ((toplay %% K)+1 !=1 || transient==1)");
		if (!option.collision){
			for (i = 0; i < N; i++){
				fprintf (out, " && nb[%d]<2", i);
			}
		}
		fprintf (out,
			";\neffect toplay=(toplay %%K)+1, semi[toplay - 1]=2, transient=0;},\n\n");
			
		fprintf (out,
			"trans_step->trans_step {guard player==0 &&  semi[(toplay %% K)]==2 && ((toplay %% K)+1 !=1 || transient==1)");
		if (!option.collision){
			for (i = 0; i < N; i++){
				fprintf (out, " && nb[%d]<2", i);
			}
		}
		fprintf (out, ";\neffect toplay=(toplay %%K)+1, semi[toplay -1]=0, transient=0;}");
		
		

      /*****other*****/   

    }else{
		fprintf (out, ",\n\ntrans_step ->trans_step {guard Ask==1 && player==0 && WouldMove==1 ");
		if (!option.collision){
			for (i = 0; i < N; i++){
				fprintf (out, " && nb[%d]<2", i);
			}
	   	}
		fprintf (out,
			";\neffect Ask=0, player=toplay, hasElectMover=1, transient=0;}");
			
		fprintf (out, ",\n\ntrans_step ->trans_step {guard Ask==0 && player==0 && ((toplay %% K)+1 !=1 || transient==1)");
		if (!option.collision){
			for (i = 0; i < N; i++){
				fprintf (out, " && nb[%d]<2", i);
			}
	   	}
		fprintf (out,
			";\neffect Ask=1, toplay=(toplay %% %d)+1, player=toplay, transient=0;}",K);
			
			

		if (!option.SYM){
			fprintf (out, ",\n\ntrans_step->trans_step {guard Ask==1 && player==0 ");
			if (!option.collision){
				for (i = 0; i < N; i++){
					fprintf (out, " && nb[%d]<2", i);
				}
			}
			fprintf (out, ";\neffect Ask=0, WouldMove=0, transient=0;} ");
			
		}
    }
/********************************************************No Collision*********************************************************/
  if (option.collision)
    fprintf (out, ";\n\n}\n\n\n");
  else
    {
      fprintf (out, ",\n\n");
      fprintf (out, "step->bad {guard player==0 && (");
      for (i = 0; i < N; i++)
	{
	  fprintf (out, " nb[%d] >=2 ", i);
	  if (i != N - 1)
	    fprintf (out, " || ");

	}
	  fprintf (out, ");}");
	  fprintf (out, ",\n\n");
      fprintf (out, "trans_step->bad {guard player==0 && (");
      for (i = 0; i < N; i++)
	{
	  fprintf (out, " nb[%d] >=2 ", i);
	  if (i != N - 1)
	    fprintf (out, " || ");

	}
      fprintf (out, ");};\n\n");
      fprintf (out, "}\n\n\n");
    }
    
    fclose (out);
    return;
}    


/******************************************************************************************************************************/
/* PROCESSES */

void PROC(int proc, int N, int K, int index){
    FILE *out;
    char tmp[32];
    sprintf(tmp,"StartProc%d.dve", proc);
    out = fopen ( tmp, "w+");
    
    fprintf (out, "process P_Rbt%d {\n", proc);
//Cherche l'index du robot proc dans l'anneau
      if (index >= N)
	{
	  fprintf (stderr,
		   " FATAL:Bad Configuration (Index %d of robot %d too big in ring of size %d!) \n ", index,
		   proc, N);
	  exit (0);
	}
      fprintf (out, "byte index=%d; \n", index);
      fprintf (out, "byte id=%d; \n", proc);

      fprintf (out, "state observe, plus, moins, stop; \n");
      fprintf (out, "init observe; \n\n");
      fprintf (out, "trans \n\n");
    
    fclose(out);
    return;
}




void rulesfile(FILE * out, int N, int K, int * map, int * indexes){
	if (FLO)
	{
		printf("bli\n");
		if (pgcd ( K, N) != 1){ 
			printf(" le nombre de robots et la taille de l'anneau doivent etre premiers entre eux! \n");
			exit(0);
		}
		flocchini(K,N,out);
	}
	else if (K == 3 && ALGO_min)
	{
	  algomin(3, N, out, NEW);
	}
    else
	{
	  fprintf (out,
		   "observe->plus {guard player==id && nb[(index+1)%%N]==0;");
	  fprintf (out, "\neffect player=0;");
	  
	  fprintf (out, "},\n\n");

	  fprintf (out,
		   "observe->moins {guard player==id && nb[(index+N-1)%%N]==0;");
	  
      fprintf (out, "\neffect player=0;");
	    
	  fprintf (out, "},\n\n");

	  fprintf (out,
		   "observe->stop {guard player==id && nb[(index+N-1)%%N]!=0 && nb[(index+1)%%N]!=0;");
	  
	      fprintf (out, "\neffect player=0; ");
	    
	  fprintf (out, "} , \n \n \n ");
	}

//compute=> move
	fprintf (out,"plus -> plus {guard Ask==1 && player== id;");
	fprintf (out,"\neffect player=0, WouldMove=1, hasMover=1;},\n\n");
	
	fprintf (out,"moins -> moins {guard Ask==1 && player==id;");
	fprintf (out,"\neffect player=0, WouldMove=1, hasMover=1;},\n\n\n");

    fprintf (out,"plus->observe {guard Ask==0 && player==id; \neffect nb[index]=nb[index]-1,");
    fprintf (out,"\nnb[index+1]=nb[index+1]+1, index=(index+1)%%N, WouldMove=0, player=0;},\n\n");
    
    fprintf (out,"moins->observe {guard Ask==0 && player==id;\neffect nb[index]=nb[index]-1,");
    fprintf (out, "\nnb[(index+N-1)%%N]=nb[(index+N-1)%%N]+1, index=(index+N-1)%%N, WouldMove=0, player=0;};\n\n");
    fprintf (out, "}\n\n\n");
    
    
    
    
    
    //ATTENTION
//en fin de fichier
  //fprintf (out, "system async;\n");


/** CLOSE **/
    fclose(out);
    return; 
}
