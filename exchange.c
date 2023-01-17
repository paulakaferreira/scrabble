#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LETTRE 27
#define TOTAL_JETON 102
#define MAX_JETON_TOUR 7
#define MAX_JOUEUR 2

/* Déclaration des types globaux*/

// type lettre
struct lettre
{
  int id_lettre;
  int nbpoint, quantite;
};

// type joueur
struct type_joueur
{
  int id_joueur;
  int score;
  char jeton[MAX_JETON_TOUR];
};

// variables globales
struct lettre tablettre[MAX_LETTRE];
struct type_joueur tabjoueur[MAX_JOUEUR];
char tabjeton[TOTAL_JETON - 1];
int premier_tour = 1;
int sac_vide = 0;
char chaine_lettres_lues[MAX_JETON_TOUR]; // une variable globale qui va nous permettre de stocker les lettres lues
// les comparer avec les lettres possédées et puis faire l'opération de remplacement de lettres

void fiche_lettre ();
void saclettres ();
void init_joueur ();
void affichage_lettre_joueur (int joueur_lu);
void affichage_sac ();
void echange ();
void remise (int lettre_remise);
void tirage (int nb_jetons, int joueur_lu);
int verification_sac ();
int verif_lettres();

/*-------------------Programme appelant--------------------*/

int main ()
{


  fiche_lettre ();
  saclettres ();
  init_joueur ();
  tirage (7, 1);
  echange ();
	
}

void fiche_lettre ()
{


  struct lettre lettre;
  int i, j;

/* Utilisation d'une boucle for qui parcourt i de 65 (code ASCII de A) jusque 90, code ASCII de Z,
et 91 qu'on utilisera pour le cas des jetons joker. Le switch est fait en utilisant les caractères
qui sont interprétés comme entiers, par leur code ASCII */

  for (i = 65, j = 0; i < MAX_LETTRE + 65; i++, j++)
    {

      if (i == 91)
	{
	  lettre.id_lettre = '0';
	}
      else
	{
	  lettre.id_lettre = i;
	}


      switch (i)
	{
	case 'A':
	case 'E':
	case 'I':
	case 'L':
	case 'N':
	case 'O':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	  lettre.nbpoint = 1;
	  break;

	case 'D':
	case 'G':
	case 'M':
	  lettre.nbpoint = 2;
	  break;

	  /* Pour les cas suivants, chaque lettre valant le même nombre de point ont aussi la même quantité. Cela permet de simplifier le switch 
	     suivant qui attribuera une quantité à une lettre */
	case 'B':
	case 'C':
	case 'P':
	  lettre.nbpoint = 3;
	  lettre.quantite = 2;
	  break;

	case 'F':
	case 'H':
	case 'V':
	  lettre.nbpoint = 4;
	  lettre.quantite = 2;
	  break;

	case 'J':
	case 'Q':
	  lettre.nbpoint = 8;
	  lettre.quantite = 1;
	  break;

	case 'K':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	  lettre.nbpoint = 10;
	  lettre.quantite = 1;
	  break;

	  /* Cas des jetons jokers */
	case 91:
	  lettre.nbpoint = 0;
	  lettre.quantite = 2;
	  break;
	}

      switch (i)
	{
	case 'E':
	  lettre.quantite = 15;
	  break;

	case 'A':
	  lettre.quantite = 9;
	  break;

	case 'I':
	  lettre.quantite = 8;
	  break;

	case 'N':
	case 'O':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	  lettre.quantite = 6;
	  break;

	case 'L':
	  lettre.quantite = 5;
	  break;

	case 'D':
	case 'M':
	  lettre.quantite = 3;
	  break;
	case 'G':
	  lettre.quantite = 2;
	  break;


	}
	/* La variable lettre en type structure lettre est rangée dans un tableau de 
	structure lettre, et ceci à chaque passage de la boucle qui incrémente le compteur
	j pour avancer dans le tableau, jusqu'à <MAX_LETTRE qui correspond à 92 */
      tablettre[j] = lettre;
    }

}


