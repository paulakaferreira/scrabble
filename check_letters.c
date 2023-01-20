#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_JETON_TOUR 7
#define MAX_JOUEUR 2

struct type_joueur
{
  int id_joueur;
  int score;
  char jeton[MAX_JETON_TOUR];
};

struct type_joueur tabjoueur[MAX_JOUEUR];
char chaine_lettres_lues[MAX_JETON_TOUR];

int verif_lettres(int choix_joueur)
{
	int lettre='v';
	int i;
	int j=0;
	int trouve=0;
	int cpt=0; // compteur pour vérifier que l'utilisateur n'a pas entré plus de 7 lettres
	char tab_jeton_tempo[MAX_JETON_TOUR]; // Variable locale représentant le nombre de jetons du joueur.

	
	// initialisation de la chaîne chaine_lettres_lues
	for(i=0; i<MAX_JETON_TOUR; i++)
	{
		chaine_lettres_lues[i]='\0';
	}
	
	i=0;
	
  if((lettre=getchar())!='\n')
   {
      lettre=toupper(lettre);
      chaine_lettres_lues[i]=lettre;
      i++;
    	cpt++;
    	while ((lettre=getchar())  != '\n')
    	{
    		if(lettre!=' ')
    		{
    			lettre=toupper(lettre);
    			chaine_lettres_lues[i]=lettre;
    			i++;
		    	cpt++;
    		}
    	}
    }
    
    else
    {
    while ((lettre=getchar())  != '\n')
    	{
    		if(lettre!=' ')
    		{
    			lettre=toupper(lettre);
    			chaine_lettres_lues[i]=lettre;
    			i++;
			    cpt++;
    		 }
    	}
    }
    
    if(cpt>MAX_JETON_TOUR)
    {
    	printf("Erreur : vous avez entré un nombre de lettres supérieur aux jetons que vous possédez.\n");
	    return(trouve);
    }
    
    else
    {
	
    	strcpy(tab_jeton_tempo, tabjoueur[choix_joueur].jeton);
    	for(i=0; chaine_lettres_lues[i]!='\0'; i++)
	    {
	    	if(chaine_lettres_lues[i]!='\0')
	    	{
		    	trouve=0;
          // à chaque lettre qu'on commence à vérifier, on remet trouve à 0
	    	}
	    	for(j=0; j<MAX_JETON_TOUR; j++)
		    {
		    	if(tab_jeton_tempo[j]==chaine_lettres_lues[i])
			    	{
				    	trouve=1;
					    tab_jeton_tempo[j]='\0'; // Suprression de la lettre du joueur dans tab_jeton_tempo pour éviter qu'elle soit relue par la suite
				    	j=MAX_JETON_TOUR; // sortie de la boucle car la lettre est trouvée
		    		}
	    	 }
        
	  	   if (trouve==0) // Si une lettre n'a pas été trouvé, on sort de la boucle directement et la fonction renvoie trouve=0
	  	   {
		     	printf("La lettre %c n'est pas dans votre jeu.\n", chaine_lettres_lues[i]);
  		   	return(trouve);
	       }
	    } // sortie boucle for
	
	    if(trouve==1)
  	{
  		printf("Toutes les lettres entrées sont bien en votre possession.\n");
  		return(trouve);
  	}
	
   } // sortie du else

}
