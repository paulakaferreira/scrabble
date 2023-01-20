#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionnary.c"

#define BOARD_SIZE 15

#define TRIPLE_CASE 3
#define DOUBLE_CASE 2
#define SIMPLE_CASE 1

#define WORD_FLAG 'W'
#define LETTER_FLAG 'L'
#define ABSENT_FLAG 'A'

#define DEFAULT_TILE '.'


struct Square 
{
    int value;
    char type;
    char tile;

};

struct Square board[BOARD_SIZE][BOARD_SIZE];
char jeton;
int column, row;
int i = 0;
int j = 0;

void create_board();
void get_move();
void print_board();
void set_board_value();
void print_board_value();
int check_board_compatibility(int column, int row, char direction, char word_read[30]);

int main()
{
    create_board();
    set_board_value();
    print_board();
    //print_board_value();
    while (1)
    {
        get_move();
        print_board();
    }
    return 0;
}


int check_board_compatibility(int column, int row, char direction, char word_read[30])
{

    for (i = 0; i < strlen(word_read); i++)
    {
        if (board[row][column].tile != word_read[i] && board[row][column].tile != DEFAULT_TILE)
        {
            return 0;
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

    return 1;
}

// Demande au joueur de jouer son tour
void get_move()
{
    int count = 1;
    char word_read[30];
    char direction;

    printf("Vouz avez decidé d'ajouter un mot au tableau. \n");
    strcpy(word_read, "not-a-word");


    while (in_dic(word_read) == 0)
    {
        printf("Entrez le mot à ajouter au tableau: ");
        scanf("%s", word_read);
        for (i = 0; i < strlen(word_read); i++)
        {
            word_read[i] = toupper(word_read[i]);

        }
        if (in_dic(word_read) == 0)
        {
            printf("Le mot que vous avez écrit n'est pas dans notre dictionnaire\n");
            //Ici, on aura l'option de retour au menu
            printf("Merci d'entrer un mot valide.\n");
        }
    }

    printf("Le mot est valide \n");
    printf("Entrez le numéro de la colomne où la première lettre du mot apparaitra (1 - 15): ");
    scanf("%d", &column);
    printf("Entrez le numéro de la ligne où la première lettre du mot apparaitra (1 - 15): ");
    scanf("%d", &row);
    printf("Entrez la direction du mot (H pour horizontal et V pour vertical) : ");
    scanf(" %c", &direction);
    direction = toupper(direction);


    column--;
    row--;

    if (check_board_compatibility(column, row, direction, word_read) == 1)
    {

        printf("Votre mot est compatible avec le tableau\n");
        // Ajoute du mot validé au tableau
        for (i = 0; i < strlen(word_read); i++)
        {
            board[row][column].tile = toupper(word_read[i]);
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

}

// Initialise le tableau avec les valeurs de base
void create_board()
{
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
                    printf("# ");
                }
                // Mot double
                else if ((board[i][j].value == DOUBLE_CASE) && (board[i][j].type == WORD_FLAG))
                {
                    printf("@ ");
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
