#include <stdio.h>

int actions()
{
    int action = 0;
    while ((action < 1) || (action > 5))
    {
        printf("Quelle action souhaitez-vous réaliser ? \n");
        printf("1 - Placer un mot;\n");
        printf("2 - Échanger mes tuiles contre de nouvelles;\n");
        printf("3 - Passer\n");
        printf("4 - Voir les règles du plateau\n");
        printf("5 - Regarder les valeurs des lettres\n");
        printf("Veuillez saisir votre option : ");
        scanf("%d", &action);

        if ((action < 1) || (action > 5))
        {
            printf("Option erronée\n");
            printf("Veuillez saisir un numéro entre 1 et 3.\n");
        }
        // Still needs to check if the caracter is an actual number. Otherwise we get an infinite loop.
    }

    return action;
}