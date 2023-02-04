#include <stdio.h>
#include <string.h>
#include "joueur.c"
#include "plateau.c"
#include "score.c"
#include "tirage.c"

#define TUILE_STANDARD '.'

#define MAX_JETON_TOUR 7
char lettre_joker(char joker, int cpt_joker, int joueur);
int check_board_new_word(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, char direction, int joueur_actuel);
void score_mots_modif(char verif_mot[TAILLE_PLATEAU], int colonne, int ligne, int direction, int joueur);
int verif_depassement_tableau(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, char direction);
struct Carre copie_plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];

/** Verifie la compatibilité du mot saisie avec les tuiles qui sont à la main du joueur **/
int verif_compatibilite_main(char mot_lu[MAX_JETON_TOUR], int joueur_actuel)
{
  char copie_main[MAX_JETON_TOUR];
  int nb_lettres_supprimees = 0;

  // Initialise une copie de la main de joueur.
  strcpy(copie_main, tabjoueur[joueur_actuel].jeton);

  for (int i = 0; i < strlen(mot_lu); i++)
  {
    int trouve = 0;
    for (int j = 0; j < MAX_JETON_TOUR; j++)
    {
      if (mot_lu[i] == TUILE_STANDARD)
      {
        trouve = 1;
        break;
      }
      else if (mot_lu[i] == copie_main[j])
      {
        copie_main[j] = '\0';
        trouve = 1;
        break;
      }
    }
    if (trouve == 0)
    {
      for (int j = 0; j < MAX_JETON_TOUR; j++)
      {
        if (copie_main[j] == '0')
        {
          copie_main[j] = '\0';
          mot_lu[i] = tolower(mot_lu[i]); // on met la lettre en minuscule pour pouvoir identifier le joker
          trouve = 1;
          break;
        }
      }
      if (trouve == 0)
      {
        return 0;
      }
    }
  }

  for (int i = 0; i < MAX_JETON_TOUR; i++)
  {
    tabjoueur[joueur_actuel].jeton[i] = copie_main[i];
    if (copie_main[i] == '\0')
    {
      nb_lettres_supprimees++;
    }
  }
  return nb_lettres_supprimees;
}

/** Verifie la compatibilité du mot saisie avec le tableau **/
// Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
int verif_compatibilite_tableau(int colonne, int ligne, char direction, char mot_lu[TAILLE_PLATEAU], int tour)
{
  int i = 0;
  int intersection = 0;
  int milieu_tableau = 0;
  int haut = 0;
  int bas = 0;
  int droite = 0;
  int gauche = 0;

  for (i = 0; i < strlen(mot_lu); i++)
  {
    if (plateau[ligne][colonne].tuile != mot_lu[i] && plateau[ligne][colonne].tuile != TUILE_STANDARD)
    {
      if (mot_lu[i] == toupper(plateau[ligne][colonne].tuile))
      {
        mot_lu[i] = TUILE_STANDARD;
        intersection = 1;
      }
      else
      {
        return 0;
      }
    }
    // Intersection avec un autre mot
    else if (plateau[ligne][colonne].tuile != TUILE_STANDARD)
    {
      mot_lu[i] = TUILE_STANDARD;
      intersection = 1;
    }

    // on vérifie maintenant si le mot est adjacent à un mot déjà posé
    // si la ligne n'est pas égale à 0, on vérifie la case au-dessus du mot
    if (ligne > 0)
    {
      haut = ligne - 1;
    }

    // si la ligne est inférieure à 14, on vérifie la case en dessous du mot
    if (ligne < 14)
    {
      bas = ligne + 1;
    }

    // on vérifie de même la colonne suivante, sauf si elle est égale à 15 (dépasse le tableau)
    droite = colonne + 1;
    if (droite == 15)
    {
      droite = 14;
    }

    // de même pour la colonne de gauche qui ne doit pas aller en-deça de 0.
    gauche = colonne - 1;
    if (gauche == (-1))
    {
      gauche = 0;
    }

    // si l'une des cases sélectionnées contient un jeton, alors la pose est valide. Nous utilisons le même booléen pour l'intersection pour simplifier le traitement
    if ((plateau[bas][colonne].tuile != TUILE_STANDARD) || (plateau[haut][colonne].tuile != TUILE_STANDARD) || (plateau[ligne][gauche].tuile != TUILE_STANDARD) || (plateau[ligne][droite].tuile != TUILE_STANDARD))
    {
      intersection = 1;
    }

    // Milieu du tableu
    if ((colonne == 7) && (ligne == 7))
    {
      milieu_tableau = 1;
    }

    // Fait avancer la boucle
    if (direction == 'H')
    {
      colonne++;
    }
    else
    {
      ligne++;
    }
  }
  // Verifie la condition du premier tour : le mot doit passer par le milieu tu tableau
  if ((milieu_tableau == 0) && (tour == 0))
  {
    printf("Vous êtes au premier tour et votre mot ne passe pas par le milieu du tableau\n");
    return 0;
  }
  // Verifie la condition des tours suivants : le mot doit croiser un mot existant
  if ((intersection == 0) && (tour != 0))
  {
    printf("Attention à la règle du scrabble : votre mot doit croiser ou toucher un mot existant sur le plateau\n");
    printf("Les lettres qui se touchent doivent aussi former un mot valide dans le dictionnaire\n");
    return 0;
  }
  return 1;
}

