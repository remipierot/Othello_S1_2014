#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "othello.h"

int main()
{
	int exit=0, check=1, end, i, noir=0, blanc=0;
	struct partie *p=NULL;

	makeSave();

	do{
	    exit=menu(p);

	    if(exit==1)
		p=creerPartie();
	    else if(exit==2)
	    {
		p=(partie*)calloc(sizeof(struct partie),1);
		check=chargementPartie(p);
	    }
	    else if(exit==3)
		check=sauvegardePartie(p);
		if(exit!=0 && check!=0 && p!=NULL)
	    {
		end=jouerPartie(p);

	    if(end==1)
		{
		    if(finPartie(p)!=1)
		    {
		        if(p->premierJoueurJoue==1)
		            printf("%s abandonne le jeu.\n%s remporte donc la victoire par forfait !\n\n", p->nomJ1, p->nomJ2);
		        else
		            printf("%s abandonne le jeu.\n%s remporte donc la victoire par forfait !\n\n", p->nomJ2, p->nomJ1);
		    }
		    else
		    {
			affichage(p);

			for(i=0; i<NB_CASES; i++)
			{
				if(getCase(p, i/NB_CASES_PAR_LIGNE, i%NB_CASES_PAR_LIGNE)==1)
					noir++;
				else if(getCase(p, i/NB_CASES_PAR_LIGNE, i%NB_CASES_PAR_LIGNE)==-1)
					blanc++;
			}

		        if(gagnant(p)==1)
		            printf("%s remporte la victoire avec %d points !\n\n", p->nomJ1, noir);
		        else if(gagnant(p)==-1)
		            printf("%s remporte la victoire avec %d points !\n\n", p->nomJ2, blanc);
		        else
		            printf("Match nul!\n\n");
		    }
		    free(p);
		    p=NULL;
		}
	    }
	    else if(check==0 && p!=NULL)
	    {
		if(exit==2)
		    printf("\nImpossible de charger la partie comme demande.\nFin du programme.\n");
		else if(exit==3)
		    printf("\nImpossible de sauvegarder la partie comme demande.\nFin du programme.\n");
	    }
	}while(exit!=0 && check!=0);

    return 0;
}
