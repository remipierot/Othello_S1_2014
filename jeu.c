#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "othello.h"

/*!                                                                                                                             *
 * Fonction retournant 1 si le joueur posant un pion sur la case (ligne,colonne) mange un pion                                  *
 * adverse dans la direction donnée, 0 sinon.                                                                                   *
 *                                                                                                                              *
 * \param p : pointeur sur la partie en cours                                                                                   *
 * \param ligne : numéro de ligne de la case sur laquelle le pion du joueur sera posé                                           *
 * \param colonne : numéro de colonne de la case sur laquelle le pion du joueur sera posé                                       *
 * \param horizontal : axe de direction horizontal (vers la gauche, pas de changement ou vers la droite) (compris entre [-1,1]) *
 * \param vertical : axe de direction (vers le haut, pas de changement ou vers le bas) (compris entre [-1,1])                   */
int priseDansDirectionPossible(struct partie *p, int ligne, int colonne, int horizontal, int vertical)
{
    int caseAxe;

    // On vérifie que la case précédente de l'axe est bien de couleur inverse à celle du joueur actuel.
    if(p!=NULL && getCase(p, ligne-vertical, colonne-horizontal)==-(p->premierJoueurJoue-(p->premierJoueurJoue==0)))
    {
        // Si l'on croise une case à 0 avant de croiser une case de notre couleur ou que l'on ne trouve pas de case de notre couleur, le coup n'est pas jouable.
        for(caseAxe=2; caseAxe<NB_CASES_PAR_LIGNE; caseAxe++)
        {
            if(getCase(p, ligne-caseAxe*vertical, colonne-caseAxe*horizontal)==0)
                return 0;
            else if(getCase(p, ligne-caseAxe*vertical, colonne-caseAxe*horizontal)==(p->premierJoueurJoue-(p->premierJoueurJoue==0)) && (ligne-caseAxe*vertical)>=0 && (ligne-caseAxe*vertical)<=7 && (colonne-caseAxe*horizontal)>=0 && (colonne-caseAxe*horizontal)<=7)
                return 1;
        }
        return 0;
    }
    return 0;
}

/*!                                                                                          *
 * Fonction indiquant 1 si le joueur peut poser un pion sur la case (ligne,colonne), 0 sinon *
 *                                                                                           *
 * \param p : pointeur sur la partie en cours                                                *
 * \param ligne : numéro de ligne de la case sur laquelle le pion du joueur sera posé        *
 * \param colonne : numéro de colonne de la case sur laquelle le pion du joueur sera posé    */
int coupValide(struct partie *p, int ligne, int colonne)
{
    int horizontal, vertical, count=0;

    // On vérifie la valeur de priseDansDirectionPossible pour tous les axes d'une case donnée.
    for(vertical=-1; vertical<=1; vertical++)
    {
        for(horizontal=-1; horizontal<=1; horizontal++)
            count+=priseDansDirectionPossible(p, ligne, colonne, horizontal, vertical);
    }

    // Si l'on a au moins une prise possible et que la case où l'on se trouve est à 0, alors on peut jouer.
    if(count!=0 && getCase(p, ligne, colonne)==0)
        return 1;

    return 0;
}

/*!                                                                                                                             *
 * Fonction effectuant la mise à jour (pions pris) dans la direction donnée                                                     *
 *                                                                                                                              *
 * \param p : pointeur sur la partie en cours                                                                                   *
 * \param ligne : numéro de ligne de la case sur laquelle le pion du joueur sera posé                                           *
 * \param colonne : numéro de colonne de la case sur laquelle le pion du joueur sera posé                                       *
 * \param horizontal : axe de direction horizontal (vers la gauche, pas de changement ou vers la droite) (compris entre [-1,1]) *
 * \param vertical : axe de direction (vers le haut, pas de changement ou vers le bas) (compris entre [-1,1])                   */
void mouvementDansDirection(struct partie *p, int ligne, int colonne, int horizontal, int vertical)
{
    int caseAxe=0;

    // On vérifie qu'il est possible de jouer sur cet axe avant toute chose.
    if(priseDansDirectionPossible(p, ligne, colonne, horizontal, vertical)==1)
    {
        // Tant que la valeur de la case est différente de celle du joueur actuel, on remplace en conséquence.
        do{
            setCase(p, ligne-caseAxe*vertical, colonne-caseAxe*horizontal, (p->premierJoueurJoue-(p->premierJoueurJoue==0)));
            caseAxe++;
        }while(getCase(p, ligne-caseAxe*vertical, colonne-caseAxe*horizontal)!=(p->premierJoueurJoue-(p->premierJoueurJoue==0)));
    }
}

/*!                                                                                       *
 * Fonction jouant le pion sur la case (ligne,colonne) et mettant à jour le damier.       *
 *                                                                                        *
 * \param p : pointeur sur la partie en cours                                             *
 * \param ligne : numéro de ligne de la case sur laquelle le pion du joueur sera posé     *
 * \param colonne : numéro de colonne de la case sur laquelle le pion du joueur sera posé */
void mouvement(struct partie *p, int ligne, int colonne)
{
    int horizontal, vertical;

	// On applique mouvementDansDirection à tous les axes depuis une case donnée en vérifiant que la case de base est bien à 0.
	if(getCase(p, ligne, colonne)==0 && coupValide(p, ligne, colonne)==1)
	{
		for(vertical=-1; vertical<=1; vertical++)
		{
			for(horizontal=-1; horizontal<=1; horizontal++)
				mouvementDansDirection(p, ligne, colonne, horizontal, vertical);
		}
	}
}

/*!                                                                                                *
 * Fonction retournant 1 si le joueur dont cest le tour peut poser un pion sur le damier, 0 sinon *
 *                                                                                                 *
 * \param p : pointeur sur la partie en cours                                                      */
int joueurPeutJouer(struct partie *p)
{
    int caseVisee, count=0;

    for(caseVisee=0; caseVisee<NB_CASES; caseVisee++)
            count+=coupValide(p, caseVisee/NB_CASES_PAR_LIGNE, caseVisee%NB_CASES_PAR_LIGNE);

    return count;
}