/*** Ajout du mot validé au plateau ***/
void modif_plateau(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, char direction)
{
  for (int i = 0; i < strlen(mot_lu); i++)
  {
    if (mot_lu[i] != TUILE_STANDARD)
    {
      if (mot_lu[i] <= 'Z')
      {
        plateau[ligne][colonne].tuile = toupper(mot_lu[i]);
      }
      else
      {
        plateau[ligne][colonne].tuile = mot_lu[i];
      }
    }

    // Fait avancer la boucle en fonction de la direction
    if (direction == 'H')
    {
      colonne++;
    }
    else
    {
      ligne++;
    }
  }
  printf("Votre mot a été ajouté au plateau\n");
}

// Demande au joueur de jouer son tour
// Fonction principale qui appelle les fonctions de compatibilité et de modification du tableau
int coup_partie(int joueur_actuel, int tour)
{
  int i = 0;
  char mot_lu[TAILLE_PLATEAU];
  char direction;
  char column_letter = '\0';
  int colonne = 0;
  int ligne = 0;
  int nb_lettres_supprimees = 0;
  int ligne_ok = 0;
  int cpt_joker = 0;

  printf("Vouz avez decidé d'ajouter un mot au tableau. \n");
  for (i = 0; i < TAILLE_PLATEAU; i++)
  {
    mot_lu[i] = '\0';
  }

  while (in_dic(mot_lu) == 0)
  {
    printf("Entrez le mot à ajouter au tableau (1 pour retourner au menu) : ");
    scanf("%s", mot_lu);
    for (i = 0; i < TAILLE_PLATEAU; i++) // boucle for qui lit le nombre de joker saisi et les traite en appelant la fonction lettre_joker
    {
      if (mot_lu[i] == '0')
      {
        cpt_joker++;
        if (cpt_joker <= 2)
        {
          if ((mot_lu[i] = lettre_joker(mot_lu[i], cpt_joker, joueur_actuel)) == 0)
          {
            if (cpt_joker == 1)
            {
              printf("Vous n'avez pas de joker.\n");
            }
            else if (cpt_joker == 2)
            {
              printf("Vous n'avez plus assez de jokers\n");
            }
            cpt_joker = 0;
            return 0;
          }
        }
        else
        {
          printf("Erreur : vous avez saisi au moins %d jetons jokers. Or, il n'en existe que deux dans tout le jeu.\n", cpt_joker);
          printf("Veuillez revérifier votre saisie.\n");
          cpt_joker = 0;
          return 0;
        }
      }
    }
    // Retour au menu
    if (strcmp(mot_lu, "1") == 0)
    {
      return 0;
    }
    else
    {
      for (i = 0; i < strlen(mot_lu); i++)
      {
        mot_lu[i] = toupper(mot_lu[i]);
      }
      if (in_dic(mot_lu) == 0)
      {
        printf("----------------------------------------\n");
        printf("Le mot que vous avez écrit n'est pas dans notre dictionnaire\n");
        printf("Merci d'entrer un mot valide.\n");
      }
    }
  }

  printf("----------------------------------------\n");
  printf("Le mot est valide \n");
  printf("Vous allez saisir maintenant les coordonées du tableau\n");

  if (tour == 0)
  {
    printf("Attention: pour le premier tour, le mot doit passer impérativement par le milieu du tableau\n");
  }

  printf("Entrez le numéro de la ligne où la première lettre du mot apparaitra (1 - 15): ");
  ligne_ok = scanf("%d", &ligne);
  // Verification de saisie de la ligne
  while (((ligne < 1) || (ligne > 15)) || (ligne_ok == 0))
  {

    if (ligne_ok == 0)
    {
      printf("Erreur de saisie : veuillez saisir une ligne valide (1-15) : ");
      while ((ligne = getchar()) != '\n')
        ;
      ligne_ok = scanf("%d", &ligne);
    }
    else
    {
      if ((ligne < 1) || (ligne > 15))
      {
        printf("Numéro de ligne invalide : veuilez saisir un numéro de ligne entre 1 et 15 : ");
        while ((ligne = getchar()) != '\n')
          ;
        ligne_ok = scanf("%d", &ligne);
      }
    }
  }

  // Verification de saisie de la colonne
  printf("Entrez la lettre de la colonne où la première lettre du mot apparaitra (A - O): ");
  scanf(" %c", &column_letter);
  colonne = toupper(column_letter);
  colonne = colonne - 'A' + 1;
  while ((colonne < 1) || (colonne > 15))
  {
    printf("Erreur de saisie : veuillez saisi une colonne valide (A - O) :");
    while ((column_letter = getchar()) != '\n')
      ;
    scanf(" %c", &column_letter);
    colonne = toupper(column_letter);
    colonne = colonne - 'A' + 1;
  }

  printf("Entrez la direction du mot (H pour horizontal et V pour vertical) : ");
  scanf(" %c", &direction);
  direction = toupper(direction);

  while ((direction != 'H') && (direction != 'V'))
  {
    printf("Erreur de saisie : entrez la direction du mot (H pour horizontal et V pour vertical) : ");
    while ((direction = getchar()) != '\n')
      ;
    scanf(" %c", &direction);
    direction = toupper(direction);
  }

  colonne--;
  ligne--;

  if ((verif_depassement_tableau(mot_lu, colonne, ligne, direction)) == 0)
  {
    printf("Erreur : votre mot dépasse le tableau !\n");
    return 0;
  }

  if (check_board_new_word(mot_lu, colonne, ligne, direction, joueur_actuel) == 0)
  {
    printf("Le mot que vous avez saisi interfère de façon invalide avec d'autres mots\n");
    temp_score = 0;
    return 0;
  }

  // Verifie la compatibilité du mot avec le tableau;
  // Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
  if (verif_compatibilite_tableau(colonne, ligne, direction, mot_lu, tour) == 1)
  {
    printf("----------------------------------------\n");

    nb_lettres_supprimees = verif_compatibilite_main(mot_lu, joueur_actuel);

    // Verifie la compatibilité du mot avec le main du joueur
    if (nb_lettres_supprimees == 0)
    {
      printf("----------------------------------------\n");
      printf("Les lettres saisies ne sont pas compatibles avec votre main\n");
      printf("Retour au menu. Veuillez choisir une autre option ou réessayer.\n");
      return 0;
    }
  }
  else
  {
    printf("----------------------------------------\n");
    printf("Les directions ne sont pas compatibles avec le tableau\n");
    printf("Impossible d'ajouter le mot %s à l'endroit souhaité\n", mot_lu);
    printf("Retour au menu. Veuillez saisir une autre option ou ressayer\n");
    return 0;
  }

  // Modifie le tableau après validation
  modif_plateau(mot_lu, colonne, ligne, direction);

  // Change le score du joueur en cours
  printf("----------------------------------------\n");
  get_player_score(mot_lu, colonne, ligne, direction, joueur_actuel);
  printf("----------------------------------------\n");
  printf("Nombre de lettres à modifier dans votre main: %d\n", nb_lettres_supprimees);

  // Fait le tirage au sort pour le joeur actuel
  printf("----------------------------------------\n");
  tirage(nb_lettres_supprimees, joueur_actuel);
  return 1;
}

