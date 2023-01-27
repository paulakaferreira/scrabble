#include <stdio.h>
#include <string.h>
#include "player.c"
#include "board.c"
#include "score.c"
#include "tirage.c"

#define DEFAULT_TILE '.'

#define MAX_JETON_TOUR 7
char lettre_joker(char joker, int cpt_joker);
int check_board_new_word (char word_read[BOARD_SIZE], int column, int row, char direction, int current_player);
void score_mots_modif(char verif_mot[BOARD_SIZE], int column, int row, int direction, int player);
struct Square copie_plateau[BOARD_SIZE][BOARD_SIZE];

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
            if (word_read[i] == DEFAULT_TILE)
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
            for (int j=0; j<MAX_JETON_TOUR; j++)
            {
              if(hand_copy[j]=='0')
              {
                hand_copy[j]= '\0';
                word_read[i]=tolower(word_read[i]);
                found=1;
                break;
              } 
            }
            if(found==0)
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
int check_board_compatibility(int column, int row, char direction, char word_read[BOARD_SIZE], int turn)
{
    int i = 0;
    int intersection = 0;
    int middle_board = 0;
    int up, down, right, left;

    for (i = 0; i < strlen(word_read); i++)
    {
        // Vérifie la compatibilité du mot avec le plateau
        if (board[row][column].tile != word_read[i] && board[row][column].tile != DEFAULT_TILE)
        {
            return 0;
        }
        // Intersection avec un autre mot
        else if (board[row][column].tile != DEFAULT_TILE)
        {
            word_read[i] = DEFAULT_TILE;
            intersection = 1;
        }
	    
	up=row-1;
        down=row+1;
        right=column+1;
        left=column-1;
        if ((board[down][column].tile != DEFAULT_TILE) || (board[up][column].tile != DEFAULT_TILE) || (board[row][left].tile!= DEFAULT_TILE) || (board[row][right].tile != DEFAULT_TILE))
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
        printf("Attention à la règle principale du scrabble : votre mot doit croiser un mot existant sur le plateau\n");
        return 0;
    }
    return 1;
}

