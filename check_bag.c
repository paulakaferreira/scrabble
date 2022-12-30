/* Cette fonction permet de compter le nombre de lettres dans le sac de lettres
et renvoie cpt_lettre = nombre de lettre dans le sac de lettres, et met à 1 un booléen sac_vide.
Elle sera utilisée
au début de la procédure d'échange (si nb_lettre<7 alors échange impossible)
et lors de la procédure de tirage pour vérifier que le sac n'est pas vide */

#incluse <stdio.h>
#define TOTAL_JETON 102

int verification_sac ()
{
  int i, cpt_lettre = 0;
  
  for (i = 0; i < TOTAL_JETON; i++)
  {
      if (tabjeton[i] != '\0')
	   {
	    cpt_lettre++;
  	 }
   }
  
  if(cpt_lettre==0)
  {
    sac_vide=1;
  }
  
  return cpt_lettre;

}
