#include <stdio.h>

#define BOARD_SIZE 15

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
void get_position();
void print_board();
void modify_board();
void set_board_value();

int main()
{
    create_board();
    print_board();
    get_position();
    modify_board();
    print_board();
    return 0;
}

void get_position()
{

    printf("Entrez la lettre à ajouter au tableau: ");
    scanf("%c", &jeton);
    printf("Entrez le numéro de la colomne: ");
    scanf("%d", &column);
    printf("Entrez le numéro de la ligne: ");
    scanf("%d", &row);

}

void create_board()
{
    // i pour la ligne
    for (i = 0; i < BOARD_SIZE; i++)
    {
        // j pour la colomne
        for (j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].tile = '0';
        }
    }
}

void print_board()
{

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {            
            printf("%c ", board[i][j].tile);
            if (j == BOARD_SIZE - 1)
            {
                printf("\n");
            }
        }
    }

}

void set_board_value()
{

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == 7) || (i == 0 && j == 14))
            {
                board[i][j].value = 3;
                // Le type 'M' indique la valeur totale du mot 
                board[i][j].type = 'M';
            }
            else
            {
                board[i][j].value = 1;
                board[i][j].type = NULL;
            }
        }
    }

}

void modify_board()
{
    column--;
    row--;
    board[row][column].tile = jeton;
}
