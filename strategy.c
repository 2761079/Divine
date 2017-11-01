#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//modification de l'algorithme de base pour que ça marche pour 10
// 0 => faulty version 1=>new version
#define MODIF 1


//toujours vers l'avant
void
robots3 (int r1, int r2, int anneau_size, FILE * out)
{
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+%d)%%N]==1 && nb[(index+%d)%%N]==1;",
	   r1, r2);
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+%d)%%N]==1 && nb[(index+%d)%%N]==1;",
	   anneau_size - r1, anneau_size - r2);
  fprintf (out, "\neffect player=0;},");
  return;
}

void
robots5 (int v1, int v2, int v3, int v4, int v5, int anneau_size, FILE * out)
{
  fprintf (out,
	   "observe -> plus {guard player ==id && nb[(index+%d)%%N]==0 && nb[(index+%d)%%N]==0 && nb[(index+%d)%%N]==0 && nb[(index+%d)%%N]==0 &&nb[(index+%d)%%N]==0;",
	   v1, v2, v3, v4, v5);
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player ==id && nb[(index+%d)%%N]==0 && nb[(index+%d)%%N]==0 && nb[(index+%d)%%N]==0 && nb[(index+%d)%%N]==0 &&nb[(index+%d)%%N]==0;",
	   anneau_size - v1, anneau_size - v2, anneau_size - v3,
	   anneau_size - v4, anneau_size - v5);
  fprintf (out, "\neffect player=0;},");
}

