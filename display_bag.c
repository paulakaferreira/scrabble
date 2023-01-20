#include <stdio.h>
#define TOTAL_JETON 102

char tabjeton[TOTAL_JETON];


void affichage_sac ()
{
  int i, cpt = 0;
  for (i = 0; i < TOTAL_JETON; i++)
    {
      if (tabjeton[i] != '\0')
	{
	  cpt++;
	}
    }
  printf ("\n");
  printf ("Il reste %d lettres dans le sac de lettres.\n", cpt);

}
