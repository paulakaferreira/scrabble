#include <stdio.h>

void board_rules()
{
    printf(" -------Règles du plateau-------\n\n");
    printf("Cases spéciales :\n");
    printf("Les cases '#' dupliquent la valeur du mot;\n");
    printf("Les cases '@' tripliquent la valeur du mot;\n");
    printf("Les cases '*' duplique la valuer de la lettre placé dessus\n");
    printf("Les cases '*' tripliquent la valuer de la lettre placé dessus\n");
    printf("Les cases '.' n'ont aucune valeur spéciale\n\n");
    printf("Une fois utilisées, les cases spéciales perdront leur valeur spéciale.\n");
}

void hand_rules()
{
    // to do : print hand rules. eg. dire que 0 est un jeton sans valeur.
}

void print_letter_value()
{
    // to do: renvoie les valeurs de chaque lettre qui sont à la main du joueur;
}