void
strategy_10_3 (FILE *out)
{
  fprintf (out, "// LEGITIMATE PHASE\n\n");


  fprintf (out, "// 1-1-0-0-0-R-Z => ARR\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+6)%%N]==1 && nb[(index+5)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV <=> Z-R-0-0-0-1-1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+4)%%N]==1 && nb[(index+5)%%N]==1;");
 fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n// 1-0-R-0-0-1-Z => ARR\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+8)%%N]==1 && nb[(index+3)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+7)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "\n// R-1-0-0-1-Z => ARR\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+4)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+9)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n\n// CONVERGENCE PHASE\n\n");

  if (MODIF)
    {
      fprintf (out, "//la nouvelle règle\n");
      fprintf (out, "//101 000 000 arriere		\n");
      fprintf (out,
	       "observe -> plus {guard player==id && nb[(index+9)%%N]==1 && nb[(index+7)%%N]==1;");
     fprintf (out, "\neffect player=0;},");
      fprintf (out, "//INV\n");
      fprintf (out,
	       "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+3)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
    }
  else
    {
      fprintf (out, "//l'ancienne\n");
      fprintf (out, "\n// 1-1-0-R-Z => AV\n");
      fprintf (out,
	       "observe -> plus {guard player==id && nb[(index+7)%%N]==1 && nb[(index+8)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
      fprintf (out, "//INV\n");
      fprintf (out,
	       "observe -> moins {guard player==id && nb[(index+2)%%N]==1 && nb[(index+3)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
    }

  fprintf (out, "\n// 1-1-R-Z => AV\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+9)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+2)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "\n// 1-1-Y-R-Z => ARR (Y!=Z!={1,2,3})\n// Impossible avec N<11\n\n");

  fprintf (out, "// 1-X-1-Y-R-Y => ARR\n");
  fprintf (out, "// <=> 1-0-1-0-0-0-R-0-0-0 || 1-0-0-0-1-0-0-R-0-0 || 1-0-0-0-0-0-1-0-R-0\n");	//on peut aller dans les deux sens ...
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+6)%%N]==1 && nb[(index+4)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+4)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "\nobserve -> moins {guard player==id && nb[(index+7)%%N]==1 && nb[(index+3)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+3)%%N]==1 && nb[(index+7)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out,
	   "\nobserve -> moins {guard player==id && nb[(index+8)%%N]==1 && nb[(index+2)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out,
	   "\nobserve-> stop {guard player==id \n&& (nb[(index+6)%%N]!=1 || nb[(index+5)%%N]!=1) \n&& (nb[(index+4)%%N]!=1 || nb[(index+5)%%N]!=1) \n&& (nb[(index+8)%%N]!=1 || nb[(index+3)%%N]!=1) \n&& (nb[(index+2)%%N]!=1 || nb[(index+7)%%N]!=1) \n&& (nb[(index+1)%%N]!=1 || nb[(index+4)%%N]!=1) \n&& (nb[(index+9)%%N]!=1 || nb[(index+6)%%N]!=1) \n");
  if (MODIF)
    {
      fprintf (out,
	       "&& (nb[(index+9)%%N]!=1 || nb[(index+7)%%N]!=1) \n&& (nb[(index+1)%%N]!=1 || nb[(index+3)%%N]!=1) \n");
    }
  else
    {
      fprintf (out,
	       "&& (nb[(index+8)%%N]!=1 || nb[(index+7)%%N]!=1) \n&& (nb[(index+2)%%N]!=1 || nb[(index+3)%%N]!=1) \n");
    }
  fprintf (out,
	   "&& (nb[(index+9)%%N]!=1 || nb[(index+8)%%N]!=1) \n&& (nb[(index+1)%%N]!=1 || nb[(index+2)%%N]!=1) \n&& (nb[(index+6)%%N]!=1 || nb[(index+4)%%N]!=1) \n&& (nb[(index+3)%%N]!=1 || nb[(index+7)%%N]!=1) \n&& (nb[(index+8)%%N]!=1 || nb[(index+2)%%N]!=1);");
  fprintf (out, "\neffect player=0;},");


  /*fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+2)%%N]==1 && nb[(index+3)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+8)%%N]==1 && nb[(index+7)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+2)%%N]==1 && nb[(index+4)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+8)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+4)%%N]==1 && nb[(index+3)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+6)%%N]==1 && nb[(index+7)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+1)%%N]==1 && nb[(index+5)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+9)%%N]==1 && nb[(index+5)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+2)%%N]==1 && nb[(index+5)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+8)%%N]==1 && nb[(index+5)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+5)%%N]==1 && nb[(index+3)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+5)%%N]==1 && nb[(index+7)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+1)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+9)%%N]==1 && nb[(index+4)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+2)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+8)%%N]==1 && nb[(index+4)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+6)%%N]==1 && nb[(index+3)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+4)%%N]==1 && nb[(index+7)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+1)%%N]==1 && nb[(index+7)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+9)%%N]==1 && nb[(index+3)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+1)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  //INV
  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+9)%%N]==1 && nb[(index+2)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out,
	   "observe -> stop {guard player==id \n && nb[(index+9)%%N]==1 && nb[(index+1)%%N]==1;");
  fprintf (out, "\neffect player=0;},");*/
  return;
}











////////////////////////////////////////////////////////////////////
//////////////////////////11_3//////////////////////////////////////
////////////////////////////////////////////////////////////////////
void
strategy_11_3 (FILE *out)
{
  fprintf (out, "// LEGITIMATE PHASE\n\n");
  fprintf (out, "//R000 000 1001\n");
  robots3 (10, 7, 11, out);

  fprintf (out, "\n//R000  110 0000\n");
  robots3 (4, 5, 11, out);

  fprintf (out, "\n//R010 000 0100 \n");
  robots3 (2, 8, 11, out);


  fprintf (out, "\n\n//PHASE DE CONVERGENCE");
  fprintf (out, "//R000 000 0011\n");
  robots3 (9, 10, 11, out);

  if (MODIF)
    {
      fprintf (out, "\n//R000 000 0101\n");
      robots3 (8, 10, 11, out);
    }
  else
    {
      fprintf (out, "\n//R000 000 0110\n");
      robots3 (9, 10, 11, out);
    }

  fprintf (out, "\n//R0000 11 0000\n");
  robots3 (5, 6, 11, out);

  fprintf (out, "\n//R010 000 1000\n");
  robots3 (2, 7, 11, out);

  fprintf (out, "\n//R000 1001 000\n");
  robots3 (4, 7, 11, out);

  fprintf (out, "\n//R001 0000 100\n");
  robots3 (3, 8, 11, out);


  fprintf (out, "\n//R010 0000 010\n");
  robots3 (2, 9, 11, out);



  fprintf (out, "\n\nobserve-> stop {guard player==id ");
//  1100000000 
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+2)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+9)%%N]!=1 || nb[(index+10)%%N]!=1)");
  if (MODIF)
    {
//1010000000
      fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+3)%%N]!=1) ");
      fprintf (out, "\n&& (nb[(index+8)%%N]!=1 || nb[(index+10)%%N]!=1) ");
    }
  else
    {
//0110000000 
      fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+3)%%N]!=1) ");
      fprintf (out, "\n&& (nb[(index+8)%%N]!=1 || nb[(index+9)%%N]!=1) ");
    }
