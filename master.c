#include <stdio.h>
#include "saclettre.c"
#include "actions.c"
#include "move.c"

int main()
{
    int action = 0;
    int current_player = 0;
    int current_turn = 0;
    int turn = 0;

    printf("            S C R A B B L E\n");

    /* Initialisations */
    init_joueur();
    fiche_lettre();
    sac_lettres();
    create_board();
    set_board_value();

    /* Tirage au sort des lettres */
    tirage(7, 0);

    print_board(); // pour tester l'initialisation des valeurs: print_board_value();

    /* Menu d'actions - Boucle du jeu - Le tour commence */
    while (1)
    {
        /* Affichage de lettres du joueur en cours */
        printf("Joueur actuel: %d\n", current_player + 1);
        affichage_lettre_joueur(current_player);

        action = actions();
        switch (action)
        {
        case 1:
            if (get_move(current_player, current_turn) == 1)
            {
                // To do: ajouter une fonction de calcul après la validation du mot;
                print_board();
                current_player = change_turn(current_player);
                turn++;
            }
            break;
        case 2:
            // To do: import from exchange.c and make sure it works
            current_player = change_turn(current_player);
            printf("Joueur actuel: %d\n", current_player + 1);
            break;
        case 3:
            printf("Vous avez dédicé de passer votre tour\n");
            current_player = change_turn(current_player);
            printf("Joueur actuel: %d\n", current_player + 1);
            break;
        }
    }

    return 0;
}