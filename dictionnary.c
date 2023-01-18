#include <stdio.h>
#include <string.h>

int in_dic();

int main()
{
    int result;
    result = in_dic("alshdas");
    printf("%d", result);
}

/* Finds word in dictionnary */
int in_dic(char word[30])
{
    FILE *dic;
    int i=0;
    int find=3;
    char word_dic[30];

    dic = fopen("liste_francais.txt", "r");
    strcpy(word_dic,"");

    while ((! feof(dic)) && (strcmp(word, word_dic) != 0))
    {
        fscanf(dic, "%s", word_dic);
        if (strcmp(word, word_dic) == 0)
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