//1001000000 legitime
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+4)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+10)%%N]!=1 || nb[(index+7)%%N]!=1)");
//0001100000                                                                          legitime
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+5)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+7)%%N]!=1 || nb[(index+6)%%N]!=1) ");
//0000110000 avant ou arriere
  fprintf (out, "\n&& (nb[(index+5)%%N]!=1 || nb[(index+6)%%N]!=1) ");
//0100001000 
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+7)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+9)%%N]!=1) ");
//0001001000 avant ou arriere
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+7)%%N]!=1) ");
//0100000100  legitime
  fprintf (out, "\n&& (nb[(index+8)%%N]!=1 || nb[(index+2)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+9)%%N]!=1) ");
//0010000100 avant ou arriere 
  fprintf (out, "\n&& (nb[(index+8)%%N]!=1 || nb[(index+3)%%N]!=1) ");
//0100000010 avant ou arriere
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+9)%%N]!=1) ;");
  fprintf (out, "\neffect player=0;},");

  return;
}












////////////////////////////////////////////////////////////////////
//////////////////////////13_3//////////////////////////////////////
////////////////////////////////////////////////////////////////////
void
strategy_13_3 (FILE *out)
{
  fprintf (out, "// LEGITIMATE PHASE\n\n");

  fprintf (out, "//R 000 000 001 001\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+9)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+4)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R000  110 000 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+4)%%N]==1 && nb[(index+5)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+8)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R010 000 000 100 \n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
//////////////////////////////////////////////////////
  fprintf (out, "\n\n//PHASE DE CONVERGENCE");

//1
  fprintf (out, "//R000 000 000 011\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+11)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+2)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  if (MODIF)
    {
//2
      fprintf (out, "\n//R000 000 000 101\n");
      fprintf (out,
	       "observe -> plus {guard player==id && nb[(index+10)%%N]==1 && nb[(index+12)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
      fprintf (out, "//INV\n");
      fprintf (out,
	       "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+3)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
    }
  else
    {
//2
      fprintf (out, "\n//R000 000 000 110\n");
      fprintf (out,
	       "observe -> plus {guard player==id && nb[(index+10)%%N]==1 && nb[(index+11)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
      fprintf (out, "//INV\n");
      fprintf (out,
	       "observe -> moins {guard player==id && nb[(index+2)%%N]==1 && nb[(index+3)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
    }


  fprintf (out, "\n//R000 011 000 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+5)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+7)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//5
  fprintf (out, "\n//R00000 11 00000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+7)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+7)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//6
  fprintf (out, "\n//R010 000 010 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+5)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//7
  fprintf (out, "\n//R0000 1001 0000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+5)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+5)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//6
  fprintf (out, "\n//R010 000 001 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+4)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R001 000 001 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+3)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+4)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//9
  fprintf (out, "\n//R000 100 001 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+4)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+4)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//9
  fprintf (out, "\n//R001 000 000 100\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+3)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//10
  fprintf (out, "\n//R010 000 000 010\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n\nobserve-> stop {guard player==id ");
//110000000000
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+2)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+11)%%N]!=1 || nb[(index+12)%%N]!=1)");
  if (MODIF)
    {
//101000000000 
      fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+3)%%N]!=1) ");
      fprintf (out, "\n&& (nb[(index+10)%%N]!=1 || nb[(index+12)%%N]!=1) ");
    }
  else
    {
//011000000000 
      fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+3)%%N]!=1) ");
      fprintf (out, "\n&& (nb[(index+10)%%N]!=1 || nb[(index+11)%%N]!=1) ");
    }
//1001 000 000 00      legitime
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+4)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+12)%%N]!=1 || nb[(index+9)%%N]!=1)");
//0001 100 000 00      legitime
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+5)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+9)%%N]!=1 || nb[(index+8)%%N]!=1) ");
//000011000000
  fprintf (out, "\n&& (nb[(index+6)%%N]!=1 || nb[(index+5)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+7)%%N]!=1 || nb[(index+8)%%N]!=1) ");