int check_board_new_word(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, char direction, int joueur_actuel)
{
  /* cette fonction permet de vérifier les mots nouveaux formés à partir de lettres déjà existantes sur le plateau
  Elle fonctionne en créant une copie du plateau, en posant le mot joué par le joueur, et en vérifiant la validité
  des mots formés sur le plateau */

  int i = 0;
  int j = 0;
  int k;
  char verif_mot[TAILLE_PLATEAU];
  int cpt = 0;
  int cpt_score = 0;
  char direction_mot;
  char copie_verif_mot[TAILLE_PLATEAU];
  int fin;

  // intialisation de verif_mot
  for (i = 0; i < TAILLE_PLATEAU; i++)
  {
    verif_mot[i] = '\0';
  }

  // copie du plateau de jeu
  for (i = 0; i < TAILLE_PLATEAU; i++)
  {
    for (j = 0; j < TAILLE_PLATEAU; j++)
    {
      copie_plateau[i][j] = plateau[i][j];
    }
  }

  //
  for (i = 0; i < strlen(mot_lu); i++) // ajout du mot au plaetau
  {
    if (mot_lu[i] != TUILE_STANDARD) // si la lettre saisie ne correspond pas à tuile_standard
    {
      if (mot_lu[i] <= 'Z') // si la lettre saisie est <= 'Z' (donc pas un joker qui est supérieur à Z)
      {
        if (mot_lu[i] == toupper(copie_plateau[ligne][colonne].tuile)) // si la lettre est déjà présente sur le plateau, on ne fait rien
        {
        }
        else
        {
          copie_plateau[ligne][colonne].tuile = toupper(mot_lu[i]); // Si la lettre est pas déjà présente sur le plateau, on la met sur le plateau
        }
      }
    }

    // Fait avancer la boucle en fonction de la direction
    if (direction == 'H')
    {
      colonne++;
    }
    else
    {
      ligne++;
    }
  }

  // le mot a été ajouté à la copie du plateau
  // maintenant il va s'agir de lire chaque colonne du tableau et de valider le mot ou non
  for (colonne = 0; colonne < TAILLE_PLATEAU; colonne++)
  {
    for (ligne = 0; ligne < TAILLE_PLATEAU; ligne++) // parcours colonne par colonne, grâce au compteur ligne qui augmente jusqu'à < TAILLE_PLATEAU
    {
      fin = 0; // remise à 0 du booléen fin qui permet au if suivant de ne pas prendre en compte le cas où la ligne est égale à 15 (TAILLE_PLATEAU)
      if ((copie_plateau[ligne][colonne].tuile != TUILE_STANDARD) && (fin == 0))
      {
        j = 0;                                                                                      // initialise le compteur J qui permettre de parcourir verif_mot
        cpt = 0;                                                                                    // permet de compter la taille du mot. Si la lettre est toute seule, cpt=1, et donc ce n'est pas un mot
        while ((copie_plateau[ligne][colonne].tuile != TUILE_STANDARD) && (ligne < TAILLE_PLATEAU)) // tant que ligne ne dépasse pas TAILLE_PLATEAU et que la tuile est différente de la tuile par défaut, on continue à ranger les lettres lues dans verif_mot
        {
          verif_mot[j] = copie_plateau[ligne][colonne].tuile;
          if (toupper(copie_plateau[ligne][colonne].tuile) == toupper(plateau[ligne][colonne].tuile))
          {
            cpt_score++; // vérification du nb de lettres qui sont déjà présentes sur l'ancien plateau
            // pour vérifier si le mot est nouveau ou si c'est déjà un mot posé qui n'a pas changé qui n'est donc pas àvérifier
          }
          j++;     // on incrémente j pour passer à l'indice suivant de verif_mot
          ligne++; // on passe à a ligne suivante
          cpt++;   // taille du mot
        }

        strcpy(copie_verif_mot, verif_mot); // pour vérifier les mots dans le dico, on fait une copie. ça permet de conserver les lettres en minuscule
        // lors du calcul du score

        for (k = 0; k < (strlen(copie_verif_mot)); k++)
        {
          copie_verif_mot[k] = toupper(copie_verif_mot[k]); // passage du mot en majuscule
        }

        if ((in_dic(verif_mot) == 0) && (cpt > 1))
        {
          printf("Le mot %s n'existe pas\n", verif_mot); // si un mot lu n'existe pas, on arrête tout et la saisie est impossible
          return 0;
        }

        // ce else if permet d'éviter de lire un mot qui n'a été modifié par le coup du joueur
        // et d'éviter de lire le mot qui vient d'être saisi par le joueur
        // et d'éviter de lire une lettre isolée
        // ou de lire le mot si un joueur joue un mot similaire au mot qui sera formé avec des lettres déjà présentes dans une autre direction
        else if (((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(mot_lu, copie_verif_mot)) != 0) && (cpt > 1)) || ((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(mot_lu, copie_verif_mot)) == 0) && (cpt > 1) && (direction == 'H')))
        {
          printf("En plaçant vos lettres, vous formez le mot %s\n", verif_mot);
          direction_mot = 'V'; // comme on vérifie les mots en vertical, on envoie le paramètre 'V' à la fonction score
          score_mots_modif(verif_mot, colonne, ligne, direction_mot, joueur_actuel);
        }
        cpt_score = 0; // on remet les compteurs à 0 pour passer au prochain mot
        for (i = 0; i < TAILLE_PLATEAU; i++)
        {
          verif_mot[i] = '\0'; // réinitialisaion de verif_mot
        }
        if (ligne == TAILLE_PLATEAU)
        {
          fin = 1; // si ligne atteint un maximum, on ne rentre plus dans le if
        }
      }
      cpt = 0;
    }
  }

  // de façon similaire mais pour une lecture ligne par ligne
  for (ligne = 0; ligne < TAILLE_PLATEAU; ligne++)
  {
    for (colonne = 0; colonne < TAILLE_PLATEAU; colonne++)
    {
      fin = 0;
      if ((copie_plateau[ligne][colonne].tuile != TUILE_STANDARD) && (fin == 0))
      {
        j = 0;
        cpt = 0;
        while ((copie_plateau[ligne][colonne].tuile != TUILE_STANDARD) && (colonne < TAILLE_PLATEAU))
        {
          verif_mot[j] = copie_plateau[ligne][colonne].tuile;
          if (toupper(copie_plateau[ligne][colonne].tuile) == toupper(plateau[ligne][colonne].tuile))
          {
            cpt_score++;
          }
          j++;
          colonne++;
          cpt++;
        }

        strcpy(copie_verif_mot, verif_mot);
        for (k = 0; k < (strlen(copie_verif_mot)); k++)
        {
          copie_verif_mot[k] = toupper(copie_verif_mot[k]);
        }

        if ((in_dic(verif_mot) == 0) && (cpt > 1))
        {
          printf("Le mot %s n'existe pas\n", verif_mot);
          return 0;
        }

        else if (((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(mot_lu, copie_verif_mot)) != 0) && (cpt > 1)) || ((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(mot_lu, copie_verif_mot)) == 0) && (cpt > 1) && (direction == 'V')))
        {
          printf("En plaçant vos lettres, vous formez le mot %s\n", verif_mot);
          direction_mot = 'H';
          score_mots_modif(verif_mot, colonne, ligne, direction_mot, joueur_actuel);
        }
        cpt_score = 0;
        for (i = 0; i < TAILLE_PLATEAU; i++)
        {
          verif_mot[i] = '\0';
        }
        if (colonne == TAILLE_PLATEAU)
        {
          fin = 1;
        }
      }
      cpt = 0;
    }
  }

  return 1;
}

