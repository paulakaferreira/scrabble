#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAILLE_PLATEAU 15

/**** Cherche le mot au dictionnaire ****/
int dans_dic(char mot[TAILLE_PLATEAU])
{
    FILE *dic;
    int i = 0;
    int trouve = 3;
    char mot_dic[30];
    char copie_mot[TAILLE_PLATEAU];

    strcpy(copie_mot, mot);
    for (i = 0; copie_mot[i] != '\0'; i++)
    {
        copie_mot[i] = toupper(copie_mot[i]);
    }

    dic = fopen("dictionnaire.txt", "r");
    strcpy(mot_dic, "");

    while ((!feof(dic)) && (strcmp(copie_mot, mot_dic) != 0))
    {
        fscanf(dic, "%s", mot_dic);
        if (strcmp(copie_mot, mot_dic) == 0)
        {
            trouve = 1;
        }
    }
 
    fclose(dic);
    if (trouve == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
