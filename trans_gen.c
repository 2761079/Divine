#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h> //pour le isprint de getopt
#include "strategy.h"
#include "flocchini/algo.h"

//collision=0 on n'en veut pas !!!
//#define collision 0
//SYm 0=>CORDA 1=>SYm
//#define SYM 1
// Si SYm = 1      1 => Fully  0=>Semi
//#define FULL 0

//ALGO_10_3=1 si on veut utiliser l'algorithme de "Exclusive Perpetual Ring Exploration without Chirality"
#define ALGO_10_3 1
#define ALGO_11_3 1
#define ALGO_13_3 1
#define ALGO_14_3 1
#define ALGO_16_3 1
#define ALGO_12_5 1
#define FLO 1


int N, K, Obs, i, proc;
char *name;
FILE *out;
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
printf("blablabalbkeflj\n");
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
//map=array[N] describe the ring where each robot is represented by his index
  int map[N], indexes[K];
  for (i = 0; i < N; i++)
    map[i] = 0;
  for (i = 1; i <= K; i++)
    {
      indexes[i - 1] = atoi (argv[optind + 2 + i]);
      map[atoi (argv[optind + 2 + i])] = i;
    }

  name = strdup (argv[optind + 2]);
  char tmp[32];
  int r = sprintf(tmp,"%s.dve",name);
  out = fopen ( tmp, "w+");
  r = sprintf(tmp,"order_%s.dve",name);
  order = fopen (tmp, "w+");
//out=fopen("/dev/tty","w+"); // for debugging purposes

  if (argc != optind + 3 + K)
    {
      printf ("FATAL : Bad Configuration (Bad number of robots !)\n");
      exit (1);
    }



/* DECLARATIONS */
  fprintf (order,"#TYPE %s.dve \n",name);
  //fprintf (order,"chir\nN\nK\nP_Env.state\nP_Env.transient\nP_Env.toplay\nplayer\n");
  fprintf (order,"N\nK\nP_Env.state\nP_Env.transient\nP_Env.toplay\nplayer\n");
  //for(i = 1; i <=K ; i++)
	//fprintf (order,"P_Rbt%d.id\n",i); 
  //for(i = 0; i< N ; i++)
	//fprintf (order,"map[%d]\n",i);
  for(i = 0; i< N ; i++)
	fprintf (order,"nb[%d]\n",i);
  for(i = 1; i <=K ; i++){
	fprintf (order,"P_Rbt%d.index\n",i);
	fprintf (order,"P_Rbt%d.state\n",i); 
  }
  fprintf (order,"#END\n");


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

