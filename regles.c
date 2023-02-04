#include <stdio.h>

/****** Régles du plateau *****/
void regles_plateau()
{
    printf(" -------Règles du plateau-------\n\n");
    printf("Cases spéciales :\n");
    printf("Les cases '#' doublent la valeur du mot;\n");
    printf("Les cases '@' triplent la valeur du mot;\n");
    printf("Les cases '*' doublent la valeur de la lettre placée dessus\n");
    printf("Les cases '&' triplent la valeur de la lettre placée dessus\n");
    printf("Les cases '.' n'ont aucune valeur spéciale\n");
    printf("Une fois utilisées, les cases spéciales perdront leur valeur spéciale.\n");
}
