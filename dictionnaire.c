#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAILLE_PLATEAU 15

/* Finds word in dictionnary */
int in_dic(char word[TAILLE_PLATEAU])
{
    FILE *dic;
    int i = 0;
    int find = 3;
    char word_dic[30];
    char copie_mot[TAILLE_PLATEAU];

    strcpy(copie_mot, word);
    for (i = 0; copie_mot[i] != '\0'; i++)
    {
        copie_mot[i] = toupper(copie_mot[i]);
    }

    dic = fopen("liste_normalisee.txt", "r");
    strcpy(word_dic, "");

    while ((!feof(dic)) && (strcmp(copie_mot, word_dic) != 0))
    {
        fscanf(dic, "%s", word_dic);
        if (strcmp(copie_mot, word_dic) == 0)
        {
            find = 1;
        }
    }

    if (find == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
