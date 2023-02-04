#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "plateau.c"
#include "joueur.c"
#include "lettres.c"

int temp_score = 0;

void score_mots_modif(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, int direction, int joueur);

// Calcul du score
// Modifie aussi les valeurs du plateau afin d'enlever les valeurs spéciales déjà utilisées;
void score_joueur(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, int direction, int joueur)
{
    int sum = 0;
    int mult = 1;
    int letter_index = 0;

    // 1- Comptabilise les points des lettres et leurs multiplicateurs
    for (int i = 0; i < strlen(mot_lu); i++)
    {
        if (islower(plateau[ligne][colonne].tuile))
        {
            letter_index = 91;
            tablettre[letter_index].nbpoint = 0; // je ne sais pas pourquoi ça me le met à 1 par défaut...
        }
        else
        {
            letter_index = plateau[ligne][colonne].tuile - 'A';
        }
        // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
        if (mot_lu[i] != TUILE_STANDARD)
        {
            // Commence le comptage des valeurs
            if (plateau[ligne][colonne].type == BALISE_LETTRE)
            {
                sum += plateau[ligne][colonne].valeur * tablettre[letter_index].nbpoint;
                plateau[ligne][colonne].valeur = CASE_SIMPLE;
                plateau[ligne][colonne].type = BALISE_ABSENTE;
            }
            else if (plateau[ligne][colonne].type == BALISE_MOT)
            {
                sum += tablettre[letter_index].nbpoint;
                mult *= plateau[ligne][colonne].valeur;
                plateau[ligne][colonne].valeur = CASE_SIMPLE;
                plateau[ligne][colonne].type = BALISE_ABSENTE;
            }
            else
            {
                sum += tablettre[letter_index].nbpoint;
            }
        }
        else
        {
            sum += tablettre[letter_index].nbpoint;
        }
        // Fait avancer la boucle
        if (direction == 'H')
        {
            colonne++;
        }
        else
        {
            ligne++;
        }
    }

    tabjoueur[joueur].score += sum * mult;
    tabjoueur[joueur].score += temp_score;
    printf("Nombre de points accumulés dans ce tour: %d\n", (sum * mult) + temp_score);
    temp_score = 0;
    printf("Votre score total (joueur %d) est : %d\n", joueur + 1, tabjoueur[joueur].score);
}

void print_letter_value()
{
    // to do: renvoie les valeurs de chaque lettre qui sont à la main du joueur;
}