//000001100000 avant ou arriere
  fprintf (out, "\n&& (nb[(index+7)%%N]!=1 || nb[(index+6)%%N]!=1) ");
//010000010000 
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+8)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+5)%%N]!=1 || nb[(index+11)%%N]!=1) ");
//000010010000 avant ou arriere
  fprintf (out, "\n&& (nb[(index+5)%%N]!=1 || nb[(index+8)%%N]!=1) ");
//010000001000 avant
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+9)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+11)%%N]!=1) ");
//000100001000 avant ou arriere 
  fprintf (out, "\n&& (nb[(index+9)%%N]!=1 || nb[(index+4)%%N]!=1) ");
//010000000100         legitime
  fprintf (out, "\n&& (nb[(index+10)%%N]!=1 || nb[(index+2)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+11)%%N]!=1) ");
//001000000100 avant ou arriere 
  fprintf (out, "\n&& (nb[(index+10)%%N]!=1 || nb[(index+3)%%N]!=1) ");
//010000000010 avant ou arriere
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+11)%%N]!=1) ;");
  fprintf (out, "\neffect player=0;},");

  return;
}



////////////////////////////////////////////////////////////////////
//////////////////////////14_3//////////////////////////////////////
////////////////////////////////////////////////////////////////////
void
strategy_14_3 (FILE *out)
{
	fprintf (out, "// LEGITIMATE PHASE\n\n");

  fprintf (out, "//R 000 000 000 1001\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+10)%%N]==1 && nb[(index+13)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+4)%%N]==1;");
  fprintf (out, "\neffect player=0;},");



  fprintf (out, "\n//R000  110 000 0000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+4)%%N]==1 && nb[(index+5)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+9)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R010 000 000 0100 \n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

//////////////////////////////////////////////////////
  fprintf (out, "\n\n//PHASE DE CONVERGENCE");

//1
  fprintf (out, "//R000 000 000 0011\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+13)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+2)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


  if (MODIF)
    {
      fprintf (out, "\n//R000 000 000 0101\n");
      fprintf (out,
	       "observe -> plus {guard player==id && nb[(index+13)%%N]==1 && nb[(index+11)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
      fprintf (out, "//INV\n");
      fprintf (out,
	       "observe -> moins {guard player==id && nb[(index+1)%%N]==1 && nb[(index+3)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
    }
  else
    {
//2
      fprintf (out, "\n//R000 000 000 0110\n");
      fprintf (out,
	       "observe -> plus {guard player==id && nb[(index+12)%%N]==1 && nb[(index+11)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
      fprintf (out, "//INV\n");
      fprintf (out,
	       "observe -> moins {guard player==id && nb[(index+2)%%N]==1 && nb[(index+3)%%N]==1;");
      fprintf (out, "\neffect player=0;},");
    }


//5
  fprintf (out, "\n//R000 011 000 0000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+5)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+9)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//6
  fprintf (out, "\n//R000 001 100 0000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+7)%%N]==1 && nb[(index+6)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+7)%%N]==1 && nb[(index+8)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

//8
  fprintf (out, "\n//R000 001 0 100 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+6)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+6)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

//9
  fprintf (out, "\n//R010 000 001 0000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+5)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//10
  fprintf (out, "\n//R001 000 001 0000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+3)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+5)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//11
  fprintf (out, "\n//R000 010 0 010 000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+5)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+5)%%N]==1 && nb[(index+9)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//12
  fprintf (out, "\n//R010 000 000 1000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+4)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//13
  fprintf (out, "\n//R001 000 000 1000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+3)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+4)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//14
  fprintf (out, "\n//R0001 00 0 00 1000\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+4)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+4)%%N]==1 && nb[(index+10)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//15
  fprintf (out, "//R010 000 000 0100\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//16
  fprintf (out, "\n//R001 000 0 000 100\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+3)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==1 && nb[(index+11)%%N]==1;");
  fprintf (out, "\neffect player=0;},");


//17
  fprintf (out, "\n//R010 000 0 000 010\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+2)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==1 && nb[(index+12)%%N]==1;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n\nobserve-> stop {guard player==id ");

//1100000000000
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+2)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+13)%%N]!=1 || nb[(index+12)%%N]!=1)");
  if (MODIF)
    {
      //1010000000000
      fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+3)%%N]!=1) ");
      fprintf (out, "\n&& (nb[(index+13)%%N]!=1 || nb[(index+11)%%N]!=1) ");
    }
  else
    {
      //0110000000000
      fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+3)%%N]!=1) ");
      fprintf (out, "\n&& (nb[(index+12)%%N]!=1 || nb[(index+11)%%N]!=1) ");
    }
//1001 000 000 000                     legitime
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+4)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+13)%%N]!=1 || nb[(index+10)%%N]!=1)");
//0001 100 000 000                     legitime
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+5)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+9)%%N]!=1 || nb[(index+10)%%N]!=1) ");
//0000110000000
  fprintf (out, "\n&& (nb[(index+6)%%N]!=1 || nb[(index+5)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+9)%%N]!=1 || nb[(index+8)%%N]!=1) ");
