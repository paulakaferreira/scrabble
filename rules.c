#include <stdio.h>

void board_rules()
{
    printf(" -------Règles du plateau-------\n\n");
    printf("Cases spéciales :\n");
    printf("Les cases '#' duplient la valeur du mot;\n");
    printf("Les cases '@' triplient la valeur du mot;\n");
    printf("Les cases '*' duplient la valeur de la lettre placée dessus\n");
    printf("Les cases '*' triplient la valeur de la lettre placé dessus\n");
    printf("Les cases '.' n'ont aucune valeur spéciale\n");
    printf("Une fois utilisées, les cases spéciales perdront leur valeur spéciale.\n");
}

void valeurs_lettre_main(int current_player)
{
    char lettre_lue = '\0';
    int indice_lettre = 0;
    int point = 0;
    printf(" -------Valeurs dans votre main-------\n\n");
    for (int i = 0; i < MAX_JETON_TOUR; i++)
    {
        lettre_lue = tabjoueur[current_player].jeton[i];
        if (lettre_lue == '0')
        {
            indice_lettre = MAX_LETTRE - 1;
        }
        else
        {
            indice_lettre = lettre_lue - 'A';
        }

        point = tablettre[indice_lettre].nbpoint;

        if (point > 1)
        {
            printf("Lettre %c: %d points\n", lettre_lue, point);
        }
        else
        {
            printf("Lettre %c: %d point\n", lettre_lue, point);
        }
    }
}