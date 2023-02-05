#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joueur.c"
#include "lettres.c"

/**** Vérifie que les lettres saisies sont à la possession du joueur ****/
int verif_lettres(int choix_joueur)
{
	int lettre = 'v';
	int i;
	int j = 0;
	int trouve = 0;
	int cpt = 0;						  // compteur pour vérifier que l'utilisateur n'a pas entré plus de 7 lettres
	char tab_jeton_tempo[MAX_JETON_TOUR]; // Variable locale représentant le nombre de jetons du joueur.

	// initialisation de la chaîne chaine_lettres_lues
	for (i = 0; i < MAX_JETON_TOUR; i++)
	{
		chaine_lettres_lues[i] = '\0';
	}

	i = 0;

	// saisie de chaine_lettres_lues

	if ((lettre = getchar()) != '\n') // pour éviter des problèmes de buffer, si \n est toujours dans le buffer
	{
		if (lettre == '1')
		{
			return 2; // si lecture de "1", alors on quitte le menu d'échange
		}
		lettre = toupper(lettre);
		chaine_lettres_lues[i] = lettre; // si \n n'est pas dans le buffer, alors il faut stocker la première lettre saisie directement avant de continuer
		i++;
		cpt++;
		while ((lettre = getchar()) != '\n')
		{
			if (lettre != ' ') // si la lettre lue n'est pas un espace, on stocke la lettre dans chaine_lettre_lue
			{
				lettre = toupper(lettre);
				chaine_lettres_lues[i] = lettre;
				i++;
				cpt++;
			}
		}
	}

	else // si le caractère '\n' n'est pas dans le buffer, on range les lettres saisies dans la variable chaine_lettre_lue
	{
		while ((lettre = getchar()) != '\n')
		{
			if (lettre == '1') // pour quitter le menu si 1 est saisi
			{
				return 2;
			}
			if (lettre != ' ')
			{
				lettre = toupper(lettre);
				chaine_lettres_lues[i] = lettre;
				i++;
				cpt++;
			}
		}
	}

	// si cpt est supérieur au nombre max de jeton
	if (cpt > MAX_JETON_TOUR)
	{
		printf("Erreur : vous avez entré un nombre de lettres supérieur aux jetons que vous possédez.\n");
		chaine_lettres_lues[7] = '\0'; // on enlève la lettre résiduelle sinon elle reste
		return trouve;
	}

	else
	{

		strcpy(tab_jeton_tempo, tabjoueur[choix_joueur].jeton); // pour comparer les lettres, utilisation d'une copie de la main du joueur
		for (i = 0; chaine_lettres_lues[i] != '\0'; i++)		// parcours de chaine_lettre_lue jusqu'à '\0' qui correspond à une fin de saisie
		{
			if (chaine_lettres_lues[i] != '\0')
			{
				trouve = 0;
				// à chaque lettre qu'on commence à vérifier, on remet trouve à 0
				// pour vérifier que la lettre est bien dans la main du joueur
				// si toutes les lettres sont bien en possession du joueur, on ne repassera pas dans ce if
				// et trouve restera à 1
			}
			for (j = 0; j < MAX_JETON_TOUR; j++)
			{
				if (tab_jeton_tempo[j] == chaine_lettres_lues[i])
				{
					trouve = 1;
					tab_jeton_tempo[j] = '\0'; // Suprression de la lettre du joueur dans tab_jeton_tempo pour éviter qu'elle soit relue par la suite
					j = MAX_JETON_TOUR;		   // sortie de la boucle car la lettre est trouvée
				}
			}

			if (trouve == 0) // Si une lettre n'a pas été trouvé, on sort de la boucle directement et la fonction renvoie trouve=0
			{
				printf("La lettre %c n'est pas dans votre jeu.\n", chaine_lettres_lues[i]);
				return (trouve);
			}
		} // sortie boucle for

		if (trouve == 1)
		{
			printf("Toutes les lettres entrées sont bien en votre possession.\n");
		}

	} // sortie du else

	return trouve;
}

/**** Remise des lettres dans le sac ****/
void remise(int lettre_remise)
{
	int i = 0;

	// cette fonction permet au joueur de rentrer les lettres qu'il veut échanger. ces lettre sont vérifiées, et échangées avec des lettres aléatoires
	// Les lettres dont le joueur se débarasse sont remises dans le sac après le tirage des nouvelles lettres.

	while (tabjeton[i] != '\0')
	{
		i++;
	}

	tabjeton[i] = lettre_remise;
}

/**** Échange des lettres  ****/
int echange(int choix_joueur)
{
	int i = 0, j = 0, cpt_jeton = 0;
	int trouve = 0;
	int lettres_ok;
	int compteur_sac;
	tour_echange = 1;

	compteur_sac = verification_sac();
	if (compteur_sac < 7)
	{
		printf("échange impossible : Il y a moins de 7 lettres dans le sac.\n");
		return 0;
	}

	else
	{
		printf("Quelles lettres souhaitez-vous remettre dans le sac ? : (1 pour annuler) : ");

		// appel à la fonction verif_lettres qui permettra à l'utilisateur de saisir des lettres
		// dont le programme vérifiera qu'elles correspondent aux lettres qu'il possède

		lettres_ok = verif_lettres(choix_joueur);
		if (lettres_ok == 2)
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
			if (lettres_ok == 2)
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
		tour_echange = 0;

	} // fermeture du else (si compteur_sac est égal ou supérieur à 7)
}