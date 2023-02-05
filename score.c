#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "plateau.c"
#include "joueur.c"
#include "lettres.c"

int temp_score = 0;

/***** Calcul du score *****/
void score_joueur(char mot_lu[TAILLE_PLATEAU], int colonne, int ligne, int direction, int joueur)
{
    // Modifie aussi les valeurs du plateau afin d'enlever les valeurs spéciales déjà utilisées;
    int somme = 0;
    int mult = 1;
    int indice_lettre = 0;

    // 1- Comptabilise les points des lettres et leurs multiplicateurs
    for (int i = 0; i < strlen(mot_lu); i++)
    {
        if (islower(plateau[ligne][colonne].tuile))
        {
            indice_lettre = 91;
            tablettre[indice_lettre].nbpoint = 0;
        }
        else
        {
            indice_lettre = plateau[ligne][colonne].tuile - 'A';
        }
        // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
        if (mot_lu[i] != TUILE_STANDARD)
        {
            // Commence le comptage des valeurs
            if (plateau[ligne][colonne].type == BALISE_LETTRE)
            {
                somme += plateau[ligne][colonne].valeur * tablettre[indice_lettre].nbpoint;
                plateau[ligne][colonne].valeur = CASE_SIMPLE;
                plateau[ligne][colonne].type = BALISE_ABSENTE;
            }
            else if (plateau[ligne][colonne].type == BALISE_MOT)
            {
                somme += tablettre[indice_lettre].nbpoint;
                mult *= plateau[ligne][colonne].valeur;
                plateau[ligne][colonne].valeur = CASE_SIMPLE;
                plateau[ligne][colonne].type = BALISE_ABSENTE;
            }
            else
            {
                somme += tablettre[indice_lettre].nbpoint;
            }
        }
        else
        {
            somme += tablettre[indice_lettre].nbpoint;
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

    tabjoueur[joueur].score += somme * mult;
    tabjoueur[joueur].score += temp_score;
    printf("Nombre de points accumulés dans ce tour: %d\n", (somme * mult) + temp_score);
    temp_score = 0;
    printf("Votre score total (joueur %d) est : %d\n", joueur + 1, tabjoueur[joueur].score);
}

/**** Calcul score - mots modifiés ****/
void score_mots_modif(char verif_mot[TAILLE_PLATEAU], int colonne, int ligne, int direction, int joueur)
{
    int somme = 0;
    int mult = 1;
    int indice_lettre = 0;

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
            indice_lettre = 91;
            tablettre[indice_lettre].nbpoint = 0;
        }
        else
        {
            indice_lettre = copie_plateau[ligne][colonne].tuile - 'A';
        }
        // Laisse passer les cases où la lettre utilisée pour former le mot était déjà dans le plateau
        if (verif_mot[i] != TUILE_STANDARD)
        {
            // Commence le comptage des valeurs
            if (copie_plateau[ligne][colonne].type == BALISE_LETTRE)
            {
                somme += copie_plateau[ligne][colonne].valeur * tablettre[indice_lettre].nbpoint; // si la BALISE_LETTRE est présente dans la case, alors on applique le bonus
                                                                                                  // la balise ne disparaît pas car elle doit compter aussi pour le mot nouvellement posé
            }
            else if (copie_plateau[ligne][colonne].type == BALISE_MOT)
            {
                somme += tablettre[indice_lettre].nbpoint;
                mult *= copie_plateau[ligne][colonne].valeur;
                // même fonctionnement pour le bonus de multiplication de la valeur du mot : il peut être appliqué
                // aux mots formés avec les lettres déjà présentes. Il doit aussi être appliqué au mot nouvellement posé
                // donc la balise n'est pas remplacée par une balise par défaut, contrairement à la fonction de score initiale
            }
            else
            {
                somme += tablettre[indice_lettre].nbpoint;
            }
        }
        else
        {
            somme += tablettre[indice_lettre].nbpoint;
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

    temp_score += somme * mult;
}