void score_mots_modif(char verif_mot[TAILLE_PLATEAU], int colonne, int ligne, int direction, int joueur)
{
  int sum = 0;
  int mult = 1;
  int letter_index = 0;

  /* Cette fonction est similaire à la fonction de calcul des scores, sauf qu'elle fonctionne à l'envers
  du fait du fonctionnement de la fonction de vérification des nouveaux mots formés avec des lettres déjà posées
  qui envoie l'indice juste après le mot lu */

  // comme la fonction envoie l'indice juste après l'indice de la dernière lettre sur le plateau, il faut décrémenter l'indice
  if (direction == 'V')
  {
    ligne--;
  }
  else
  {
    colonne--;
  }

  puts(verif_mot);
  // 1- Comptabilise les points des lettres et leurs multiplicateurs
  for (int i = 0; i < strlen(verif_mot); i++)
  {
    if (islower(copie_plateau[ligne][colonne].tuile)) // si c'est une minuscule, c'est un joker, donc on ne compte pas
    {
      letter_index = 91;
      tablettre[letter_index].nbpoint = 0;
    }
    else
    {
      letter_index = copie_plateau[ligne][colonne].tuile - 'A';
    }
    // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
    if (verif_mot[i] != TUILE_STANDARD)
    {
      // Commence le comptage des valeurs
      if (copie_plateau[ligne][colonne].type == BALISE_LETTRE)
      {
        sum += copie_plateau[ligne][colonne].valeur * tablettre[letter_index].nbpoint; // si la BALISE_LETTRE est présente dans la case, alors on applique le bonus
        // la balise ne disparaît pas car elle doit compter aussi pour le mot nouvellement posé
      }
      else if (copie_plateau[ligne][colonne].type == BALISE_MOT)
      {
        sum += tablettre[letter_index].nbpoint;
        mult *= copie_plateau[ligne][colonne].valeur;
        // même fonctionnement pour le bonus de multiplication de la valeur du mot : il peut être appliqué
        // aux mots formés avec les lettres déjà présentes. Il doit aussi être appliqué au mot nouvellement posé
        // donc la balise n'est pas remplacée par une balise par défaut, contrairement à la fonction de score initiale
      }
      else
      {
        sum += tablettre[letter_index].nbpoint;
      }
    }
    else
    {
      sum += tablettre[letter_index].nbpoint;
    }
    // Fait reculer la boucle car on part de la dernière lettre du mot
    if (direction == 'H')
    {
      colonne--;
    }
    else
    {
      ligne--;
    }
  }

  temp_score += sum * mult;
}

