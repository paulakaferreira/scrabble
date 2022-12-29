#include <stdio.h>
#define MAX_JETON_TOUR 7
#define MAX_JOUEUR 2

// Type joueur
struct type_joueur
{
  int id_joueur;
  int score;
  char jeton[MAX_JETON_TOUR - 1];
};

// variables globales
struct type_joueur tabjoueur[MAX_JOUEUR];

void init_joueur();


int main()
{
	init_joueur();
}

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
		  un_joueur.jeton[i] = '\0';
		}
      tabjoueur[cpt_joueur] = un_joueur;
      printf ("Le joueur %d a été initialisé. Score : %d\n", tabjoueur[cpt_joueur].id_joueur, tabjoueur[cpt_joueur].score);
    }

}
