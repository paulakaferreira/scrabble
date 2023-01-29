#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "board.c"
#include "player.c"
#include "saclettre.c"

int temp_score = 0;

void score_mots_modif(char word_read[BOARD_SIZE], int column, int row, int direction, int player);

// Calcul du score
// Modifie aussi les valeurs du board afin d'enlever les valeurs spéciales déjà utilisées;
void get_player_score(char word_read[BOARD_SIZE], int column, int row, int direction, int player)
{
    int sum = 0;
    int mult = 1;
    int letter_index = 0;

    puts(word_read);

    // 1- Comptabilise les points des lettres et leurs multiplicateurs
    for (int i = 0; i < strlen(word_read); i++)
    {
        if (islower(board[row][column].tile))
        {
            letter_index = 91;
            tablettre[letter_index].nbpoint = 0; // je ne sais pas pourquoi ça me le met à 1 par défaut...
        }
        else
        {
            letter_index = board[row][column].tile - 'A';
        }
        // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
        if (word_read[i] != DEFAULT_TILE)
        {
            // Commence le comptage des valeurs
            if (board[row][column].type == LETTER_FLAG)
            {
                sum += board[row][column].value * tablettre[letter_index].nbpoint;
                board[row][column].value = SIMPLE_CASE;
                board[row][column].type = ABSENT_FLAG;
            }
            else if (board[row][column].type == WORD_FLAG)
            {
                sum += tablettre[letter_index].nbpoint;
                mult *= board[row][column].value;
                board[row][column].value = SIMPLE_CASE;
                board[row][column].type = ABSENT_FLAG;
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
