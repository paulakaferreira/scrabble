#include <stdio.h>
#include "actions.c"
#include "move.c"
#include "score.c"
#include "rules.c"
#include "exchange.c"

int main()
{
    int action = 0;
    int current_player = 0;
    int n_players = 2; // to do: let the player decide the number of players.
    int current_turn = 0;

    printf("\n            S C R A B B L E\n\n");

    /* Initialisations */
    init_joueur(n_players);
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
        printf("----------------------------------------\n");
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
                verification_sac();
                cpt_lettres_joueur(current_player);
                if ((sac_vide == 1) && (lettre_joueur_vide == 1))
                {
                    printf("La partie est terminée ! \n");
                    fin_partie();
                }
                else
                {
                    current_player = change_turn(current_player);
                    current_turn++;
                }
            }
            break;
        case 2:
            echange(current_player);
            current_player = change_turn(current_player);
            if (board[7][7].tile != DEFAULT_TILE)
            {
                current_turn++;
            }
            break;
        case 3:
            printf("Vous avez décidé de passer votre tour\n");
            printf("----------------------------------------\n");
            current_player = change_turn(current_player);
            break;
        case 4:
            board_rules();
            break;
        case 5:
            valeurs_lettre_main(current_player);
            break;
        }
    }

    return 0;
}