//0000011000000 
  fprintf (out, "\n&& (nb[(index+7)%%N]!=1 || nb[(index+6)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+7)%%N]!=1 || nb[(index+8)%%N]!=1) ");



//0000010100000 avant ou arriere
  fprintf (out, "\n&& (nb[(index+6)%%N]!=1 || nb[(index+8)%%N]!=1) ");
//0100000010000 avant
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+9)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+5)%%N]!=1 || nb[(index+12)%%N]!=1) ");
//0010000010000 avant
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+8)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+5)%%N]!=1 || nb[(index+11)%%N]!=1) ");
//0000100010000 avant ou arriere 
  fprintf (out, "\n&& (nb[(index+9)%%N]!=1 || nb[(index+5)%%N]!=1) ");
//0100000001000 avant
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+10)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+12)%%N]!=1) ");
//0010000001000 avant
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+9)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+11)%%N]!=1) ");
//0100000000100             legitime
  fprintf (out, "\n&& (nb[(index+11)%%N]!=1 || nb[(index+2)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+12)%%N]!=1) ");
//0010000000100 avant ou arriere 
  fprintf (out, "\n&& (nb[(index+11)%%N]!=1 || nb[(index+3)%%N]!=1) ");
//0100000000010 avant ou arriere
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+12)%%N]!=1) ;");
  fprintf (out, "\neffect player=0;},");

  return;
}











