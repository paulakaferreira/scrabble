#include <stdio.h>

#define BOARD_SIZE 15

char board_value[BOARD_SIZE][BOARD_SIZE];
char jeton;
int column, row;
int i = 0;
int j = 0;

void create_board();
void print_board();
void modify_board(char jeton, int column, int row);

int main()
{
    create_board();
    print_board();
    printf("Enter letter: ");
    scanf("%c", &jeton);
    printf("Enter column ");
    scanf("%d", &column);
    printf("Enter row: ");
    scanf("%d", &row);
    modify_board(jeton, column, row);
    print_board();
    return 0;
}

void create_board()
{
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            board_value[i][j] = '1';
        }
    }
}

void print_board()
{

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {            
            printf("%c ", board_value[i][j]);
            if (j == BOARD_SIZE - 1)
            {
                printf("\n");
            }
        }
    }

}

void modify_board(char jeton, int column, int row)
{
    column--;
    row--;
    board_value[column][row] = jeton;
}
