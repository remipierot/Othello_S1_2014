#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "couleursTerminal.h"
#include "othello.h"

/*!                                                                                               *
 * Fonction retournant la valeur de validite des noms de la partie p (1 s'ils sont bons, 0 sinon) *
 * On formate également les noms saisis (Majuscule au début, le reste en minuscule).              *
 *                                                                                                *
 * \param p : pointeur sur la partie en cours                                                     */
int verificationNom(struct partie *p)
{
    if(p!=NULL)
    {
        int i, count=0;

        for(i=0; p->nomJ1[i]!='\0'; i++)
        {
            if(i==0)
            {
                p->nomJ1[i]=toupper(p->nomJ1[i]);
                p->nomJ2[i]=toupper(p->nomJ2[i]);
            }
            else
            {
                p->nomJ1[i]=tolower(p->nomJ1[i]);
                p->nomJ2[i]=tolower(p->nomJ2[i]);
            }

            if(p->nomJ1[i]!=p->nomJ2[i])
                count++;

            if((p->nomJ1[i]<'A' || p->nomJ1[i]>'Z') && (p->nomJ1[i]<'a' || p->nomJ1[i]>'z') && (p->nomJ1[i]<'0' || p->nomJ1[i]>'9'))
               return 0;
        }

        for(i=0; p->nomJ2[i]!='\0'; i++)
        {
	    if(i==0)
            {
                p->nomJ1[i]=toupper(p->nomJ1[i]);
                p->nomJ2[i]=toupper(p->nomJ2[i]);
            }
            else
            {
                p->nomJ1[i]=tolower(p->nomJ1[i]);
                p->nomJ2[i]=tolower(p->nomJ2[i]);
            }

            if(p->nomJ2[i]!=p->nomJ1[i])
                count++;

            if((p->nomJ2[i]<'A' || p->nomJ2[i]>'Z') && (p->nomJ2[i]<'a' || p->nomJ2[i]>'z') && (p->nomJ2[i]<'0' || p->nomJ2[i]>'9'))
               return 0;
        }

        if(count!=0)
            return 1;

        return 0;
    }
    return 0;
}

/*!                                                                                           *
 * Fonction retournant la valeur de validite d'un nom de sauvegarde (1 s'il est bon, 0 sinon) *
 *                                                                                            *
 * \param nom : nom de la sauvegarde à vérifier                                               */
int verificationSave(char nom[])
{
    int i;

    for(i=0; nom[i]!='\0'; i++)
    {
        if((nom[i]<'A' || nom[i]>'Z') && (nom[i]<'a' || nom[i]>'z') && (nom[i]<'0' || nom[i]>'9'))
           return 0;
    }
    return 1;
}

/*!                                                                         *
 * Fonction retournant la valeur de la case (ligne, colonne) de la partie p *
 *                                                                          *
 * \param p : pointeur sur la partie en cours                               *
 * \param ligne : entier compris entre [0, NB_CASES_PAR_LIGNE-1]            *
 * \param colonne : entier compris entre [0, NB_CASES_PAR_LIGNE-1]          */
int getCase(struct partie *p, int ligne, int colonne)
{
    /* On vérifie la validité des paramètres, si l'un d'entre eux ne l'est pas on renvoie 2 (valeur naturellement inexistante dans le damier). *
     * Sinon, on renvoie la valeur de la case.                                                                                                 */
    if(p==NULL || ligne<0 || ligne>=NB_CASES || colonne<0 || colonne>=NB_CASES)
        return 2;

    return p->damier[colonne+(ligne*NB_CASES_PAR_LIGNE)];
}

/*!                                                                       *
 * Fonction modifiant la valeur de la case (ligne,colonne) de la partie p *
 *                                                                        *
 * \param p : pointeur sur la partie en cours                             *
 * \param ligne : entier compris entre [0,NB_CASES_PAR_LIGNE-1]           *
 * \param colonne : entier compris entre [0,NB_CASES_PAR_LIGNE-1]         *
 * \param valeur : entier compris entre [-1,1]                            */