////////////////////////////////////////////////////////////////////
//////////////////////////16_3//////////////////////////////////////
////////////////////////////////////////////////////////////////////
void
strategy_16_3 (FILE *out)
{
	fprintf (out, "// LEGITIMATE PHASE\n\n");
  fprintf (out, "//R1001 0000 000 0000 \n");
  robots3 (12, 15, 16, out);

  fprintf (out, "\n//R000  1100 0000 0000 \n");
  robots3 (4, 5, 16, out);

  fprintf (out, "\n//R0100 0000 000 0100 \n");
  robots3 (2, 13, 16, out);


//////////////////////////////////////////////////////
  fprintf (out, "//PHASE DE CONVERGENCE");

//1
  fprintf (out, "//R0000 0000 000 0011\n");
  robots3 (14, 15, 16, out);

//2
  fprintf (out, "\n//R101000000000000 arriere\n");
  robots3 (13, 15, 16, out);

//5
  fprintf (out, "\n//R000011000000000\n");
  robots3 (6, 5, 16, out);

//6
  fprintf (out, "\n//R000001100000000\n");
  robots3 (6, 7, 16, out);

//7
  fprintf (out, "\n//R000000110000000\n");
  robots3 (8, 7, 16, out);

//8
  fprintf (out, "\n//000000101000000\n");
  robots3 (9, 7, 16, out);

//9
  fprintf (out, "\n//R010000000100000\n");
  robots3 (2, 10, 16, out);

//10
  fprintf (out, "\n//R001000000100000\n");
  robots3 (3, 10, 16, out);

//11
  fprintf (out, "\n//R000001000100000\n");
  robots3 (6, 10, 16, out);

//12 
  fprintf (out, "\n//R010000000010000\n");
  robots3 (2, 11, 16, out);

//13
  fprintf (out, "//R001000000010000 \n");
  robots3 (3, 11, 16, out);

//14
  fprintf (out, "//R000100000010000\n");
  robots3 (4, 11, 16, out);

//15
  fprintf (out, "//R000010000010000\n");
  robots3 (5, 11, 16, out);

//16
  fprintf (out, "//R010000000001000\n");
  robots3 (2, 12, 16, out);

//17
  fprintf (out, "//R001000000001000\n");
  robots3 (3, 12, 16, out);

//18
  fprintf (out, "//R000100000001000\n");
  robots3 (4, 12, 16, out);

//20
  fprintf (out, "//R001000000000100\n");
  robots3 (3, 13, 16, out);

//21
  fprintf (out, "//R010000000000010\n");
  robots3 (2, 14, 16, out);





  fprintf (out, "\n\nobserve-> stop {guard player==id ");

// legitime 3
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+4)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+15)%%N]!=1 || nb[(index+12)%%N]!=1)");
// legitime 4
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+5)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+12)%%N]!=1 || nb[(index+11)%%N]!=1) ");
// legitime 19
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+13)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+14)%%N]!=1 || nb[(index+3)%%N]!=1)");
//1
  fprintf (out, "\n&& (nb[(index+14)%%N]!=1 || nb[(index+15)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+2)%%N]!=1) ");
//2
  fprintf (out, "\n&& (nb[(index+13)%%N]!=1 || nb[(index+15)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+1)%%N]!=1 || nb[(index+3)%%N]!=1) ");
//5
  fprintf (out, "\n&& (nb[(index+5)%%N]!=1 || nb[(index+6)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+11)%%N]!=1 || nb[(index+10)%%N]!=1) ");
//6
  fprintf (out, "\n&& (nb[(index+6)%%N]!=1 || nb[(index+7)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+10)%%N]!=1 || nb[(index+9)%%N]!=1) ");
//7
  fprintf (out, "\n&& (nb[(index+8)%%N]!=1 || nb[(index+7)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+8)%%N]!=1 || nb[(index+9)%%N]!=1) ");
//8
  fprintf (out, "\n&& (nb[(index+9)%%N]!=1 || nb[(index+7)%%N]!=1) ");
//9
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+10)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+14)%%N]!=1 || nb[(index+6)%%N]!=1) ");
//10
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+10)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+13)%%N]!=1 || nb[(index+6)%%N]!=1) ");
//11
  fprintf (out, "\n&& (nb[(index+6)%%N]!=1 || nb[(index+10)%%N]!=1) ");
//12
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+11)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+14)%%N]!=1 || nb[(index+5)%%N]!=1) ");
//13
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+11)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+13)%%N]!=1 || nb[(index+5)%%N]!=1) ");
//14
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+11)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+12)%%N]!=1 || nb[(index+5)%%N]!=1) ");
//15
  fprintf (out, "\n&& (nb[(index+5)%%N]!=1 || nb[(index+11)%%N]!=1) ");
