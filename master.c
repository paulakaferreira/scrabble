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
    int n_players = MAX_JOUEUR; // to do: let the player decide the number of players.
    int current_turn = 0;
    int fin = 0;
    int quitte_echange=3;

    printf("\n            S C R A B B L E\n\n");

    /* Initialisations */
    init_joueur(n_players);
    fiche_lettre();
    sac_lettres();
    create_board();
    set_board_value();

    /* Tirage au sort des lettres */
    for (int i = 0; i < n_players; i++)
    {
        premier_tour = 1;
        tirage(7, i);
    }

    print_board(); // pour tester l'initialisation des valeurs: print_board_value();

    /* Menu d'actions - Boucle du jeu - Le tour commence */
    while (fin == 0)
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
            quitte_echange=echange(current_player);
            if(quitte_echange!=0)
            {
              current_player = change_turn(current_player);
              if ((board[7][7].tile != DEFAULT_TILE))
              {
                  current_turn++;
              }
              break;
            }
            else
            {
              break;
            }
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
        case 6:
            printf("----------------------------------------\n");
            printf("Votre score total (joueur %d) est : %d\n", current_player + 1, tabjoueur[current_player].score);
            break;
        case 7:
            fin_partie();
            fin = 1;
            break;
        }
    }

    return 0;
}