char lettre_joker(char joker, int cpt_joker, int joueur)
{
  char lettre_remplace;
  // cette fonction permet de remplacer le joker saisi par le joueur par une lettre
  int i;
  int trouve = 0;

  for (i = 0; i < MAX_JETON_TOUR; i++)
  {
    if (tabjoueur[joueur].jeton[i] == '0')
    {
      trouve++;
    }
  }

  if ((trouve == 1) && (cpt_joker >= 2))
  {
    printf("Erreur pour le deuxième joker : vous ne possédez plus de jokers.\n");
    return 0;
  }

  else if (trouve == 0)
  {
    return 0;
  }

  else
  {
    printf("Par quelle lettre voulez vous remplacer votre joker n°%d ?: ", cpt_joker);
    scanf(" %c", &lettre_remplace);

    while ((lettre_remplace < 'A') && (lettre_remplace > 'Z') && (trouve == 1))
    {
      printf("Erreur de saisie : entrez une lettre valide : ");
      while ((lettre_remplace = getchar()) != '\n')
        ;
      scanf(" %c", &lettre_remplace);
      trouve = 0;
    }

    lettre_remplace = tolower(lettre_remplace); // pour identifier le joker, on le met en minuscule
    return (lettre_remplace);
  }
}

int verif_depassement_tableau(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, char direction)
{

  int i = 0;
  int j = 0;

  /* Cettte fonction permet de vérifier que le mot saisi ne dépasse pas le tableau du plateau
  elle reprend le fonctionnement de l'inscription d'un mot sur le plateau, mais si ligne ou colonne
  dépassent le plateau, elle retourne 0 */

  for (i = 0; i < TAILLE_PLATEAU; i++)
  {
    for (j = 0; j < TAILLE_PLATEAU; j++)
    {
      copie_plateau[i][j] = plateau[i][j];
    }
  }

  for (i = 0; i < strlen(mot_lu); i++)
  {
    if ((colonne >= TAILLE_PLATEAU) || (ligne >= TAILLE_PLATEAU))
    {
      return 0;
    }

    if (mot_lu[i] != TUILE_STANDARD)
    {
      if (mot_lu[i] <= 'Z')
      {
        copie_plateau[ligne][colonne].tuile = toupper(mot_lu[i]);
      }
      else
      {
        copie_plateau[ligne][colonne].tuile = mot_lu[i];
      }
    }

    // Fait avancer la boucle en fonction de la direction
    if (direction == 'H')
    {
      colonne++;
    }
    else
    {
      ligne++;
    }
  }

  return 1;
}
