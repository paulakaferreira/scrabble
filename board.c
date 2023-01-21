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
char jeton;
int column, row;

void create_board();
int get_move();
void print_board();
void set_board_value();
void print_board_value();
int check_board_compatibility(int column, int row, char direction, char word_read[30]);


int check_board_compatibility(int column, int row, char direction, char word_read[30])
{
    int i = 0;

    for (i = 0; i < strlen(word_read); i++)
    {
        // Vérifie que le mot peut bien rentrer dans le plateau à l'lendroit souhaité
        if (board[row][column].tile != word_read[i] && board[row][column].tile != DEFAULT_TILE)
        {
            return 0;
        }
        else if (board[row][column].tile != DEFAULT_TILE)
        {
            word_read[i] = DEFAULT_TILE;
        }

        if (direction == 'H')
        {
            column++;
        }
        else
        {
            row++;
        }
    }

    printf("dentro: ");
    puts(word_read);

    return 1;
}

// Demande au joueur de jouer son tour
int get_move()
{
    int i = 0;
    int count = 1;
    char word_read[30];
    char direction;
    int column = 0;
    int row = 0;

    printf("Vouz avez decidé d'ajouter un mot au tableau. \n");
    strcpy(word_read, "not-a-word");


    while (in_dic(word_read) == 0)
    {
        printf("Entrez le mot à ajouter au tableau (1 pour retourner au menu) : ");
        scanf("%s", word_read);
        if (strcmp(word_read, "1") == 0)
        {
            return 0;
        }
        else
        {
            for (i = 0; i < strlen(word_read); i++)
            {
                word_read[i] = toupper(word_read[i]);

            }
            if (in_dic(word_read) == 0)
            {
                printf("Le mot que vous avez écrit n'est pas dans notre dictionnaire\n");
                printf("Merci d'entrer un mot valide.\n");
            }
        }
    }

    printf("Le mot est valide \n");

    // Verification de saisie de la colomne
    while ((column < 1) || (column > 15))
    {
        printf("Entrez le numéro de la colomne où la première lettre du mot apparaitra (1 - 15): ");
        scanf("%d", &column);
        //ajouter le cas ou le caracter n'est pas un chiffre
        if ((column < 1) || (column > 15))
        {
            printf("Réponse invalide. Veuillez réssayer\n");
        }

    }
    // Verification de saisie de la ligne
    while ((row < 1) || (row > 15))
    {
        printf("Entrez le numéro de la ligne où la première lettre du mot apparaitra (1 - 15): ");
        scanf("%d", &row);
        //ajouter le cas ou le caracter n'est pas un chiffre
        if ((row < 1) || (row > 15))
        {
            printf("Réponse invalide. Veuillez réssayer\n");
        }

    }

    while ((direction != 'H') && (direction != 'V'))
    {
        printf("Entrez la direction du mot (H pour horizontal et V pour vertical) : ");
        scanf(" %c", &direction);
        direction = toupper(direction);
    }

    column--;
    row--;

    // Verifie la compatibilité du mot avec le tableau;
    // Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
    if (check_board_compatibility(column, row, direction, word_read) == 1)
    {

        printf("Votre mot est compatible avec le tableau\n");
        printf("fora: ");
        puts(word_read);
        // Ajoute du mot validé au tableau
        for (i = 0; i < strlen(word_read); i++)
        {
            if (word_read[i] != DEFAULT_TILE)
            {
                board[row][column].tile = toupper(word_read[i]);
            }

            // Fait avancer la boucle en fonction de la direction
            if (direction == 'H')
            {
                column++;
            }
            else
            {
                row++;
            }
        }
    }
    else
    {
        printf("Les directions ne sont pas compatibles avec le tableau\n");
        printf("Impossible d'ajouter le mot %s à l'endroit souhaité\n", word_read);
    }

    return 1;

}

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
