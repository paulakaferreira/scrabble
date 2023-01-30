#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "player.c"
#include "saclettre.c"
#include "check_letters.c"

// variables globales
char chaine_lettres_lues[MAX_JETON_TOUR]; // une variable globale qui va nous permettre de stocker les lettres lues
// les comparer avec les lettres possédées et puis faire l'opération de remplacement de lettres

// cette fonction permet au joueur de rentrer les lettres qu'il veut échanger. ces lettre sont vérifiées, et échangées avec des lettres aléatoires
// Les lettres dont le joueur se débarasse sont remises dans le sac après le tirage des nouvelles lettres.

void remise(int lettre_remise)
{
	int i = 0;

	while (tabjeton[i] != '\0')
	{
		i++;
	}

	tabjeton[i] = lettre_remise;
}

int echange(int choix_joueur)
{
	char lettre;
	int i = 0, j = 0, cpt_jeton = 0, k;
	char jeton;
	int trouve = 0;
	int lettres_ok;
	int compteur_sac;
	tour_echange=1;

	compteur_sac = verification_sac();
	if (compteur_sac < 7)
	{
		printf("échange impossible : Il y a moins de 7 lettres dans le sac.\n");
	}

	else
	{
		printf("Quelles lettres souhaitez-vous remettre dans le sac ? : (1 pour annuler) : ");

		// appel à la fonction verif_lettres qui permettra à l'utilisateur de saisir des lettres
		// dont le programme vérifiera qu'elles correspondent aux lettres qu'il possède

		lettres_ok = verif_lettres(choix_joueur);
	        if (lettres_ok==2)
	        {
		  printf("Vous avez quitté le menu d'échange.\n");
		  return 0;
		}

		// cette boucle va permettre de lire toutes les lettres entrées par l'utilisateur
		// et enregistrées dans le tableau chaine_lettre
		// jusqu'à arriver à une case vide

		while (lettres_ok == 0)
		{
			printf("Les lettres que vous avez saisies n'ont pas été reconnues.\n");
			printf("Veuillez saisir des lettres en votre possession (1 pour annuler).\n");
			affichage_lettre_joueur(choix_joueur);
			printf("Quelles lettres souhaitez-vous remettre dans le sac ? : ");
			lettres_ok = verif_lettres(choix_joueur);
			if (lettres_ok==2)
			{
			  printf("Vous avez quitté le menu d'échange.\n");
			  return 0;
			}
		}

		for (i = 0; chaine_lettres_lues[i] != '\0'; i++)
		{
			// tant que la lettre entrée n'a pas été trouvée parmi les lettres du joueur, on ne
			// sort pas de la boucle. qaudn la lettre a été trouvée, le booléen trouve est
			// mis à 1. à la sortie de la boucle, le booléen trouve est remis à 0 pour pouvoir
			// y entrer à nouveau lorsqu'une nouvelle lettre sera traitée

			while (trouve != 1)
			{
				// si la variable lettre lue est égale à l'un des caractères possédés par le joueur
				// alors les lettres sont échangées grâce à la fonction de tirage spécifique à l'échabnge
				if (chaine_lettres_lues[i] == tabjoueur[choix_joueur].jeton[j])
				{
					printf("Lettre %c remise dans le sac\n", tabjoueur[choix_joueur].jeton[j]);
					tabjoueur[choix_joueur].jeton[j] = '\0';
					trouve = 1;
					cpt_jeton++;
				}
				// si le caractère [i] du joueur n'est pas le même que la lettre lue, on passe au
				// caractère suivant
				else
				{
					j++;
				}
			}
			// on remet trouve et le compteur j à 0 pour pouvoir repasser dans la boucle while après
			// et rescanner toutes les lettres
			trouve = 0;
			j = 0;
		}

		printf("Vous avez remis %d jetons dans le sac.\n", cpt_jeton);
		tirage(cpt_jeton, choix_joueur);
	
		for (i = 0; chaine_lettres_lues[i] != '\0'; i++)
		{
			remise(chaine_lettres_lues[i]);
		}

		printf("Voici votre nouveau set de lettres : ");
		for (i = 0; i < MAX_JETON_TOUR; i++)
		{
			printf("%c ", tabjoueur[choix_joueur].jeton[i]);
		}
		printf("\n");
		tour_echange=0;

	} // fermeture du else (si compteur_sac est égal ou supérieur à 7)
	
}