void saclettres ()
{
  int i, j = 0;

/* Ici, la boucle for parcourt le tableau de caractères tabjeton, qui correspond au sac de lettre
grâce au compteur i. la variable j permet de vérifier la quantité de chaque lettre, si tablettre[j]
n'est pas égal à 0, c'est qu'il y a encore des lettres de ce type à mettre dans le sac de lettres.
Sinon, j est incrémenté pour passer à la lettre suivante, jusqu'à arriver à 0 de quantité pour la
lettre suivante */

  for (i = 0; i < TOTAL_JETON; i++)
    {
      if (tablettre[j].quantite == 0)
	{
	  j++;

	}
	// Quand la quantité n'est pas égale à 0, on range cette lettre dans une case du sac de lettres
      tabjeton[i] = tablettre[j].id_lettre;
      tablettre[j].quantite--;

    }

/* Les lignes suivantes permettent l'affichage du sac de lettres. à réactiver pour vérification
	for(i=0; i<TOTAL_JETON; i++)
	{
		printf("%c\n", tabjeton[i]);
	}
*/
}


/* ------- Initialisation d'un joueur ------------*/
/* Cette fonction permet d'initialiser deux joueurs, comme demandé par le sujet.
Le nombre de joueur est défini par une constante globale. 
*/
void init_joueur ()
{
  struct type_joueur un_joueur;
  int i;
  int cpt_joueur;

  printf ("Ce scrabble se joue à %d joueurs\n", MAX_JOUEUR);

/* création d'un joueur avec association d'un chiffre (défini par cpt_joueur) et des pièces lui
appartenant, initialisées à 0 dans une boucle for qui va de 1 à <MAX_JETON_TOUR (7).
La variable joueur est ensuite stockée à la fin de la boucle dans un tableau de type structure
joueur*/

  for (cpt_joueur = 0; cpt_joueur < MAX_JOUEUR; cpt_joueur++)
    {
      un_joueur.id_joueur = cpt_joueur+1;
      un_joueur.score = 0;
      for (i = 0; i < MAX_JETON_TOUR; i++)
	{
	  un_joueur.jeton[i] = 0;
	}
      tabjoueur[cpt_joueur] = un_joueur;
      printf ("Le joueur %d a été initialisé. Score : %d\n",
	      tabjoueur[cpt_joueur].id_joueur, tabjoueur[cpt_joueur].score);
    }

}

// Affichage des lettres que possède un joueur
void affichage_lettre_joueur (int joueur_lu)
{
  int i;

  printf ("Lettres du joueur %d\n", joueur_lu + 1);
  for (i = 0; i < MAX_JETON_TOUR; i++)
    {
      printf ("%c ", tabjoueur[joueur_lu].jeton[i]);
    }
  printf ("\n");

}

// Affichage des lettres du sac de lettre. La variable cpt permet de compter le nombre
// de lettres différente du caractère nul ('\0'), et permet donc de compter le nombre
// de lettres restantes.

void affichage_sac ()
{
  int i, cpt = 0;
  for (i = 0; i < TOTAL_JETON; i++)
    {
      printf ("%c", tabjeton[i]);
      if (tabjeton[i] != '\0')
	{
	  cpt++;
	}
    }
  printf ("\n");
  printf ("Il reste %d lettres dans le sac de lettres.\n", cpt);

}

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


