#include <stdio.h>

#define BOARD_SIZE 15
#define TRIPLE_CASE 3
#define DOUBLE_CASE 2

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
void print_board_value();

int main()
{
    create_board();
    print_board();
    set_board_value();
    print_board_value();
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
            board[i][j].value = 1;
            board[i][j].type = 'A';
        }
    }
}

void set_board_value()
{
    // Le type 'A' indique l'absence de multiplication
    // Le type 'M' indique une multiplication du mot
    // Le type 'L' indique une multiplication de la valeur de la lettre
    board[0][0].value = TRIPLE_CASE;
    board[0][0].type = 'M';

    board[0][7].value = TRIPLE_CASE;
    board[0][7].type = 'M';

    board[0][14].value = TRIPLE_CASE;
    board[0][14].type = 'M';
    
    board[7][0].value = TRIPLE_CASE;
    board[7][0].type = 'M';

    board[7][14].value = TRIPLE_CASE;
    board[7][14].type = 'M';

    board[14][0].value = TRIPLE_CASE;
    board[14][0].type = 'M';

    board[14][7].value = TRIPLE_CASE;
    board[14][7].type = 'M';

    board[14][14].value = TRIPLE_CASE;
    board[14][14].type = 'M';
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

void modify_board()
{
    column--;
    row--;
    board[row][column].tile = jeton;
}