//16
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+12)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+14)%%N]!=1) ");
//17
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+12)%%N]!=1) ");
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+13)%%N]!=1) ");
//18
  fprintf (out, "\n&& (nb[(index+4)%%N]!=1 || nb[(index+12)%%N]!=1) ");
//20
  fprintf (out, "\n&& (nb[(index+3)%%N]!=1 || nb[(index+13)%%N]!=1) ");
//21
  fprintf (out, "\n&& (nb[(index+2)%%N]!=1 || nb[(index+14)%%N]!=1) ;");
  fprintf (out, "\neffect player=0;},");

  return;
}







///////////////////////////////////////////////////////////////////////////






void
strategy_12_5 (FILE *out)
{
//printf("coucou \n");
  fprintf (out, "// LEGITIMATE PHASE\n\n");
  fprintf (out, "//R000 110 011 11 \n");	//avant
  fprintf (out,
	   "observe -> plus {guard player ==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+7)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player ==id && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+9)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R001 100 111 10\n");
  fprintf (out,
	   "observe -> plus {guard player ==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 001 111 00\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player ==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R001 111 000 11\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+9)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player ==id && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R011 110 001 10\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
////////////////////
  fprintf (out, "\n\n// CONVERGENCE PHASE\n\n");
  fprintf (out, "//F5\n");

  fprintf (out, "//R111 111 000 00 arriere C1_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 &&nb[(index+5)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

///////////////////////////////////////F4////////////////////////////////
  fprintf (out, "\n\n//F4\n");


  fprintf (out, "//R000 010 111 11 \t C2_43\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 &&nb[(index+6)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 110 000 11 \t C2_41\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+9)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 111 000 01 \t C2_42\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


///////////////////////////////////////F3////////////////////////////////
  fprintf (out, "\n\n//F3\n");

  fprintf (out, "//R001 111 100 01 \t C3_31 avec Ry=0\n ");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R010 001 011 11 \t C3_32\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 &&nb[(index+7)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+5)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 101 110 00 \t C3_31 avec x=3 y=3 et z=1 \n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+9)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 011 110 00 \t C3_31 avec x=4 y=2 et z=1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+9)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R001 000 111 11 \t C2_32\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 &&nb[(index+6)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "//R010 001 111 10 \t C3_34\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 000 110 11 \t C3_32\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+9)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 000 111 01 \t C3_35 \n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 100 011 10 \t C3_33\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R010 111 100 01 \t C3_31\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

/////////////////////////////////////////F2/////////////////////////////
  fprintf (out, "\n\n//F2\n");


  fprintf (out, "//R011 111 001 00 \t C3_21\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+5)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R001 010 011 11 \t C3_22\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+7)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R001 010 101 11 \t C4_3 avec x=1 y=1 w=4\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+8)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 110 101 00 \t C4_2\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 101 101 00 \t C4_2\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R001 100 111 10 \t C3_21\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R011 101 011 00 \t C4_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R001 101 100 11 \t C3_22\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+9)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 011 011 00 \t C4_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R010 111 011 00\t C4_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

////mid////

  fprintf (out, "//R011 100 111 00 \t C3_21\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 010 111 00 \t C4_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, " \n//R001 110 111 00 \t C3_23\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R011 011 100 10 \t C4_4\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+8)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R010 110 011 10 \t C4_4\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out, "observe -> moins {guard player==id &&");
  fprintf (out,
	   " nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 010 110 01 \t C4_2\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 100 110 01 \t C3_21\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 110 010 01 \t C3_21\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+6)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R010 101 111 00 \t C4_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R010 110 111 00 \t C4_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R010 101 110 01 \t C4_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R001 101 101 01\t C4_3\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+2)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+10)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+2)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+10)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
//////////////////////////////////////////F1/////////////////////////////
  fprintf (out, "\n\n//F1\n");


  fprintf (out, "//R010 101 011 10 \t C5_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+7)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");


  fprintf (out, "\n//R011 011 010 10 \t C5_1\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+7)%%N]==0 && nb[(index+9)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+3)%%N]==0 && nb[(index+5)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");

  fprintf (out, "\n//R011 010 101 10 \t C5_5\n");
  fprintf (out,
	   "observe -> plus {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out, "//INV\n");
  fprintf (out,
	   "observe -> moins {guard player==id && nb[(index+1)%%N]==0 && nb[(index+4)%%N]==0 && nb[(index+6)%%N]==0 && nb[(index+8)%%N]==0 &&nb[(index+11)%%N]==0;");
  fprintf (out, "\neffect player=0;},");
  fprintf (out,
	   "\n\nobserve-> stop {guard player==id \n/*F5*/\n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 )\n && (nb[(index+11)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+7)%%N]!=0 )\n");

  fprintf (out,
	   "/*F4*/ \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+6)%%N]!=0 )\n && (nb[(index+6)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 )\n && (nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+1)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0 )\n");

  fprintf (out,
	   "/*F3*/ \n && (nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0 ) \n && (nb[(index+5)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+1)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+7)%%N]!=0 ) \n && (nb[(index+5)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+1)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+7)%%N]!=0 ) \n ");
  fprintf (out,
	   "&& (nb[(index+1)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+6)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+6)%%N]!=0 ) \n");
  fprintf (out,
	   " && (nb[(index+1)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+1)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+3)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+9)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+1)%%N]!=0 ) \n && (nb[(index+2)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+1)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+10)%%N]!=0 )   /*sym*/ \n && (nb[(index+1)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n && (nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0 )     \n && (nb[(index+1)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0 ) \n");

  fprintf (out,
	   "/*F2*/  \n && (nb[(index+1)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+8)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+5)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+6)%%N]!=0 ||nb[(index+7)%%N]!=0) \n && (nb[(index+5)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+8)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+6)%%N]!=0 ||nb[(index+8)%%N]!=0) \n && (nb[(index+4)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+8)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n");
  fprintf (out,
	   " && (nb[(index+1)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+8)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+6)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+8)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+6)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n");
  fprintf (out,
	   " && (nb[(index+1)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0) \n && (nb[(index+3)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0) \n");
  fprintf (out,
	   " && (nb[(index+1)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0) \n");
  fprintf (out,
	   " && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+8)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0) \n");
  fprintf (out,
	   "&& (nb[(index+2)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0) \n && (nb[(index+2)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0) \n && (nb[(index+2)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+6)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n");
  fprintf (out,
	   " && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+6)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+10)%%N]!=0) \n && (nb[(index+2)%%N]!=0 || nb[(index+3)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0) \n && (nb[(index+1)%%N]!=0 || nb[(index+2)%%N]!=0 || nb[(index+5)%%N]!=0 || nb[(index+8)%%N]!=0 ||nb[(index+10)%%N]!=0) \n && (nb[(index+2)%%N]!=0 || nb[(index+4)%%N]!=0 || nb[(index+7)%%N]!=0 || nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0) \n");

  fprintf (out,
	   "/*F1*/ \n && (nb[(index+1)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n");

  fprintf (out,
	   "/*conf_legitimes*/ \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+3)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+7)%%N]!=0 ) \n && (nb[(index+11)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+9)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+5)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+2)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+9)%%N]!=0 )\n && (nb[(index+3)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+10)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+7)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+8)%%N]!=0 ||nb[(index+11)%%N]!=0 ) \n && (nb[(index+1)%%N]!=0 ||nb[(index+4)%%N]!=0 ||nb[(index+6)%%N]!=0 ||nb[(index+5)%%N]!=0 ||nb[(index+11)%%N]!=0 )\n");

  fprintf (out, "&& (nb[(index+1)%%N]!=0 || nb[(index+11)%%N]!=0);");
  fprintf (out, "\neffect player=0;},");

  return;
}
