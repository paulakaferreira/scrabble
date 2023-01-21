#include <stdio.h>
#include <string.h>
#include "board.c"
#include "tirage.c"

#define DEFAULT_TILE '.'

#define MAX_JETON_TOUR 7

// Verifie la compatibilité du mot saisie avec les tuiles qui sont à la main du joueur
int check_hand_compatibility(char word_read[MAX_JETON_TOUR], int current_player)
{
    char hand_copy[MAX_JETON_TOUR];

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
            return 0;
        }
    }

    return 1;
}

// Verifie la compatibilité du mot saisie avec le tableau;
// Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
int check_board_compatibility(int column, int row, char direction, char word_read[30])
{
    int i = 0;

    for (i = 0; i < strlen(word_read); i++)
    {
        // Vérifie que le mot peut bien rentrer dans le plateau à l'lendroit souhaité
        if (board[row][column].tile != word_read[i] && board[row][column].tile != DEFAULT_TILE)
        {
            return 0;
        }
        else if (board[row][column].tile != DEFAULT_TILE)
        {
            word_read[i] = DEFAULT_TILE;
        }

        if (direction == 'H')
        {
            column++;
        }
        else
        {
            row++;
        }
    }

    printf("dentro: ");
    puts(word_read);

    return 1;
}

// Ajout du mot validé au tableau
void modify_board(char word_read[30], int column, int row, char direction)
{
    for (int i = 0; i < strlen(word_read); i++)
    {
        if (word_read[i] != DEFAULT_TILE)
        {
            board[row][column].tile = toupper(word_read[i]);
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
}

// Demande au joueur de jouer son tour
// Fonction principale qui appelle les fonctions de compatibilité et de modification du tableau
int get_move(int current_player)
{
    int i = 0;
    int count = 1;
    char word_read[30];
    char direction;
    int column = 0;
    int row = 0;

    printf("Vouz avez decidé d'ajouter un mot au tableau. \n");
    strcpy(word_read, "not-a-word");

    while (in_dic(word_read) == 0)
    {
        printf("Entrez le mot à ajouter au tableau (1 pour retourner au menu) : ");
        scanf("%s", word_read);
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
                printf("Le mot que vous avez écrit n'est pas dans notre dictionnaire\n");
                printf("Merci d'entrer un mot valide.\n");
            }
        }
    }

    printf("Le mot est valide \n");

    // Verification de saisie de la colomne
    while ((column < 1) || (column > 15))
    {
        printf("Entrez le numéro de la colomne où la première lettre du mot apparaitra (1 - 15): ");
        scanf("%d", &column);
        // ajouter le cas ou le caracter n'est pas un chiffre
        if ((column < 1) || (column > 15))
        {
            printf("Réponse invalide. Veuillez réssayer\n");
        }
    }
    // Verification de saisie de la ligne
    while ((row < 1) || (row > 15))
    {
        printf("Entrez le numéro de la ligne où la première lettre du mot apparaitra (1 - 15): ");
        scanf("%d", &row);
        // ajouter le cas ou le caracter n'est pas un chiffre
        if ((row < 1) || (row > 15))
        {
            printf("Réponse invalide. Veuillez réssayer\n");
        }
    }

    while ((direction != 'H') && (direction != 'V'))
    {
        printf("Entrez la direction du mot (H pour horizontal et V pour vertical) : ");
        scanf(" %c", &direction);
        direction = toupper(direction);
    }

    column--;
    row--;

    // Verifie la compatibilité du mot avec le tableau;
    // Si compatible, modifie le mot sasie pour enlever les tuiles déjà existantes dans le tableau;
    if (check_board_compatibility(column, row, direction, word_read) == 1)
    {

        printf("Votre mot est compatible avec le tableau\n");
        printf("fora: ");
        puts(word_read);

        // Verifie la compatibilité du mot avec le main du joueur
        if (check_hand_compatibility(word_read, current_player) == 1)
        {
            printf("Votre mot est compatible avec votre main\n");
        }
        else
        {
            printf("Le lettres saisies ne sont pas compatibles avec votre main\n");
            printf("Retour au menu. Veuillez choisir une autre option au ressayer\n");
            return 0;
        }
    }
    else
    {
        printf("Les directions ne sont pas compatibles avec le tableau\n");
        printf("Impossible d'ajouter le mot %s à l'endroit souhaité\n", word_read);
        printf("Retour au menu. Veuillez saisir une autre option ou ressayer\n");
        return 0;
    }

    // Modifie le tableau après validation
    modify_board(word_read, column, row, direction);
    return 1;
}