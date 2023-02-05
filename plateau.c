#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionnaire.c"

#define TAILLE_PLATEAU 15

#define CASE_TRIPLE 3
#define CASE_DOUBLE 2
#define CASE_SIMPLE 1

#define BALISE_MOT 'W'
#define BALISE_LETTRE 'L'
#define BALISE_ABSENTE 'A'

#define TUILE_STANDARD '.'

#define MAX_JETON_TOUR 7

struct Carre
{
    int valeur;
    char type;
    char tuile;
};

struct Carre plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
struct Carre copie_plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];

/******** Initialisation du plateau ********/
void creation_plateau()
{
    int i, j = 0;

    // i pour la ligne
    for (i = 0; i < TAILLE_PLATEAU; i++)
    {
        // j pour la colomne
        for (j = 0; j < TAILLE_PLATEAU; j++)
        {
            plateau[i][j].tuile = TUILE_STANDARD;
            plateau[i][j].valeur = CASE_SIMPLE;
            plateau[i][j].type = BALISE_ABSENTE;
        }
    }
}

/***** Implémente les valeurs du plateau *****/
void init_valeurs_plateau()
{
    int i, j = 0;
    // Crétion du premier triangle + ligne du milieu
    plateau[0][0].valeur = CASE_TRIPLE;
    plateau[0][0].type = BALISE_MOT;

    plateau[0][3].valeur = CASE_DOUBLE;
    plateau[0][3].type = BALISE_LETTRE;

    // Début colonne du milieu
    plateau[0][7].valeur = CASE_TRIPLE;
    plateau[0][7].type = BALISE_MOT;

    plateau[3][7].valeur = CASE_DOUBLE;
    plateau[3][7].type = BALISE_LETTRE;

    plateau[14][7].valeur = CASE_TRIPLE;
    plateau[14][7].type = BALISE_MOT;

    plateau[11][7].valeur = CASE_DOUBLE;
    plateau[11][7].type = BALISE_LETTRE;
    // Fin colonne du milieu

    // Début ligne du milieu
    plateau[7][0].valeur = CASE_TRIPLE;
    plateau[7][0].type = BALISE_MOT;

    plateau[7][3].valeur = CASE_DOUBLE;
    plateau[7][3].type = BALISE_LETTRE;

    plateau[7][14].valeur = CASE_TRIPLE;
    plateau[7][14].type = BALISE_MOT;

    plateau[7][11].valeur = CASE_DOUBLE;
    plateau[7][11].type = BALISE_LETTRE;
    // Fin ligne du milieu

    // Carré du milieu
    plateau[7][7].valeur = CASE_DOUBLE;
    plateau[7][7].type = BALISE_MOT;
    // Fin carré du milieu

    plateau[1][5].valeur = CASE_TRIPLE;
    plateau[1][5].type = BALISE_LETTRE;

    plateau[2][6].valeur = CASE_DOUBLE;
    plateau[2][6].type = BALISE_LETTRE;

    plateau[1][1].valeur = CASE_DOUBLE;
    plateau[1][1].type = BALISE_MOT;

    plateau[2][2].valeur = CASE_DOUBLE;
    plateau[2][2].type = BALISE_MOT;

    plateau[3][3].valeur = CASE_DOUBLE;
    plateau[3][3].type = BALISE_MOT;

    plateau[4][4].valeur = CASE_DOUBLE;
    plateau[4][4].type = BALISE_MOT;

    plateau[5][5].valeur = CASE_TRIPLE;
    plateau[5][5].type = BALISE_LETTRE;

    plateau[6][6].valeur = CASE_DOUBLE;
    plateau[6][6].type = BALISE_LETTRE;

    // Réflexion du premier triangle = création d'un carré
    for (i = 0; i < (TAILLE_PLATEAU / 2); i++)
    {
        for (j = 0; j < (TAILLE_PLATEAU / 2); j++)
        {
            plateau[j][i].valeur = plateau[i][j].valeur;
            plateau[j][i].type = plateau[i][j].type;
        }
    }

    // Réflexion du carré = création d'un réctangle (première moité du tableau)
    for (i = 0; i < (TAILLE_PLATEAU / 2); i++)
    {
        for (j = 0; j < (TAILLE_PLATEAU / 2); j++)
        {
            plateau[(TAILLE_PLATEAU - 1) - i][j].valeur = plateau[i][j].valeur;
            plateau[(TAILLE_PLATEAU - 1) - i][j].type = plateau[i][j].type;
        }
    }

    // Réflexion de la moité du tableau = création du tableau complét
    for (i = 0; i < TAILLE_PLATEAU; i++)
    {
        for (j = 0; j < (TAILLE_PLATEAU / 2); j++)
        {
            plateau[i][(TAILLE_PLATEAU - 1) - j].valeur = plateau[i][j].valeur;
            plateau[i][(TAILLE_PLATEAU - 1) - j].type = plateau[i][j].type;
        }
    }
}

/********* Affichage du plateau **********/
void affichage_plateau()
{
    int i, j;
    int k = 1;

    // Imprime les indices des colonnes
    printf("Voici le plateau à l'état actuel: \n");
    printf("\n");
    printf("     A B C D E F G H I J K L M N O\n");
    printf("    ------------------------------\n");
    for (i = 0; i < TAILLE_PLATEAU; i++)
    {
        // Imprime les indices des lignes
        if (k < 10)
        {
            printf("0%d | ", k);
        }
        else
        {
            printf("%d | ", k);
        }
        k++;

        // Imprime les valeurs du tableau
        for (j = 0; j < TAILLE_PLATEAU; j++)
        {
            // Imprime les carrés spéciaux
            if (plateau[i][j].tuile == TUILE_STANDARD)
            {
                // Mot triple
                if ((plateau[i][j].valeur == CASE_TRIPLE) && (plateau[i][j].type == BALISE_MOT))
                {
                    printf("@ ");
                }
                // Mot double
                else if ((plateau[i][j].valeur == CASE_DOUBLE) && (plateau[i][j].type == BALISE_MOT))
                {
                    printf("# ");
                }
                // Lettre double
                else if ((plateau[i][j].valeur == CASE_DOUBLE) && (plateau[i][j].type == BALISE_LETTRE))
                {
                    printf("* ");
                }
                // Lettre triple
                else if ((plateau[i][j].valeur == CASE_TRIPLE) && (plateau[i][j].type == BALISE_LETTRE))
                {
                    printf("& ");
                }
                else
                {
                    printf("%c ", plateau[i][j].tuile);
                }
            }
            else
            {
                printf("%c ", plateau[i][j].tuile);
            }

            // Saut de ligne du tableau
            if (j == TAILLE_PLATEAU - 1)
            {
                printf("\n");
            }
        }
    }
}

/****** Affiche les valeurs des cases du plateau ******/
void affichage_valeurs_plateau()
{
    int i, j = 0;
    for (i = 0; i < TAILLE_PLATEAU; i++)
    {
        for (j = 0; j < TAILLE_PLATEAU; j++)
        {
            printf("%d ", plateau[i][j].valeur);
            if (j == TAILLE_PLATEAU - 1)
            {
                printf("\n");
            }
        }
    }
}
