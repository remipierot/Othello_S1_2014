#ifndef OTHELLO_H
#define OTHELLO_H

#define TAILLE_CH 256
#define NB_CASES 64
#define NB_CASES_PAR_LIGNE 8

typedef struct partie
{
	int damier[NB_CASES];
    	char nomJ1[TAILLE_CH];
    	char nomJ2[TAILLE_CH];
    	int premierJoueurJoue;
} partie;

int priseDansDirectionPossible(partie *p, int ligne, int colonne, int horizontal, int vertical);
int coupValide(partie *p, int ligne, int colonne);
void mouvementDansDirection(partie *p, int ligne, int colonne, int horizontal, int vertical); 
void mouvement(partie *p, int ligne, int colonne);
int joueurPeutJouer(partie *p);
int verificationNom(partie *p);
int verificationSave(char nom[]);
int getCase(partie *p, int ligne, int colonne); 
void setCase(partie *p, int ligne, int colonne, int valeurAffectee);
void changementJoueur(partie *p);
partie* creerPartie();
void affichage(partie * p);
void makeSave();
int sauvegardePartie(partie *p);
int chargementPartie(partie *p); 
int menu(partie *p);
int saisieJoueur (int *ligne, int *colonne);
int tourJoueur(partie *p);
int gagnant(partie *p); 
int finPartie (partie *p);
int jouerPartie (partie *p);

#endif
