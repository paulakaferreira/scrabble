#include <stdio.h>
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



// variables globales
struct lettre tablettre[MAX_LETTRE-1];
char tabjeton[TOTAL_JETON - 1];


void fiche_lettre ();
void sac_lettres ();
void affichage_sac();

int main()
{
	fiche_lettre();
	sac_lettres();
	affichage_sac();
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


void sac_lettres ()
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
}

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
