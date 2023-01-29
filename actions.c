#include <stdio.h>

#define MAX_ACTION 6

int actions()
{
    int action = 0;
    int saisie_ok = 0;

    printf("----------------------------------------\n");
    printf("Quelle action souhaitez-vous réaliser ? \n");
    printf("1 - Placer un mot\n");
    printf("2 - Échanger mes tuiles contre de nouvelles\n");
    printf("3 - Passer\n");
    printf("4 - Voir les règles du plateau\n");
    printf("5 - Regarder les valeurs des lettres\n");
    printf("6 - Afficher mon score\n");
    printf("----------------------------------------\n");
    printf("Veuillez saisir votre option : ");
    saisie_ok = scanf("%d", &action);

    while (((action < 1) || (action > MAX_ACTION)) || (saisie_ok == 0))
    {

        if (saisie_ok == 0)
        {
            printf("Erreur de saisie : veuillez saisir une action valide (1-6) : ");
            while ((action = getchar()) != '\n')
                ;
            saisie_ok = scanf("%d", &action);
        }
        else if ((action < 1) || (action > MAX_ACTION))
        {
            printf("Option erronée\n");
            printf("Veuillez saisir un numéro entre 1 et 6 :");
            while ((action = getchar()) != '\n')
                ;
            saisie_ok = scanf("%d", &action);
        }
    }

    return action;
}