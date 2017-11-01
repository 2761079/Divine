#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//gen_ltl N K file

int main (int argc, char **argv){
	if(argc != 4)
		printf("ERREUR");
	FILE *out = fopen (strdup (strcat (argv[3], ".ltl")), "w+");
	int K = atoi(argv[2]);
	
	int i;
	fprintf(out,"#define env (P_Env.step || P_Env.trans_step)\n\n");
    fprintf(out,"#define fin (P_Env.step_fin || P_Env.trans_fin)\n\n");
	for (i = 1 ; i <= K ; i++){
		fprintf(out,"#define p1_%d (P_Rbt%d.observe)\n",i,i);
		fprintf(out,"#define p2_%d (P_Rbt%d.plus || P_Rbt%d.moins || P_Rbt%d.stop) \n",i, i, i, i);
		fprintf(out,"#define p%d (P_Rbt%d.observe || P_Rbt%d.stop) \n\n",i,i,i);
	}
	fprintf(out, "\n");
	
	fprintf(out, "#define FINAL !(G( env || fin )");
	//fprintf(out, "&& (G (");
	//for (i = 1 ; i < K ; i++)
	//	fprintf(out, "(F p1_%d) && (F p2_%d) && ",i,i);
	//fprintf(out, "(F p1_%d) && (F p2_%d) )",K,K);
	
	//fprintf(out,")");/*
	
	fprintf(out," -> ");
	fprintf(out," (F (G (");
	for (i = 1 ; i < K ; i++)
		fprintf(out, "p%d && ",i);
	fprintf(out, "p%d && fin)) ) && !G(P_Env.bad) )",K);
	
	fprintf(out, "\n\n FINAL ");

	
}