// Ajout du mot validé au tableau
void modify_board(char word_read[BOARD_SIZE], int column, int row, char direction)
{
    for (int i = 0; i < strlen(word_read); i++)
    {
        if (word_read[i] != DEFAULT_TILE)
        {
            if(word_read[i]<='Z')
            {
              board[row][column].tile = toupper(word_read[i]);
            }
            else
            {
              board[row][column].tile = word_read[i];
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
int get_move(int current_player, int turn)
{
    int i = 0;
    int count = 1;
    char word_read[BOARD_SIZE];
    char direction;
    char column_letter = '\0';
    int column = 0;
    int row = 0;
    int n_letters_removed = 0;
    int ligne_ok=0;
    int cpt_joker=0;


    printf("Vouz avez decidé d'ajouter un mot au tableau. \n");
    for(i=0; i<BOARD_SIZE; i++)
    {
      word_read[i]='\0';
    }

    while (in_dic(word_read) == 0)
    {
        printf("Entrez le mot à ajouter au tableau (1 pour retourner au menu) : ");
        scanf("%s", word_read);
        for(i=0; i<BOARD_SIZE; i++)
        {
          if(word_read[i]=='0')
            {
              cpt_joker++;
              word_read[i]=lettre_joker(word_read[i], cpt_joker);
              
            }
        }
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
    ligne_ok=scanf("%d", &row);
    // Verification de saisie de la ligne
    while (((row < 1) || (row > 15))||(ligne_ok==0))
    {

  	  if(ligne_ok==0)
	  {
	    printf("Erreur de saisie : veuillez saisir une ligne valide (1-15) : ");
	    while((row=getchar())!='\n');
	    ligne_ok=scanf("%d", &row);
	  }
	  else
	  {
          if ((row < 1) || (row > 15))
          {
              printf("Numéro de ligne invalide : veuilez saisir un numéro de ligne entre 1 et 15 : ");
	          while((row=getchar())!='\n');
              ligne_ok=scanf("%d", &row);
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
	  while((column_letter=getchar())!='\n');
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
        while ((direction=getchar())!='\n');
        scanf(" %c", &direction);
        direction = toupper(direction);
    }

    column--;
    row--;

     if (check_board_new_word(word_read, column, row, direction, current_player)==0)
     {
       printf("Le mot que vous avez saisi interfère de façon invalide avec d'autres mots\n");
       temp_score=0;
       return 0;
     }
    // Verifie la compatibilité du mot avec le tableau;
    // Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
    if (check_board_compatibility(column, row, direction, word_read, turn) == 1)
    {
        printf("----------------------------------------\n");
        printf("Votre mot est compatible avec le tableau\n");

        n_letters_removed = check_hand_compatibility(word_read, current_player);

        // Verifie la compatibilité du mot avec le main du joueur
        if (n_letters_removed != 0)
        {
            printf("Votre mot est compatible avec votre main\n");
        }
        else
        {
            printf("----------------------------------------\n");
            printf("Les lettres saisies ne sont pas compatibles avec votre main\n");
            printf("Retour au menu. Veuillez choisir une autre option au ressayer\n");
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


int check_board_new_word (char word_read[BOARD_SIZE], int column, int row, char direction, int current_player)
{
    
    int i=0;
    int j=0;
    char verif_mot[BOARD_SIZE];
    int cpt=0;
    int cpt_score=0;
    char direction_mot;

    for(i=0; i<BOARD_SIZE; i++)
    {
      verif_mot[i] = '\0';
    }
    
    for (i=0; i<BOARD_SIZE; i++)
    {
      for(j=0; j<BOARD_SIZE; j++)
      {
        copie_plateau[i][j]=board[i][j];
      }
     }
     
    for (i = 0; i < strlen(word_read); i++)
    {
        if (word_read[i] != DEFAULT_TILE)
        {
             if(word_read[i]>='A')
            {
              copie_plateau[row][column].tile = toupper(word_read[i]);
            }
            else
            {
              copie_plateau[row][column].tile = word_read[i];
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
  for (column=0; column<BOARD_SIZE; column++)
  {
    for(row=0; row<BOARD_SIZE; row++)
    {
      if (copie_plateau[row][column].tile != DEFAULT_TILE)
      {
        j=0;
        cpt=0;
        while(copie_plateau[row][column].tile != DEFAULT_TILE)
        {
          verif_mot[j]=copie_plateau[row][column].tile;
          if(copie_plateau[row][column].tile==board[row][column].tile)
          {
            cpt_score++;
          }
          j++;
          row++;
          cpt++;
        }
        if ((in_dic(verif_mot) == 0)&&(cpt>1))
        {
          printf("Le mot %s n'existe pas\n", verif_mot);
          return 0;
        }
        else if (((cpt_score==((strlen(verif_mot)-1)))&&((strcmp(word_read, verif_mot))!=0)&&(cpt>1))||((cpt_score==((strlen(verif_mot)-1)))&&((strcmp(word_read, verif_mot))==0)&&(cpt>1)&&(direction=='H')))
        {
          printf("En plaçant vos lettres, vous formez le mot %s\n", verif_mot);
          direction_mot = 'V';
          score_mots_modif(verif_mot, column, row,  direction_mot, current_player);
        }
        cpt_score=0;
        for(i=0; i<BOARD_SIZE; i++)
        {
          verif_mot[i] = '\0';
        }
      }
      cpt=0;
    }
  }
  
    for (row=0; row<BOARD_SIZE; row++)
  {
    for(column=0; column<BOARD_SIZE; column++)
    {
      if (copie_plateau[row][column].tile != DEFAULT_TILE)
      {
        j=0;
        cpt=0;
        while(copie_plateau[row][column].tile != DEFAULT_TILE)
        {
          verif_mot[j]=copie_plateau[row][column].tile;
          if(copie_plateau[row][column].tile==board[row][column].tile)
          {
            cpt_score++;
          }
          j++;
          column++;
          cpt++;
        }
        if ((in_dic(verif_mot) == 0)&&(cpt>1))
        {
          printf("Le mot %s n'existe pas\n", verif_mot);
          return 0;
        }
        else if (((cpt_score==((strlen(verif_mot)-1)))&&((strcmp(word_read, verif_mot))!=0)&&(cpt>1))||((cpt_score==((strlen(verif_mot)-1)))&&((strcmp(word_read, verif_mot))==0)&&(cpt>1)&&(direction=='V')))
        {
          printf("En plaçant vos lettres, vous formez le mot %s\n", verif_mot);
          direction_mot='H';
          score_mots_modif(verif_mot, column, row,  direction_mot, current_player);
        }
        cpt_score=0;
        for(i=0; i<BOARD_SIZE; i++)
        {
          verif_mot[i] = '\0';
        }
      }
      cpt=0;
    }
  }
  
  return 1;


}

void score_mots_modif(char verif_mot[BOARD_SIZE], int column, int row, int direction, int player)
{
    int sum = 0;
    int mult = 1;
    int letter_index = 0;
    
    
    if(direction=='V')
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
        if(islower(copie_plateau[row][column].tile))
        {
          letter_index = 91;
          tablettre[letter_index].nbpoint=0; // je ne sais pas pourquoi ça me le met à 1 par défaut...
        }
        else
        {
          letter_index = copie_plateau[row][column].tile - 'A';
        }
        // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
        if (verif_mot[i] != DEFAULT_TILE)
        {
            // Commence le comptage des valeurs
            if (copie_plateau[row][column].type == LETTER_FLAG)
            {
                  sum += copie_plateau[row][column].value * tablettre[letter_index].nbpoint;
                
            }
            else if (copie_plateau[row][column].type == WORD_FLAG)
            {
                sum += tablettre[letter_index].nbpoint;
                mult *= copie_plateau[row][column].value;
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
        // Fait reculer la boucle
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

char lettre_joker(char joker, int cpt_joker)
{
  char lettre_remplace;
  
  printf("Par quelle lettre voulez vous remplacer votre joker n°%d ?: ");
  scanf(" %c", &lettre_remplace);
  
  while ((lettre_remplace < 'A') && (lettre_remplace > 'Z'))
  {
      printf("Erreur de saisie : entrez une lettre valide : ");
      while ((lettre_remplace=getchar())!='\n');
      scanf(" %c", &lettre_remplace);
  }
  
  lettre_remplace=tolower(lettre_remplace);
  return(lettre_remplace); 
}