void setCase(struct partie *p, int ligne, int colonne, int valeurAffectee)
{
    // On vérifie la validité des paramètres, s'ils le sont tous on affecte la valeur reçue à la case voulue.
    if(p!=NULL && ligne>=0 && ligne<NB_CASES && colonne>=0 && colonne<NB_CASES && valeurAffectee>=-1 && valeurAffectee<=1)
        p->damier[colonne+(ligne*NB_CASES_PAR_LIGNE)]=valeurAffectee;
}

/*!                                                *
 * Fonction changeant le joueur dont cest le tour *
 *                                                 *
 * \param p : pointeur sur la partie en cours      */
void changementJoueur(struct partie *p)
{
    if(p!=NULL)
        p->premierJoueurJoue=1-p->premierJoueurJoue;
}

/*!                                                                                 *
 * Fonction créant une partie.                                                      *
 * Allocation dynamique dune variable de type partie dont ladresse est retournée. *
 * Le champ damier de la variable retournée doit correspondre à une configuration   */
struct partie* creerPartie()
{
    // On utilise un calloc pour avoir un espace mémoire réservé qui soit vidé, de façon à éviter l'utilisation d'une boucle d'initialisation du damier.
    struct partie *p=(partie*)calloc(sizeof(struct partie), 1);
	int i;

    do{
        printf("\nNom du premier Joueur : ");
        scanf("%s", p->nomJ1);
        printf("Nom du second Joueur : ");
        scanf("%s", p->nomJ2);

        if(verificationNom(p)==0)
            printf("\nAu moins l'un des noms saisis est invalide.\nVous devez utilisez des caracteres autorises. (a-z, A-Z, 1-9)\nDe plus, vous ne pouvez pas avoir deux fois le meme pseudo.\nVeuillez donc entrer des noms valides.\n");
    }while(verificationNom(p)==0);

	for(i=0; i<4; i++)
		p->damier[(i<=1)*(27+(i==1))+(i>=2)*(36-(i==3))]=((i%2)!=0)-((i%2)==0);

    p->premierJoueurJoue=1;

    return p;
}

/*!                                                             *
 * Fonction affichant le damier sur le terminal                 *
 *                                                              *
 * \param p : pointeur sur la partie que lon souhaite afficher */
void affichage(struct partie * p)
{
    int ligne, colonne, casePaireImpaire, couleur;

    if(p!=NULL)
    {
        // On utilise 9 lignes et 9 colonnes pour afficher les identifiants des cases en plus du damier (A-H et 1-8).
        for(ligne=0; ligne<9; ligne++)
        {
            // On utilise 9*3=27 colonnes car on va afficher 3 'sous-lignes' pour chaque ligne afin de donner de la hauteur aux cases.
            for(colonne=0; colonne<27; colonne++)
            {
                casePaireImpaire=((colonne%9-ligne)%2==0);
                couleur=1+(casePaireImpaire*2);

                // On vérifie que l'on se trouve bien sur le damier et non sur ce qui identifie les cases (A-H et 1-8) avant de changer la couleur.
                if(ligne>0 && colonne%9!=0)
                    changerCouleursTerminal(couleur, couleur);

                // Avant un retour à la ligne on remet la couleur du terminal à son origine pour éviter d'avoir toute une fin de ligne colorée.
                if(colonne%9==0)
                {
                    changerCouleursTerminal(9, 9);
                    printf("\n");
                }

                // Ici on affiche simplement le damier.
                if(colonne==9 && ligne>0)
                    printf("   %c   ", 'A'+ligne-1);
                else if(colonne<=9 || colonne>17 )
                    printf("       ");
                else if(ligne==0)
                    printf("   %d   ", colonne-9);
                else
                {
                    printf("  ");

                    // Si la case n'est pas vide, on lui applique un changement de couleur en fonction de sa valeur.
                    if(getCase(p, ligne-1, colonne-10)!=0 && colonne>8 && colonne<18)
                        changerCouleursTerminal(7-(7*(getCase(p, ligne-1, colonne-10)==1)), 7-(7*(getCase(p, ligne-1, colonne-10)==1)));
		    else if(coupValide(p, ligne-1, colonne-10)!=0)
			 changerCouleurEcritureTerminal(7-(7*(p->premierJoueurJoue==1)));

                    printf(" * ");
                    changerCouleursTerminal(couleur, couleur);
                    printf("  ");
                }
            }
        }
        changerCouleursTerminal(9, 9);
        printf("\n\n");
    }
}
