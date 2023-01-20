#include <stdio.h>
#include "player.c"
#include "saclettre.c"
#include "tirage.c"
#include "board.c"
#include "actions.c"


int main()
{
    int action = 0;
    int current_player = 0;

    printf("            S C R A B B L E\n");
    
    /* Initialisations */
    init_joueur();
    fiche_lettre();
    sac_lettres();
    create_board();
    set_board_value();

    /* Tirage au sort des lettres */
    tirage(7, 0);

    /* Affichage de lettres pour le joueur 1 */
    affichage_lettre_joueur(current_player);

    print_board(); //pour tester l'initialisation des valeurs: print_board_value();

    /* Menu d'actions */
    action = actions();
    
    return 0;

}