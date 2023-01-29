#include <stdio.h>

void board_rules()
{
    printf(" -------Règles du plateau-------\n\n");
    printf("Cases spéciales :\n");
    printf("Les cases '#' duplient la valeur du mot;\n");
    printf("Les cases '@' triplient la valeur du mot;\n");
    printf("Les cases '*' duplient la valeur de la lettre placée dessus\n");
    printf("Les cases '&' triplient la valeur de la lettre placé dessus\n");
    printf("Les cases '.' n'ont aucune valeur spéciale\n");
    printf("Une fois utilisées, les cases spéciales perdront leur valeur spéciale.\n");
}