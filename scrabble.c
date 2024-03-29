/*
//////////////////////////////////////////////////////////////////////
///////////////// Scrabble - Master MIMO - 2022/2023 /////////////////
////////////// Auteurs : Paula Ferreira et Lucas Leroux //////////////
//////////////////////////////////////////////////////////////////////
*/
#include <stdio.h>
#include "menu.c"
#include "coup.c"
#include "score.c"
#include "regles.c"
#include "echange.c"

/***** Programme principal ******/
int main()
{
    int action = 0;
    int joueur_actuel = 0;
    int nb_joueurs = MAX_JOUEUR;
    int tour_actuel = 0;
    int fin = 0;
    int quitte_echange = 3;
    int quitter_partie=0;

    printf("\n            S C R A B B L E\n\n");

    /* Initialisations */
    init_joueur(nb_joueurs);
    fiche_lettre();
    sac_lettres();
    creation_plateau();
    init_valeurs_plateau();

    /* Tirage au sort des lettres */
     premier_tour = 1;
     tirage(7, 0);

    /* Menu d'actions - Boucle du jeu - Le tour commence */
    while (fin == 0)
    {
        /* Affichage de lettres et du score du joueur en cours */
        printf("----------------------------------------\n");
        printf("Joueur actuel: %d\n", joueur_actuel + 1);
        affichage_lettre_joueur(joueur_actuel);
        printf("Score du joueur : %d\n", tabjoueur[joueur_actuel].score);
        affichage_plateau();
        action = actions();
        
        switch (action)
        {
        case 1:
            if (coup_partie(joueur_actuel, tour_actuel) == 1)
            {
                verification_sac();
                cpt_lettres_joueur(joueur_actuel);
                if ((sac_vide == 1) && (lettre_joueur_vide == 1))
                {
                    printf("La partie est terminée ! \n");
                    fin = fin_partie(0);
                }
                else
                {
                    joueur_actuel = changement_tour(joueur_actuel);
                    tour_actuel++;
                }
            }
            break;
        case 2:
            quitte_echange = echange(joueur_actuel);
            if (quitte_echange != 0)
            {
                joueur_actuel = changement_tour(joueur_actuel);
                if ((plateau[7][7].tuile != TUILE_STANDARD))
                {
                    tour_actuel++;
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
            joueur_actuel = changement_tour(joueur_actuel);
            break;
        case 4:
            regles_plateau();
            break;
        case 5:
            valeurs_lettre_main(joueur_actuel);
            break;
        case 6:
            printf("----------------------------------------\n");
            printf("Votre score total (joueur %d) est : %d\n", joueur_actuel + 1, tabjoueur[joueur_actuel].score);
            break;
        case 7:
            quitter_partie=1;
            fin = fin_partie(quitter_partie);
            quitter_partie=0;
            break;
        }
    }

    return 0;
}
