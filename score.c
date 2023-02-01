#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "plateau.c"
#include "player.c"
#include "saclettre.c"

int temp_score = 0;

void score_mots_modif(char word_read[TAILLE_PLATEAU], int column, int row, int direction, int player);

// Calcul du score
// Modifie aussi les valeurs du plateau afin d'enlever les valeurs spéciales déjà utilisées;
void get_player_score(char word_read[TAILLE_PLATEAU], int column, int row, int direction, int player)
{
    int sum = 0;
    int mult = 1;
    int letter_index = 0;

    // 1- Comptabilise les points des lettres et leurs multiplicateurs
    for (int i = 0; i < strlen(word_read); i++)
    {
        if (islower(plateau[row][column].tuile))
        {
            letter_index = 91;
            tablettre[letter_index].nbpoint = 0; // je ne sais pas pourquoi ça me le met à 1 par défaut...
        }
        else
        {
            letter_index = plateau[row][column].tuile - 'A';
        }
        // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
        if (word_read[i] != TUILE_STANDARD)
        {
            // Commence le comptage des valeurs
            if (plateau[row][column].type == BALISE_LETTRE)
            {
                sum += plateau[row][column].valeur * tablettre[letter_index].nbpoint;
                plateau[row][column].valeur = CASE_SIMPLE;
                plateau[row][column].type = BALISE_ABSENTE;
            }
            else if (plateau[row][column].type == BALISE_MOT)
            {
                sum += tablettre[letter_index].nbpoint;
                mult *= plateau[row][column].valeur;
                plateau[row][column].valeur = CASE_SIMPLE;
                plateau[row][column].type = BALISE_ABSENTE;
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
            column++;
        }
        else
        {
            row++;
        }
    }

    tabjoueur[player].score += sum * mult;
    tabjoueur[player].score += temp_score;
    printf("Nombre de points accumulés dans ce tour: %d\n", (sum * mult) + temp_score);
    temp_score = 0;
    printf("Votre score total (joueur %d) est : %d\n", player + 1, tabjoueur[player].score);
}

void print_letter_value()
{
    // to do: renvoie les valeurs de chaque lettre qui sont à la main du joueur;
}
