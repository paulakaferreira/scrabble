#pragma once
#include <stdio.h>
#include "saclettre.c"
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

void affichage_lettre_joueur(int joueur_lu)
{
  int i;

  printf("Lettres du joueur %d:\n", joueur_lu + 1);
  for (i = 0; i < MAX_JETON_TOUR; i++)
  {
    printf("%c ", tabjoueur[joueur_lu].jeton[i]);
  }
  printf("\n");
}

void cpt_lettres_joueur(int joueur_lu)
{
  int i;
  int cpt = 0;

  for (i = 0; i < MAX_JETON_TOUR; i++)
  {
    if (tabjoueur[joueur_lu].jeton[i] != '\\')
    {
      cpt++;
    }
  }

  if (cpt == 0)
  {
    lettre_joueur_vide = 1;
  }
  else
  {
    lettre_joueur_vide = 0;
  }
}

// fonction pour changer le tour du joueur.
int change_turn(int player)
{
  if (player == MAX_JOUEUR - 1)
  {
    return 0;
  }
  else
  {
    return player + 1;
  }
}

int fin_partie()
{
  int i, j;
  int malus = 0;
  int index_lettre = 0;

  for (i = 0; i < MAX_JOUEUR; i++)
  {
    for (j = 0; j < MAX_JETON_TOUR; j++)
    {
      if (tabjoueur[i].jeton[j] != '\0')
      {
        index_lettre = tabjoueur[i].jeton[j] - 'A';
        malus += tablettre[index_lettre].nbpoint;
      }
    }
    // if (score =)
    tabjoueur[i].score = tabjoueur[i].score - malus;
    printf("Le joueur %d prend un malus de %d\n", tabjoueur[i].id_joueur, malus);
    if((tabjoueur[i].id_joueur==1)&&(malus>0))
    {
      tabjoueur[1].score += malus;
      printf("Le joueur %d prend un bonus de %d\n", tabjoueur[1].id_joueur, malus);
    }
    else if((tabjoueur[i].id_joueur==2)&&(malus > 0))
    {
      tabjoueur[0].score += malus;
      printf("Le joueur %d prend un bonus de %d\n", tabjoueur[0].id_joueur, malus);
    }
    malus = 0;
  }

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

  printf("Score final : \n");
  printf("Joueur 1 : %d points.\n", tabjoueur[0].score);
  printf("Joueur 2 : %d points. \n", tabjoueur[1].score);
  return 1;
}

void valeurs_lettre_main(int current_player)
{
  char lettre_lue = '\0';
  int indice_lettre = 0;
  int point = 0;
  printf(" -------Valeurs dans votre main-------\n\n");
  for (int i = 0; i < MAX_JETON_TOUR; i++)
  {
    lettre_lue = tabjoueur[current_player].jeton[i];
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
