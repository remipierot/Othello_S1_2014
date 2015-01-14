#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "othello.h"

int saisieJoueur (int *ligne, int *colonne)
{
    if(ligne!=NULL && colonne!=NULL)
    {
        char choixCase[TAILLE_CH]={'\0'};

        printf("Que souhaitez-vous faire ?\nA - Abandonner\nM - Menu principal\nA8 - Poser un pion (lettres A-H et numeros 1-8)\n");
        scanf("%s", choixCase);

        *choixCase=toupper(*choixCase);

        if(choixCase[1]=='\0')
        {
            if(*choixCase=='A')
                return -2;
            else if(*choixCase=='M')
                return -1;

            return 0;
        }
        else if(choixCase[2]=='\0')
        {
            if(*choixCase>='A' && *choixCase<='H' && choixCase[1]>='1' && choixCase[1]<='8')
            {
                (*ligne)=(int)(*choixCase-'A');
                (*colonne)=(int)(choixCase[1]-'1');

                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

int tourJoueur(struct partie *p)
{
    int ligne, colonne, choixJoueur=1, i, noir=0, blanc=0;

    affichage(p);

	for(i=0; i<NB_CASES; i++)
	{
		if(getCase(p, i/NB_CASES_PAR_LIGNE, i%NB_CASES_PAR_LIGNE)==1)
			noir++;
		else if(getCase(p, i/NB_CASES_PAR_LIGNE, i%NB_CASES_PAR_LIGNE)==-1)
			blanc++;
	}

	if(noir>1)
	{
	    if(blanc>1)
            printf("          %d Noirs                                %d Blancs\n", noir, blanc);
        else
            printf("          %d Noirs                                %d Blanc\n", noir, blanc);
	}
    else
    {
        if(blanc>1)
            printf("          %d Noir                                %d Blancs\n", noir, blanc);
        else
            printf("          %d Noir                                %d Blanc\n", noir, blanc);
    }

    if(p!=NULL && p->premierJoueurJoue==1)
        printf("\nC'est au tour de %s. (Noir)\n", p->nomJ1);
    else if(p!=NULL)
        printf("\nC'est au tour de %s. (Blanc)\n", p->nomJ2);
    else
        printf("\nLa partie que vous essayez de jouer n'existe pas.\n");

    if(joueurPeutJouer(p)==0)
    {
        printf("Vous ne pouvez actuellement jouer aucun coup.\n");
        changementJoueur(p);
        return 0;
    }
    else
    {
        do{
            choixJoueur=saisieJoueur(&ligne, &colonne);

            if(choixJoueur==0 || (choixJoueur==1 && coupValide(p, ligne, colonne)==0))
                printf("\nVotre saisie est incorrecte.\nVous devez saisir un des choix proposes ou bien un coup jouable.\nVeuillez donc entrer des valeurs valides.\n\n");
            else
                printf("\n\n");
        }while(choixJoueur==0 || (choixJoueur==1 && coupValide(p, ligne, colonne)==0));

        if(choixJoueur==1 && coupValide(p, ligne, colonne)!=0)
        {
            mouvement(p, ligne, colonne);
            changementJoueur(p);
        }
        return choixJoueur;
    }
}

int gagnant(struct partie *p)
{
    int caseVisee, noir=0, blanc=0;

    for(caseVisee=0; caseVisee<NB_CASES; caseVisee++)
    {
         if(getCase(p, caseVisee/NB_CASES_PAR_LIGNE, caseVisee%NB_CASES_PAR_LIGNE)==-1)
             blanc++;
         else if(getCase(p, caseVisee/NB_CASES_PAR_LIGNE, caseVisee%NB_CASES_PAR_LIGNE)==1)
             noir++;
    }

    return (((noir>blanc)==1)-((blanc>noir)==1));
}

int finPartie (struct partie *p)
{
    int fin=0;

    fin+=joueurPeutJouer(p);
    changementJoueur(p);
    fin+=joueurPeutJouer(p);
    changementJoueur(p);

    if(fin==0)
        return 1;

    return 0;
}

int jouerPartie (struct partie *p)
{
    int fin=0;
    do{
        fin=tourJoueur(p);
    }while(finPartie(p)!=1 && (fin!=-1 && fin!=-2));

    if(finPartie(p)==1 || fin==-2)
        return 1;

    return 0;
}
