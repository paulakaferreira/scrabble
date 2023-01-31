#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LETTRE 27
#define TOTAL_JETON 102
#define MAX_JETON_TOUR 7
#define MAX_JOUEUR 2

// variables globales
char tabjeton[TOTAL_JETON];
int premier_tour = 1;
int sac_vide = 0;
int tour_echange = 0;

int verification_sac()
{
	int i, cpt = 0;
	for (i = 0; i < TOTAL_JETON; i++)
	{
		if (tabjeton[i] != '\0')
		{
			cpt++;
		}
	}
	if (cpt == 0)
	{
		sac_vide = 1;
	}

	return (cpt);
}

void tirage(int nb_jetons, int joueur_lu)
{
	time_t nb_secondes, tp;
	int alea, initialisation;
	int i = 0;
	int j;
	int cpt_joueur;
	int cpt_jeton = 0;
	int cpt_jeton_tire = 0;
	/* Pour la fonction aléatoire, récupération du nombre de seconde écoulée depuis 1970 */
	nb_secondes = time(&tp);
	/* Initialisation de la fonction aléatoire */
	initialisation = nb_secondes;
	srand(initialisation);
	alea = rand() % 102;
	// booléen premier tour, car au premier tour, toutes les lettres sont initialisés
	// donc comportement légérement différent. à la fin du tirage du premier tour
	// ce booléen passe à 0. Le booléen premier_tour doit impérativement être une variable
	// globale

	if (premier_tour == 1)
	{
		for (cpt_joueur = 0; cpt_joueur < MAX_JOUEUR; cpt_joueur++)
		{
			while (i < MAX_JETON_TOUR)
			{
				// vérification que la case du jeton sélectionné au hasard n'est pas vide
				if (tabjeton[alea] != '\0')
				{
					tabjoueur[cpt_joueur].jeton[i] = tabjeton[alea];
					// remplacement de la case tabjeton[alea] par un caractère vide
					tabjeton[alea] = '\0';
					// on reprend une autre valeur aléatoire
					alea = rand() % 102;
					// on incrémente le compteur i pour passer à la case suivante des caractères
					// que possède le joueur
					i++;
				}
				// si tabjeton[alea] est vide, on reprend un autre nombre aléatoire et on repasse dans la
				// boucle, sans incrémenter i.
				else
				{
					alea = rand() % 102;
				}
			}
			// à la sortie de cette boucle while, il faut repasser i à 0 pour parcourir les letttres
			// du joueur suivant
			i = 0;
		}
		premier_tour = 0;
	}
	else
	{
		while (i < nb_jetons)
		{
			verification_sac();
			// la fonction verification_sac renvoie un booléen. On vérifie ici que le sac
			// n'est pas vide (1 si vide, 0 si pas vide)
			if (sac_vide == 0)
			{
				// on vérifie ici si la case de caractères du joueur est vide ou pas avant
				// de tirer un nouveau jeton
				if ((tabjoueur[joueur_lu].jeton[cpt_jeton] == '\0'))
				{
					alea = rand() % 102;
					// on vérifie aussi que tabjeton[alea] contient bien un jeton; Sinon, on
					// reprend une autre valeur aléatoire
					if (tabjeton[alea] != '\0')
					{
						tabjoueur[joueur_lu].jeton[cpt_jeton] = tabjeton[alea];
						tabjeton[alea] = '\0';
						i++;
						cpt_jeton++;
						alea = rand() % 102;
						// cpt_jeton_tire permet de compter le nb de jetons remplacés.
						// à ne pas confondre avec cpt_jeton qui permet de parcourir le tableau
						// de jetons possédés par le joueur
						cpt_jeton_tire++;
					}
					else
					{
						alea = rand() % 102;
					}
				}
				else
				{
					// si [cpt_jeton]du joueur est pas vide, on vérifie si la case suivante est vide
					cpt_jeton++;
				}
			}
			else
			// cas où le sac est vide
			{
				printf("Le sac de lettre est vide. il est impossible de piocher plus de jetons.\n");
				// on met i au nombre de jetons demandés pour sortir de la boucle définitivement
				i = nb_jetons;
				for (j = 0; j < MAX_JETON_TOUR; j++)
				{
					if (tabjoueur[joueur_lu].jeton[j] == '\0')
					{
						tabjoueur[joueur_lu].jeton[j] = '\\';
					}
				}
			}
		}
		if ((cpt_jeton_tire == 7) && (tour_echange == 0))
		{
			printf("S C R A B B L E :\n");
			printf("Félicitations ! Vous avez joué en un tour tous les jetons de votre jeu. Vous remportez un bonus de 50 points.\n");
			tabjoueur[joueur_lu].score += 50;
			printf("Score du joueur %d : %d\n", tabjoueur[joueur_lu].id_joueur, tabjoueur[joueur_lu].score);
		}
		else
		{
			tour_echange = 0;
		}
		if (cpt_jeton_tire != 0)
		{
			printf("Tirage au sort: vous avez tiré %d jetons du sac\n", cpt_jeton_tire);
			printf("Le(s) jeton(s) ont été ajoutés à votre main\n");
		}
	}
}
