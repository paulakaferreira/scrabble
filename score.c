#pragma once
#include <stdio.h>
#include <string.h>
#include "board.c"
#include "player.c"
#include "saclettre.c"

// Calcul du score
// Modifie aussi les valeurs du board afin d'enlever les valeurs spéciales déjà utilisées;
void get_player_score(char word_read[30], int column, int row, int direction, int player)
{
    int sum = 0;
    int mult = 1;
    int letter_index = 0;

    puts(word_read);

    // 1- Comptabilise les points des lettres et leurs multiplicateurs
    for (int i = 0; i < strlen(word_read); i++)
    {
        letter_index = board[row][column].tile - 'A';
        // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
        if (word_read[i] != DEFAULT_TILE)
        {
            // Commence le comptage des valeurs
            if (board[row][column].type == LETTER_FLAG)
            {
                sum += board[row][column].value * tablettre[letter_index].nbpoint;
            }
            else if (board[row][column].type == WORD_FLAG)
            {
                sum += tablettre[letter_index].nbpoint;
                mult *= board[row][column].value;
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
    printf("Nombre de points accumulés dans ce tour: %d\n", sum * mult);
    printf("Votre score total (joueur %d) est : %d\n", player, tabjoueur[player].score);
}

void print_letter_value()
{
    // to do: renvoie les valeurs de chaque lettre qui sont à la main du joueur;
}