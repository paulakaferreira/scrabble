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
    int sum, letter_sum, word_sum = 0;
    int letter_index = 0;

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
                letter_sum += board[row][column].value * tablettre[letter_index].nbpoint;
            }
            else if (board[row][column].value == ABSENT_FLAG)
            {
                letter_sum += tablettre[letter_index].nbpoint;
            }
        }
        else
        {
            letter_sum += tablettre[letter_index].nbpoint;
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

    // 2 - Comptabilise les multiplicateurs du mot
    for (int i = 0; i < strlen(word_read); i++)
    {

        if (board[row][column].type == WORD_FLAG)
        {
            word_sum += board[row][column].value * letter_sum;
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

    tabjoueur[player].score += word_sum;
    // A enlever
    printf("word read:");
    puts(word_read);
    printf("Nombre de points accumulés dans ce tour: %d\n", word_sum);
    printf("Votre score total (joueur %d) est : %d\n", player, tabjoueur[player].score);
}