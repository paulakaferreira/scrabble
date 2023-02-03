#include <stdio.h>
#include <string.h>
#include "player.c"
#include "plateau.c"
#include "score.c"
#include "tirage.c"

#define DEFAULT_TILE '.'

#define MAX_JETON_TOUR 7
char lettre_joker(char joker, int cpt_joker, int joueur);
int check_board_new_word(char word_read[TAILLE_PLATEAU], int column, int row, char direction, int current_player);
void score_mots_modif(char verif_mot[TAILLE_PLATEAU], int column, int row, int direction, int player);
int verif_depassement_tableau(char word_read[TAILLE_PLATEAU], int column, int row, char direction);
struct Carre copie_plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];

// Verifie la compatibilité du mot saisie avec les tuiles qui sont à la main du joueur

int check_hand_compatibility(char word_read[MAX_JETON_TOUR], int current_player)
{
  char hand_copy[MAX_JETON_TOUR];
  int n_letters_removed = 0;

  // Initialise une copie de la main de joueur.
  strcpy(hand_copy, tabjoueur[current_player].jeton);

  for (int i = 0; i < strlen(word_read); i++)
  {
    int found = 0;
    for (int j = 0; j < MAX_JETON_TOUR; j++)
    {
      if (word_read[i] == TUILE_STANDARD)
      {
        found = 1;
        break;
      }
      else if (word_read[i] == hand_copy[j])
      {
        hand_copy[j] = '\0';
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      for (int j = 0; j < MAX_JETON_TOUR; j++)
      {
        if (hand_copy[j] == '0')
        {
          hand_copy[j] = '\0';
          word_read[i] = tolower(word_read[i]);
          found = 1;
          break;
        }
      }
      if (found == 0)
      {
        return 0;
      }
    }
  }

  for (int i = 0; i < MAX_JETON_TOUR; i++)
  {
    tabjoueur[current_player].jeton[i] = hand_copy[i];
    if (hand_copy[i] == '\0')
    {
      n_letters_removed++;
    }
  }
  return n_letters_removed;
}

// Verifie la compatibilité du mot saisie avec le tableau;
// Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
int check_board_compatibility(int column, int row, char direction, char word_read[TAILLE_PLATEAU], int turn)
{
  int i = 0;
  int intersection = 0;
  int middle_board = 0;
  int up = 0;
  int down = 0;
  int right = 0;
  int left = 0;

  for (i = 0; i < strlen(word_read); i++)
  {
    // Vérifie la compatibilité du mot avec le plateau
    if (plateau[row][column].tuile != word_read[i] && plateau[row][column].tuile != TUILE_STANDARD)
    {
      if (word_read[i] == toupper(plateau[row][column].tuile))
      {
        word_read[i] = TUILE_STANDARD;
        intersection = 1;
      }
      else
      {
        return 0;
      }
    }
    // Intersection avec un autre mot
    else if (plateau[row][column].tuile != TUILE_STANDARD)
    {
      word_read[i] = TUILE_STANDARD;
      intersection = 1;
    }

    if (row > 0)
    {
      up = row - 1;
    }

    if (row < 14)
    {
      down = row + 1;
    }

    right = column + 1;
    if (right == 15)
    {
      right = 14;
    }

    left = column - 1;
    if (left == (-1))
    {
      left = 0;
    }

    if ((plateau[down][column].tuile != TUILE_STANDARD) || (plateau[up][column].tuile != TUILE_STANDARD) || (plateau[row][left].tuile != TUILE_STANDARD) || (plateau[row][right].tuile != TUILE_STANDARD))
    {
      intersection = 1;
    }

    // Milieu du tableu
    if ((column == 7) && (row == 7))
    {
      middle_board = 1;
    }

    // Fait avancer la boucle
    if (direction == 'H')
    {
      column++;
    }
    else
    {
      row++;
    }
  }
  // Verifie la condition du premier tour : le mot doit passer par le milieu tu tableau
  if ((middle_board == 0) && (turn == 0))
  {
    printf("Vous êtes au premier tour et votre mot ne passe pas par le milieu du tableau\n");
    return 0;
  }
  // Verifie la condition des tours suivants : le mot doit croiser un mot existant
  if ((intersection == 0) && (turn != 0))
  {
    printf("Attention à la règle du scrabble : votre mot doit croiser ou toucher un mot existant sur le plateau\n");
    printf("Les lettres qui se touchent doivent aussi former un mot valide dans le dictionnaire\n");
    return 0;
  }
  return 1;
}

// Ajout du mot validé au tableau
void modify_board(char word_read[TAILLE_PLATEAU], int column, int row, char direction)
{
  for (int i = 0; i < strlen(word_read); i++)
  {
    if (word_read[i] != TUILE_STANDARD)
    {
      if (word_read[i] <= 'Z')
      {
        plateau[row][column].tuile = toupper(word_read[i]);
      }
      else
      {
        plateau[row][column].tuile = word_read[i];
      }
    }

    // Fait avancer la boucle en fonction de la direction
    if (direction == 'H')
    {
      column++;
    }
    else
    {
      row++;
    }
  }
  printf("Votre mot a été ajouté au plateau\n");
}

// Demande au joueur de jouer son tour
// Fonction principale qui appelle les fonctions de compatibilité et de modification du tableau
int coup_partie(int current_player, int turn)
{
  int i = 0;
  char word_read[TAILLE_PLATEAU];
  char direction;
  char column_letter = '\0';
  int column = 0;
  int row = 0;
  int n_letters_removed = 0;
  int ligne_ok = 0;
  int cpt_joker = 0;

  printf("Vouz avez decidé d'ajouter un mot au tableau. \n");
  for (i = 0; i < TAILLE_PLATEAU; i++)
  {
    word_read[i] = '\0';
  }

  while (in_dic(word_read) == 0)
  {
    printf("Entrez le mot à ajouter au tableau (1 pour retourner au menu) : ");
    scanf("%s", word_read);
    for (i = 0; i < TAILLE_PLATEAU; i++)
    {
      if (word_read[i] == '0')
      {
        cpt_joker++;
        if(cpt_joker <=2)
        {
          word_read[i] = lettre_joker(word_read[i], cpt_joker, current_player);
        }
        else
        {
          printf("Erreur : il n'y a que deux jetons jokers dans le jeu. Veuillez revérifier votre saisie.\n");
          return 0;
      }
    }
    // Retour au menu
    if (strcmp(word_read, "1") == 0)
    {
      return 0;
    }
    else
    {
      for (i = 0; i < strlen(word_read); i++)
      {
        word_read[i] = toupper(word_read[i]);
      }
      if (in_dic(word_read) == 0)
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

  if (turn == 0)
  {
    printf("Attention: pour le premier tour, le mot doit passer impérativement par le milieu du tableau\n");
  }

  printf("Entrez le numéro de la ligne où la première lettre du mot apparaitra (1 - 15): ");
  ligne_ok = scanf("%d", &row);
  // Verification de saisie de la ligne
  while (((row < 1) || (row > 15)) || (ligne_ok == 0))
  {

    if (ligne_ok == 0)
    {
      printf("Erreur de saisie : veuillez saisir une ligne valide (1-15) : ");
      while ((row = getchar()) != '\n')
        ;
      ligne_ok = scanf("%d", &row);
    }
    else
    {
      if ((row < 1) || (row > 15))
      {
        printf("Numéro de ligne invalide : veuilez saisir un numéro de ligne entre 1 et 15 : ");
        while ((row = getchar()) != '\n')
          ;
        ligne_ok = scanf("%d", &row);
      }
    }
  }

  // Verification de saisie de la colonne
  printf("Entrez la lettre de la colonne où la première lettre du mot apparaitra (A - O): ");
  scanf(" %c", &column_letter);
  column = toupper(column_letter);
  column = column - 'A' + 1;
  while ((column < 1) || (column > 15))
  {
    printf("Erreur de saisie : veuillez saisi une colonne valide (A - O) :");
    while ((column_letter = getchar()) != '\n')
      ;
    scanf(" %c", &column_letter);
    column = toupper(column_letter);
    column = column - 'A' + 1;
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

  column--;
  row--;

  if ((verif_depassement_tableau(word_read, column, row, direction)) == 0)
  {
    printf("Erreur : votre mot dépasse le tableau !\n");
    return 0;
  }

  if (check_board_new_word(word_read, column, row, direction, current_player) == 0)
  {
    printf("Le mot que vous avez saisi interfère de façon invalide avec d'autres mots\n");
    temp_score = 0;
    return 0;
  }

  // Verifie la compatibilité du mot avec le tableau;
  // Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
  if (check_board_compatibility(column, row, direction, word_read, turn) == 1)
  {
    printf("----------------------------------------\n");

    n_letters_removed = check_hand_compatibility(word_read, current_player);

    // Verifie la compatibilité du mot avec le main du joueur
    if (n_letters_removed == 0)
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
    printf("Impossible d'ajouter le mot %s à l'endroit souhaité\n", word_read);
    printf("Retour au menu. Veuillez saisir une autre option ou ressayer\n");
    return 0;
  }

  // Modifie le tableau après validation
  modify_board(word_read, column, row, direction);

  // Change le score du joueur en cours
  printf("----------------------------------------\n");
  get_player_score(word_read, column, row, direction, current_player);
  printf("----------------------------------------\n");
  printf("Nombre de lettres à modifier dans votre main: %d\n", n_letters_removed);

  // Fait le tirage au sort pour le joeur actuel
  printf("----------------------------------------\n");
  tirage(n_letters_removed, current_player);
  return 1;
}

int check_board_new_word(char word_read[TAILLE_PLATEAU], int column, int row, char direction, int current_player)
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
  for (i = 0; i < strlen(word_read); i++) // ajout du mot au plaetau
  {
    if (word_read[i] != TUILE_STANDARD) // si la lettre saisie ne correspond pas à tuile_standard
    {
      if (word_read[i] <= 'Z') // si la lettre saisie est <= 'Z' (donc pas un joker qui est supérieur à Z)
      {
        if (word_read[i] == toupper(copie_plateau[row][column].tuile)) // si la lettre est déjà présente sur le plateau, on ne fait rien
        {
        }
        else
        {
          copie_plateau[row][column].tuile = toupper(word_read[i]); // Si la lettre est pas déjà présente sur le plateau, on la met sur le plateau
        }
      }
    }

    // Fait avancer la boucle en fonction de la direction
    if (direction == 'H')
    {
      column++;
    }
    else
    {
      row++;
    }
  }

  // le mot a été ajouté à la copie du plateau
  // maintenant il va s'agir de lire chaque colonne du tableau et de valider le mot ou non
  for (column = 0; column < TAILLE_PLATEAU; column++)
  {
    for (row = 0; row < TAILLE_PLATEAU; row++) // parcours colonne par colonne, grâce au compteur ligne qui augmente jusqu'à < TAILLE_PLATEAU
    {
      fin = 0; // remise à 0 du booléen fin qui permet au if suivant de ne pas prendre en compte le cas où la ligne est égale à 15 (TAILLE_PLATEAU)
      if ((copie_plateau[row][column].tuile != TUILE_STANDARD) && (fin == 0))
      {
        j = 0; // initialise le compteur J qui permettre de parcourir verif_mot
        cpt = 0; // permet de compter la taille du mot. Si la lettre est toute seule, cpt=1, et donc ce n'est pas un mot
        while ((copie_plateau[row][column].tuile != TUILE_STANDARD) && (row < TAILLE_PLATEAU)) // tant que ligne ne dépasse pas TAILLE_PLATEAU et que la tuile est différente de la tuile par défaut, on continue à ranger les lettres lues dans verif_mot
        {
          verif_mot[j] = copie_plateau[row][column].tuile;
          if (toupper(copie_plateau[row][column].tuile) == toupper(plateau[row][column].tuile))
          {
            cpt_score++; // vérification du nb de lettres qui sont déjà présentes sur l'ancien plateau
            // pour vérifier si le mot est nouveau ou si c'est déjà un mot posé qui n'a pas changé qui n'est donc pas àvérifier
          }
          j++; // on incrémente j pour passer à l'indice suivant de verif_mot
          row++; // on passe à a ligne suivante
          cpt++; // taille du mot
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
        else if (((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(word_read, copie_verif_mot)) != 0) && (cpt > 1)) || ((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(word_read, copie_verif_mot)) == 0) && (cpt > 1) && (direction == 'H')))
        {
          printf("En plaçant vos lettres, vous formez le mot %s\n", verif_mot);
          direction_mot = 'V'; // comme on vérifie les mots en vertical, on envoie le paramètre 'V' à la fonction score
          score_mots_modif(verif_mot, column, row, direction_mot, current_player);
        }
        cpt_score = 0; // on remet les compteurs à 0 pour passer au prochain mot
        for (i = 0; i < TAILLE_PLATEAU; i++)
        {
          verif_mot[i] = '\0'; // réinitialisaion de verif_mot
        }
        if (row == TAILLE_PLATEAU)
        {
          fin = 1; // si row atteint un maximum, on ne rentre plus dans le if
        }
      }
      cpt = 0;
    }
  }
  
  // de façon similaire mais pour une lecture ligne par ligne
  for (row = 0; row < TAILLE_PLATEAU; row++)
  {
    for (column = 0; column < TAILLE_PLATEAU; column++)
    {
      fin = 0;
      if ((copie_plateau[row][column].tuile != TUILE_STANDARD) && (fin == 0))
      {
        j = 0;
        cpt = 0;
        while ((copie_plateau[row][column].tuile != TUILE_STANDARD) && (column < TAILLE_PLATEAU))
        {
          verif_mot[j] = copie_plateau[row][column].tuile;
          if (toupper(copie_plateau[row][column].tuile) == toupper(plateau[row][column].tuile))
          {
            cpt_score++;
          }
          j++;
          column++;
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

        else if (((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(word_read, copie_verif_mot)) != 0) && (cpt > 1)) || ((cpt_score == ((strlen(verif_mot) - 1))) && ((strcmp(word_read, copie_verif_mot)) == 0) && (cpt > 1) && (direction == 'V')))
        {
          printf("En plaçant vos lettres, vous formez le mot %s\n", verif_mot);
          direction_mot = 'H';
          score_mots_modif(verif_mot, column, row, direction_mot, current_player);
        }
        cpt_score = 0;
        for (i = 0; i < TAILLE_PLATEAU; i++)
        {
          verif_mot[i] = '\0';
        }
        if (column == TAILLE_PLATEAU)
        {
          fin = 1;
        }
      }
      cpt = 0;
    }
  }

  return 1;
}

void score_mots_modif(char verif_mot[TAILLE_PLATEAU], int column, int row, int direction, int player)
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
    row--;
  }
  else
  {
    column--;
  }

  puts(verif_mot);
  // 1- Comptabilise les points des lettres et leurs multiplicateurs
  for (int i = 0; i < strlen(verif_mot); i++)
  {
    if (islower(copie_plateau[row][column].tuile)) // si c'est une minuscule, c'est un joker, donc on ne compte pas
    {
      letter_index = 91;
      tablettre[letter_index].nbpoint = 0;
    }
    else
    {
      letter_index = copie_plateau[row][column].tuile - 'A';
    }
    // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
    if (verif_mot[i] != TUILE_STANDARD)
    {
      // Commence le comptage des valeurs
      if (copie_plateau[row][column].type == BALISE_LETTRE)
      {
        sum += copie_plateau[row][column].valeur * tablettre[letter_index].nbpoint; // si la BALISE_LETTRE est présente dans la case, alors on applique le bonus
        // la balise ne disparaît pas car elle doit compter aussi pour le mot nouvellement posé
      }
      else if (copie_plateau[row][column].type == BALISE_MOT)
      {
        sum += tablettre[letter_index].nbpoint;
        mult *= copie_plateau[row][column].valeur;
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
      column--;
    }
    else
    {
      row--;
    }
  }

  temp_score += sum * mult;
}

char lettre_joker(char joker, int cpt_joker, int joueur)
{
  char lettre_remplace;

  int i;
  int trouve = 0;

  // boucle qui compte le nombre de joker dans la main du boujeur
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
    printf("Vous ne possédez pas de joker.\n");
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

    lettre_remplace = tolower(lettre_remplace);
    return (lettre_remplace);
  }
}

int verif_depassement_tableau(char word_read[TAILLE_PLATEAU], int column, int row, char direction)
{

  int i = 0;
  int j = 0;

  for (i = 0; i < TAILLE_PLATEAU; i++)
  {
    for (j = 0; j < TAILLE_PLATEAU; j++)
    {
      copie_plateau[i][j] = plateau[i][j];
    }
  }

  for (i = 0; i < strlen(word_read); i++)
  {
    if ((column >= TAILLE_PLATEAU) || (row >= TAILLE_PLATEAU))
    {
      return 0;
    }

    if (word_read[i] != TUILE_STANDARD)
    {
      if (word_read[i] <= 'Z')
      {
        copie_plateau[row][column].tuile = toupper(word_read[i]);
      }
      else
      {
        copie_plateau[row][column].tuile = word_read[i];
      }
    }

    // Fait avancer la boucle en fonction de la direction
    if (direction == 'H')
    {
      column++;
    }
    else
    {
      row++;
    }
  }

  return 1;
}
