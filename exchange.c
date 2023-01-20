#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_JETON 102
#define MAX_JETON_TOUR 7
#define MAX_JOUEUR 2

/* Déclaration des types globaux*/
// type joueur
struct type_joueur
{
  int id_joueur;
  int score;
  char jeton[MAX_JETON_TOUR];
};

// variables globales
struct type_joueur tabjoueur[MAX_JOUEUR];
char tabjeton[TOTAL_JETON];
int sac_vide = 0;
char chaine_lettres_lues[MAX_JETON_TOUR]; // une variable globale qui va nous permettre de stocker les lettres lues
// les comparer avec les lettres possédées et puis faire l'opération de remplacement de lettres


void echange ()
{
  char lettre;
  int i = 0, j=0, cpt_jeton = 0, k;
  char jeton;
  int trouve = 0;
  int choix_joueur;
  int lettres_ok;
  int compteur_sac;
  
  compteur_sac=verification_sac();
  if(compteur_sac<7)
  {
  	printf("échange impossible : Il y a moins de 7 lettres dans le sac");
  }
  
  else
  {
	  printf ("Quel joueur souhaite échanger ses lettres ? : ");
	  scanf ("%d", &choix_joueur);
  
	  // Vérification que l'utilisateur a bien entré un identifiant de joueur correct
	  while (choix_joueur < 1 || choix_joueur > MAX_JOUEUR)
  	  {
  	    printf ("Le numéro de joueur doit être entre 1 et %d", MAX_JOUEUR);
  	    scanf ("%d", &choix_joueur);
  	  }

	  // Le tableau de joueur commençant à 0, il faut décrémenter la variable choix_joueur
	  // Pour traiter le joueur demandé par l'utilisateur. Si l'utilisateur demande le joueur 1
 	 // il faut traiter la case 0 du tableau de joueur
 	 choix_joueur--;
  

	// rappel des lettres possédées par le joueur
 	 printf ("Le joueur %d possède les lettres suivantes : \n", tabjoueur[choix_joueur].id_joueur);
 	 affichage_lettre_joueur (choix_joueur);
 	 printf ("Quelles lettres souhaitez-vous remettre dans le sac ? : ");
  
 	 // appel à la fonction verif_lettres qui permettra à l'utilisateur de saisir des lettres
 	 // dont le programme vérifiera qu'elles correspondent aux lettres qu'il possède
  
 	 lettres_ok=verif_lettres(choix_joueur);

 	 // cette boucle va permettre de lire toutes les lettres entrées par l'utilisateur
 	 // et enregistrées dans le tableau chaine_lettre
 	 // jusqu'à arriver à une case vide 
  
  	while(lettres_ok==0)
  	{
  		printf("Les lettres que vous avez saisies n'ont pas été reconnues.\n");
  		printf("Veuillez saisir des lettres en votre possession.\n");
  		affichage_lettre_joueur(choix_joueur);
  		printf("Quelles lettres souhaitez-vous remettre dans le sac ? : ");
  		lettres_ok=verif_lettres(choix_joueur);
  	}

 	for(i=0; chaine_lettres_lues[i]!='\0'; i++)
    {
	    // tant que la lettre entrée n'a pas été trouvée parmi les lettres du joueur, on ne
	    // sort pas de la boucle. qaudn la lettre a été trouvée, le booléen trouve est 
	    // mis à 1. à la sortie de la boucle, le booléen trouve est remis à 0 pour pouvoir
	    // y entrer à nouveau lorsqu'une nouvelle lettre sera traitée
    
	  while (trouve != 1)
		    {
	       // si la variable lettre lue est égale à l'un des caractères possédés par le joueur
	       // alors les lettres sont échangées grâce à la fonction de tirage spécifique à l'échabnge
	  	    if (chaine_lettres_lues[i] == tabjoueur[choix_joueur].jeton[j])
			{
			  printf ("Lettre %c remise dans le sac\n",  tabjoueur[choix_joueur].jeton[j]);
			  remise(tabjoueur[choix_joueur].jeton[j]);
			  tabjoueur[choix_joueur].jeton[j]='\0';
			  trouve = 1;
			  cpt_jeton++;

			}
		   // si le caractère [i] du joueur n'est pas le même que la lettre lue, on passe au
		   // caractère suivant
		      else
			{
			  j++;
			}
		    }
	  // on remet trouve et le compteur j à 0 pour pouvoir repasser dans la boucle while après
	  // et rescanner toutes les lettres
		  trouve = 0;
		  j = 0;
	
  	}
  	  
 	 printf ("Vous avez remis %d jetons dans le sac.\n", cpt_jeton);
 	 tirage(cpt_jeton, choix_joueur);

	  printf ("Voici votre nouveau set de lettres : ");
 	 for (i = 0; i < MAX_JETON_TOUR; i++)
 	   {
  	    printf ("%c ", tabjoueur[choix_joueur].jeton[i]);
  	  }
  	printf ("\n");
  	
	} // fermeture du else (si compteur_sac est égal ou supérieur à 7)

}

// this function allows the user to put back a tile in the bag when exchanging letters

void remise (int lettre_remise)
{
 int i=0;
 
 while(tabjeton[i]!='\0')
 {
 	i++;
 }
 
 tabjeton[i]=lettre_remise;

}
