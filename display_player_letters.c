#include <stdio.h>
#define MAX_JETON_TOUR 7
#define MAX_JOUEUR 2

struct type_joueur
{
  int id_joueur;
  int score;
  char jeton[MAX_JETON_TOUR];
};

struct type_joueur tabjoueur[MAX_JOUEUR];

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