/* ENVIRONNEMENT */

  fprintf (out, "process P_Env{\n");
  fprintf (out, "byte toplay=0;\n");
  fprintf (out, "byte transient=1;\n");
  fprintf (out, "state step, trans_step");
  if (!option.collision)
    fprintf (out, ",bad");
  fprintf (out, ";\ninit trans_step;\n");
  fprintf (out, "trans\n\n");
  
  fprintf (out, "step->trans_step {effect transient=1;},\n\n");
  fprintf (out, "trans_step->step {guard (toplay %% K)+1 ==1 && transient==0;}");

  if (option.SYM && !option.FULL)
    /*****///semi-synchrone///*****/
	{

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
		
		

      /*****///other///*****/   

    }else{
		fprintf (out, ",\n\ntrans_step ->trans_step {guard player==0 && ((toplay %% K)+1 !=1 || transient==1)");
		if (!option.collision){
			for (i = 0; i < N; i++){
				fprintf (out, " && nb[%d]<2", i);
			}
	   	}
		fprintf (out,
			";\neffect toplay=(toplay %% %d)+1, player=toplay, transient=0;}",K);

		if (!option.SYM){
			fprintf (out, ",\n\ntrans_step->trans_step {guard player==0 && ((toplay %% K)+1 !=1 || transient==1)");
			if (!option.collision){
				for (i = 0; i < N; i++){
					fprintf (out, " && nb[%d]<2", i);
				}
			}
			fprintf (out, ";\neffect toplay=(toplay %% K)+1, transient=0;} ");
			
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


/******************************************************************************************************************************/
/* PROCESSES */

  for (proc = 1; proc <= K; proc++)
    {

      fprintf (out, "process P_Rbt%d {\n", proc);
      int i = 0;
//Cherche l'index du robot proc dans l'anneau
      i = indexes[proc - 1];
      if (i >= N)
	{
	  fprintf (stderr,
		   " FATAL:Bad Configuration (Index of robot %d too big !) \n ",
		   proc);
	  exit (0);
	}
      fprintf (out, "byte index=%d; \n", i);
      //fprintf (out, "byte id=%d; \n", proc);

      fprintf (out, "state observe, plus, moins, stop; \n");
      fprintf (out, "init observe; \n\n");
      fprintf (out, "trans \n\n");
	if (FLO)
	{
		if (pgcd ( K, N) != 1){ 
			printf(" le nombre de robots et la taille de l'anneau doivent etre premiers entre eux! \n");
			return 1;
		}
		flocchini(K,N,out,proc);
	}
	else if (K == 3 && N == 10 && ALGO_10_3)
	{
	  strategy_10_3 (out);
	}
     else if (K == 7 && N == 12 && ALGO_12_5)
	{
	  strategy_12_5 (out);
	}
      else if (K == 3 && N == 11 && ALGO_11_3)
	{

	  strategy_11_3 (out);
	}
      else if (K == 3 && N == 13 && ALGO_13_3)
	{
	  strategy_13_3 (out);
	}
      else if (K == 3 && N == 14 && ALGO_14_3)
	{
	  fprintf (stderr, "!!!!!!!!!!!!!!\n");
	  strategy_14_3 (out);
	}
     /* else if (K == 3 && N == 16 && ALGO_16_3)
	{
	  fprintf (stderr, "!!!!!!!!!!!!!!\n");
	  strategy_16_3 (out);
	}*/
      else
	{
	  //fprintf (out,
		   //"observe->plus {guard player==id && ((chir==0 && nb[(index+1)%%N]==0)	|| (chir==1 && nb[(index+1)%%N]==0));");
	  //fprintf (out, "\neffect player=0;");
	  
	  //fprintf (out, "},\n\n");

	  //fprintf (out,
		   //"observe->moins {guard player==id && ((chir==1 && nb[(index+N-1)%%N]==0)|| (chir==0 && nb[(index+N-1)%%N]==0));");
	  
	      //fprintf (out, "\neffect player=0;");
	    
	  //fprintf (out, "},\n\n");
	  
	  fprintf (out,
		   "observe->plus {guard player==%d && nb[(index+1)%%N]==0;",proc);
	  fprintf (out, "\neffect player=0;");
	  
	  fprintf (out, "},\n\n");

	  fprintf (out,
		   "observe->moins {guard player==%d && nb[(index+N-1)%%N]==0;",proc);
	  
	      fprintf (out, "\neffect player=0;");
	    
	  fprintf (out, "},\n\n");

	  fprintf (out,
		   "observe->stop {guard player==%d && nb[(index+N-1)%%N]!=0 && nb[(index+1)%%N]!=0;",proc);
	  
	      fprintf (out, "\neffect player=0; ");
	    
	  fprintf (out, "} , \n \n \n ");
	}
//compute=> move
      fprintf (out,
	       "plus->observe {guard player==%d; \neffect nb[index]=nb[index]-1, \nnb[index+1]=nb[index+1]+1, index=(index+1)%%N, player=0;},\n\n",proc);
      fprintf (out,
	       "moins->observe {guard player==%d;\neffect nb[index]=nb[index]-1, \nnb[(index+N-1)%%N]=nb[(index+N-1)%%N]+1, index=(index+N-1)%%N, player=0;},\n\n",proc);
      fprintf (out, "stop->observe {guard player==%d;\neffect player=0;};\n",proc);
      fprintf (out, "}\n\n\n");
    }

  fprintf (out, "system async;\n");


/** CLOSE **/

  fclose (order);
  fclose (out);
	printf("fini");
  return 0;
}
