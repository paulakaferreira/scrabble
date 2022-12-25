#include <stdio.h>

/* Essai : ce programme initialise et affiche un tableau contenant l'ensemble des lettres du 
sac de lettres, leur quantité et le nombre de points qui leur sont associés*/
#define MAX_LETTRE 26
#define MAX_JETON 27


int main()
{
    struct lettre{
        int id_lettre;
        int nbpoint, quantite;
    };
    
    struct lettre lettre;
    struct lettre tablettre[MAX_JETON-1];
    int i, j;


printf("Voilà le nombre de jetons : %d\n", MAX_JETON);

/* Utilisation d'une boucle for qui parcourt i de 65 (code ASCII de A) jusque 90, code ASCII de Z,
et 91 qu'on utilisera pour le cas des jetons joker. Le switch est fait en utilisant les caractères
qui sont interprétés comme entiers, par leur code ASCII */ 

  for(i=65, j=0; i<MAX_JETON+65; i++, j++)
  {
    
    if (i==91)
    {
        lettre.id_lettre='0';
    }
    else
    {
      lettre.id_lettre=i;
    }
    
    
    switch(i)
      {
          case 'A' : 
          case 'E' : 
          case 'I' : 
          case 'L' : 
          case 'N' : 
          case 'O' : 
          case 'R' : 
          case 'S' : 
          case 'T' : 
          case 'U' : 
             lettre.nbpoint=1;
          break;
          
          case 'D' :
          case 'G' :
          case 'M' :
             lettre.nbpoint=2;
          break;
          
          /* Pour les cas suivants, chaque lettre valant le même nombre de point ont aussi la même quantité. Cela permet de simplifier le switch 
          suivant qui attribuera une quantité à une lettre*/
          case 'B' :
          case 'C' :
          case 'P' :
              lettre.nbpoint=3;
              lettre.quantite=2;
          break;
          
          case 'F' :
          case 'H' :
          case 'V' :
             lettre.nbpoint=4;
             lettre.quantite=2;
          break;
          
          case 'J' :
          case 'Q' :
             lettre.nbpoint=8;
             lettre.quantite=1;
          break;
          
          case 'K' :
          case 'W' :
          case 'X' :
          case 'Y' :
          case 'Z' :
            lettre.nbpoint=10;
            lettre.quantite=1;
          break;
          
          /* Cas des jetons jokers */
          case 91 :
            lettre.nbpoint=0;
            lettre.quantite=2;
      }
      
    switch(i)
    {
        case 'E' : 
            lettre.quantite=15;
        break;
        
        case 'A' :
            lettre.quantite=9;
        break;
        
        case 'I' :
            lettre.quantite=8;
        break;
        
        case 'N' :
        case 'O' :
        case 'R' :
        case 'S' :
        case 'T' :
        case 'U' :
            lettre.quantite=6;
        break;
        
        case 'L' :
            lettre.quantite=5;
        break;
        
        case 'D' :
        case 'M' :
            lettre.quantite=3;
        case 'G' :
            lettre.quantite=2;
        
        
    }
      tablettre[j]=lettre;
  }
  
  for(i=0; i<MAX_JETON; i++)
  {
      printf("%d. %c : %d point(s), %d jeton(s)\n", i+1, tablettre[i].id_lettre, tablettre[i].nbpoint, tablettre[i].quantite);
  }
}