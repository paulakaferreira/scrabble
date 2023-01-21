#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionnary.c"

#define BOARD_SIZE 15

#define TRIPLE_CASE 3
#define DOUBLE_CASE 2
#define SIMPLE_CASE 1

#define WORD_FLAG 'W'
#define LETTER_FLAG 'L'
#define ABSENT_FLAG 'A'

#define DEFAULT_TILE '.'

#define MAX_JETON_TOUR 7


struct Square 
{
    int value;
    char type;
    char tile;

};

struct Square board[BOARD_SIZE][BOARD_SIZE];

// Initialise le tableau avec les valeurs de base
void create_board()
{
    int i, j = 0;

    // i pour la ligne
    for (i = 0; i < BOARD_SIZE; i++)
    {
        // j pour la colomne
        for (j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].tile = DEFAULT_TILE;
            board[i][j].value = SIMPLE_CASE;
            board[i][j].type = ABSENT_FLAG;
        }
    }
}

// Implémente les valeurs de multiplication pour chaque carré spécial
void set_board_value()
{
    int i, j = 0;
    // Crétion du premier triangle + ligne du milieu
    board[0][0].value = TRIPLE_CASE;
    board[0][0].type = WORD_FLAG;

    board[0][3].value = DOUBLE_CASE;
    board[0][3].type = LETTER_FLAG;
    
        // Début colomne du milieu
    board[0][7].value = TRIPLE_CASE;
    board[0][7].type = WORD_FLAG;

    board[3][7].value = DOUBLE_CASE;
    board[3][7].type = LETTER_FLAG;

    board[14][7].value = TRIPLE_CASE;
    board[14][7].type = WORD_FLAG;

    board[11][7].value = DOUBLE_CASE;
    board[11][7].type = LETTER_FLAG;
        // Fin colomne du milieu

        //Début ligne du milieu
    board[7][0].value = TRIPLE_CASE;
    board[7][0].type = WORD_FLAG;

    board[7][3].value = DOUBLE_CASE;
    board[7][3].type = LETTER_FLAG;

    board[7][14].value = TRIPLE_CASE;
    board[7][14].type = WORD_FLAG;

    board[7][11].value = DOUBLE_CASE;
    board[7][11].type = LETTER_FLAG;    
        //Fin ligne du milieu

    board[1][5].value = TRIPLE_CASE;
    board[1][5].type = LETTER_FLAG;

    board[2][6].value = DOUBLE_CASE;
    board[2][6].type = LETTER_FLAG;

    board[1][1].value = DOUBLE_CASE;
    board[1][1].type = WORD_FLAG;

    board[2][2].value = DOUBLE_CASE;
    board[2][2].type = WORD_FLAG;

    board[3][3].value = DOUBLE_CASE;
    board[3][3].type = WORD_FLAG;

    board[4][4].value = DOUBLE_CASE;
    board[4][4].type = WORD_FLAG;

    board[5][5].value = TRIPLE_CASE;
    board[5][5].type = LETTER_FLAG;

    board[6][6].value = DOUBLE_CASE;
    board[6][6].type = LETTER_FLAG;

    // Réflexion du premier triangle = création d'un carré
    for (i = 0; i < (BOARD_SIZE / 2); i++)
    {
        for (j = 0; j < (BOARD_SIZE / 2); j++)
        {
            board[j][i].value = board[i][j].value;
            board[j][i].type = board[i][j].type;
        }
    }

    // Réflexion du carré = création d'un réctangle (première moité du tableau)
    for (i = 0; i < (BOARD_SIZE / 2); i++)
    {
        for (j = 0; j < (BOARD_SIZE / 2); j++)
        {
            board[(BOARD_SIZE - 1) - i][j].value = board[i][j].value;
            board[(BOARD_SIZE - 1) - i][j].type = board[i][j].type;
        }
    }

    // Réflexion de la moité du tableau = création du tableau complét
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < (BOARD_SIZE / 2); j++)
        {
            board[i][(BOARD_SIZE - 1) - j].value = board[i][j].value;
            board[i][(BOARD_SIZE - 1) - j].type = board[i][j].type;
        }
    }

}

void print_board()
{
    int i, j = 0;
    printf("Voici le plateau à l'état actuel: \n");
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {   
            // Imprime les carrés spéciaux         
            if (board[i][j].tile == DEFAULT_TILE)
            {
                // Mot triple
                if ((board[i][j].value == TRIPLE_CASE) && (board[i][j].type == WORD_FLAG))
                {
                    printf("@ ");
                }
                // Mot double
                else if ((board[i][j].value == DOUBLE_CASE) && (board[i][j].type == WORD_FLAG))
                {
                    printf("# ");
                }
                // Lettre double
                else if ((board[i][j].value == DOUBLE_CASE) && (board[i][j].type == LETTER_FLAG))
                {
                    printf("* ");
                }
                // Lettre triple
                else if ((board[i][j].value == TRIPLE_CASE) && (board[i][j].type == LETTER_FLAG))
                {
                    printf("& ");
                }
                else
                {
                    printf("%c ", board[i][j].tile);
                }
            }
            else
            {
                printf("%c ", board[i][j].tile);
            }

            // Saut de ligne du tableau
            if (j == BOARD_SIZE - 1)
            {
                printf("\n");
            }
        }
    }

}


void print_board_value()
{
    int i, j = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {            
            printf("%d ", board[i][j].value);
            if (j == BOARD_SIZE - 1)
            {
                printf("\n");
            }
        }
    } 

}
