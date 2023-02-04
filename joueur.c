#pragma once
#include <stdio.h>
#include "lettres.c"
#define MAX_JETON_TOUR 7
#define MAX_JOUEUR 2

struct type_joueur
{
  int id_joueur;
  int score;
  char jeton[MAX_JETON_TOUR];
};

// variables globales
struct type_joueur tabjoueur[MAX_JOUEUR];
int lettre_joueur_vide = 0;

/***** Initialisation des joueurs *****/
void init_joueur(int cpt_joueur)
{
  struct type_joueur un_joueur;
  int i;

  printf("Ce scrabble se joue à %d joueurs\n", MAX_JOUEUR);

  /* création d'un joueur avec association d'un chiffre (défini par cpt_joueur) et des pièces lui
  appartenant, initialisées à 0 dans une boucle for qui va de 1 à <MAX_JETON_TOUR (7).
  La variable joueur est ensuite stockée à la fin de la boucle dans un tableau de type structure
  joueur*/

  for (cpt_joueur = 0; cpt_joueur < MAX_JOUEUR; cpt_joueur++)
  {
    un_joueur.id_joueur = cpt_joueur + 1;
    un_joueur.score = 0;
    for (i = 0; i < MAX_JETON_TOUR; i++)
    {
      un_joueur.jeton[i] = '\0';
    }
    tabjoueur[cpt_joueur] = un_joueur;
    printf("Le joueur %d a été initialisé. Score : %d\n", tabjoueur[cpt_joueur].id_joueur, tabjoueur[cpt_joueur].score);
  }
}

/****** Affichage des lettres du joueur *****/
void affichage_lettre_joueur(int joueur_lu)
{
  int i;

  /* Parcours des lettres du joueur avec la variable i */
  printf("Lettres du joueur %d:\n", joueur_lu + 1);
  for (i = 0; i < MAX_JETON_TOUR; i++)
  {
    printf("%c ", tabjoueur[joueur_lu].jeton[i]);
  }
  printf("\n");
}

/***** Verification du vide - main du joueur *****/
void cpt_lettres_joueur(int joueur_lu)
{
  int i;
  int cpt = 0;

  for (i = 0; i < MAX_JETON_TOUR; i++)
  {
    if (tabjoueur[joueur_lu].jeton[i] != '\\')
    {
      cpt++; // Si le jeton lu est différent du caractère '\\' qui signale un jeton qui n'a pas pu être remplacé, alors cpt est incrémenté
    }
  }

  if (cpt == 0) // si aucun jeton n'a été trouvé, alors lettre_joueur_vide passe à 1
  {
    lettre_joueur_vide = 1;
  }
  else
  {
    lettre_joueur_vide = 0;
  }
}

/***** Changement de tour ******/
int changement_tour(int joueur)
{
  // fonction pour changer le tour du joueur.
  if (joueur == MAX_JOUEUR - 1)
  {
    return 0;
  }
  else
  {
    return joueur + 1;
  }
}

/***** Fin de la partie *****/
int fin_partie()
{
  int i, j;
  int malus = 0;
  int indice_lettre = 0;

  /* Calcul des malus */
  for (i = 0; i < MAX_JOUEUR; i++) // première boucle for qui permet de parcourir tous les joueurs
  {
    for (j = 0; j < MAX_JETON_TOUR; j++) // deuxième boucle for qui permet de parcourir les lettres des joueurs
    {
      if (tabjoueur[i].jeton[j] != '\\' && tabjoueur[i].jeton[j] != '0') // si l'indice du jeton n'est pas vide (signalé par \\) ou pas un joker
      {
        indice_lettre = tabjoueur[i].jeton[j] - 'A';
        malus += tablettre[indice_lettre].nbpoint; // le malus, qui est initialisé à 0, reçoit la valeur de la lettre cherchée danss tablettre
      }
    }
    tabjoueur[i].score = tabjoueur[i].score - malus; // soustraction du malus au score du joueur concerné
    printf("Le joueur %d prend un malus de %d\n", tabjoueur[i].id_joueur, malus);
    if ((tabjoueur[i].id_joueur == 1) && (malus > 0))
    {
      tabjoueur[1].score += malus; // on additionne le malus au score du joueur adverse
      printf("Le joueur %d prend un bonus de %d\n", tabjoueur[1].id_joueur, malus);
    }
    else if ((tabjoueur[i].id_joueur == 2) && (malus > 0))
    {
      tabjoueur[0].score += malus; // on additionne le malus au score du joueur adversse
      printf("Le joueur %d prend un bonus de %d\n", tabjoueur[0].id_joueur, malus);
    }
    malus = 0; // malus remis à 0 pour calculer le malus éventuel de l'autre joueur
  }

  // affichage des gagnants
  if (tabjoueur[0].score > tabjoueur[1].score)
  {
    printf("Le joueur %d a gagné, félicitations !\n", tabjoueur[0].id_joueur);
  }

  else if (tabjoueur[0].score == tabjoueur[1].score)
  {
    printf("Vous êtes à égalité : bravo à tous les deux !\n");
  }
  else
  {
    printf("Le joueur %d a gagné, félicitations !\n", tabjoueur[1].id_joueur);
  }

  // affichage  du score final
  printf("Score final : \n");
  printf("Joueur 1 : %d points.\n", tabjoueur[0].score);
  printf("Joueur 2 : %d points. \n", tabjoueur[1].score);
  return 1;
}

/****** Affichage des valeurs des lettres du joueur *****/
void valeurs_lettre_main(int joueur_actuel)
{
  char lettre_lue = '\0';
  int indice_lettre = 0;
  int point = 0;
  printf(" -------Valeurs dans votre main-------\n\n");
  for (int i = 0; i < MAX_JETON_TOUR; i++)
  {
    lettre_lue = tabjoueur[joueur_actuel].jeton[i];
    if (lettre_lue == '0')
    {
      indice_lettre = MAX_LETTRE - 1;
    }
    else
    {
      indice_lettre = lettre_lue - 'A';
    }

    point = tablettre[indice_lettre].nbpoint;

    if (point > 1)
    {
      printf("Lettre %c: %d points\n", lettre_lue, point);
    }
    else
    {
      printf("Lettre %c: %d point\n", lettre_lue, point);
    }
  }
}