void tirage (int nb_jetons, int joueur_lu)
{

  time_t nb_secondes, tp;
  int alea, initialisation;
  int i = 0;
  int cpt_joueur;
  int cpt_jeton = 0;
  int trouve = 0;
  int cpt_jeton_tire = 0;

  /* Pour la fonction aléatoire, récupération du nombre de seconde écoulée depuis 1970 */
  nb_secondes = time (&tp);

  /* Initialisation de la fonction aléatoire */
  initialisation = nb_secondes;
  srand (initialisation);

  alea = rand () % 102;

  // booléen premier tour, car au premier tour, toutes les lettres sont initialisés
  // donc comportement légérement différent. à la fin du tirage du premier tour
  // ce booléen passe à 0. Le booléen premier_tour doit impérativement être une variable
  // globale
  
  if (premier_tour == 1)
    {
      for (cpt_joueur = 0; cpt_joueur < MAX_JOUEUR; cpt_joueur++)
	{
	  while (i < MAX_JETON_TOUR)
	    {
	     // vérification que la case du jeton sélectionné au hasard n'est pas vide
	      if (tabjeton[alea] != '\0')
		{
		  tabjoueur[cpt_joueur].jeton[i] = tabjeton[alea];
		  // remplacement de la case tabjeton[alea] par un caractère vide
		  tabjeton[alea] = '\0';
		  // on reprend une autre valeur aléatoire
		  alea = rand () % 102;
		  // on incrémente le compteur i pour passer à la case suivante des caractères
		  // que possède le joueur
		  i++;
		}
		// si tabjeton[alea] est vide, on reprend un autre nombre aléatoire et on repasse dans la
		// boucle, sans incrémenter i.
	      else
		{
		  alea = rand () % 102;
		}
	    }
	    // à la sortie de cette boucle while, il faut repasser i à 0 pour parcourir les letttres
	    // du joueur suivant
	  i = 0;
	}
      premier_tour = 0;
    }

  else
    {
      while (i < nb_jetons)
	{
	  verification_sac ();
	  // la fonction verification_sac renvoie un booléen. On vérifie ici que le sac 
	  // n'est pas vide (1 si vide, 0 si pas vide)
	  if (sac_vide == 0)
	    {
	       // on vérifie ici si la case de caractères du joueur est vide ou pas avant 
	       // de tirer un nouveau jeton
	      if ((tabjoueur[joueur_lu].jeton[cpt_jeton] == '\0'))
		{
		  alea = rand () % 102;
		  // on vérifie aussi que tabjeton[alea] contient bien un jeton; Sinon, on 
		  // reprend une autre valeur aléatoire
		  if (tabjeton[alea] != '\0')
		    {
		      tabjoueur[joueur_lu].jeton[cpt_jeton] = tabjeton[alea];
		      tabjeton[alea] = '\0';
		      i++;
		      cpt_jeton++;
		      alea = rand () % 102;
		      // cpt_jeton_tire permet de compter le nb de jetons remplacés.
		      // à ne pas confondre avec cpt_jeton qui permet de parcourir le tableau
		      // de jetons possédés par le joueur
		      cpt_jeton_tire++;
		    }
		  else
		    {
		      alea = rand () % 102;
		    }
		}
	      else
		{
		  // si [cpt_jeton]du joueur est pas vide, on vérifie si la case suivante est vide
		  cpt_jeton++;
		}
	    }
	  else
	  // cas où le sac est vide
	    {

		  printf ("Le sac de lettre est vide. il est impossible de piocher plus de %d lettres\n",cpt_jeton_tire);
		// on met i au nombre de jetons demandés pour sortir de la boucle définitivement
	      i = nb_jetons;
	    }

	}
      printf ("Vous avez tiré %d jetons\n", cpt_jeton_tire);
    }
}


// cette fonction n'existe pas au scrabble
// mais permet de vérifier que le sac se vide bien et qu'on ne peut pas piocher plus de lettres que
// ce que l'on possède
// fonctionnement similaire à la fonction échange mais les letres sélectionnées ne sont pas remises
// dans le sac, et on fait appel à la fonction tirage habituelle

// cette fonction parcour tout le sac de lettres
// et si une case est pleine, incrémente un compteur qui permet de compter le nombre
// de lettres restantes dans le sac.
// si le sac est vide, alors cpt=0, ce qui met à 1 le booléen sac_vide

int verification_sac ()
{
  int i, cpt = 0;
  for (i = 0; i < TOTAL_JETON; i++)
    {
      if (tabjeton[i] != '\0')
	{
	  cpt++;
	}
    }
  if (cpt == 0)
    {
      sac_vide = 1;
    }
    
    return(cpt);

}

// Fonction permettant de vérifier si le joueur a bien les lettres de la saisie qu'il vient d'entrer
int verif_lettres(int choix_joueur)
{
	int lettre='v';
	int i;
	int j=0;
	int trouve=0;
	
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
    	while ((lettre=getchar())  != '\n')
    	{
    		if(lettre!=' ')
    		{
    			lettre=toupper(lettre);
    			chaine_lettres_lues[i]=lettre;
    			i++;
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
    		}
    	}
    }
    
	
	
	for(i=0; chaine_lettres_lues[i]!='\0'; i++)
	{
		if(chaine_lettres_lues[i]!='\0')
		{
			trouve=0;
		}
		for(j=0; j<MAX_JETON_TOUR; j++)
		{
			if(tabjoueur[choix_joueur].jeton[j]==chaine_lettres_lues[i])
				{
					trouve=1;
					j=MAX_JETON_TOUR;
				}
			
		}
		if (trouve==0) // Si une lettre n'a pas été trouvé, on sort de la boucle directement et la fonction renvoie trouve=0
		{
			printf("La lettre %c n'a pas été trouvée.\n", chaine_lettres_lues[i]);
			return(trouve);
		}
	}
	
	if(trouve==1)
	{
		printf("Toutes les lettres entrées sont bien en votre possession.\n");
		return(trouve);
	}

}
