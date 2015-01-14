#include "couleursTerminal.h"

void changerCouleursTerminal(int couleurE, int couleurF)
{
		printf("\E[%dm", couleurE+30);
		printf("\E[%dm", couleurF+40);   
}

void changerCouleurFondTerminal(int couleurF)
{
	printf("\E[%dm", couleurF+40);   
}

void changerCouleurEcritureTerminal(int couleurE)
{
	printf("\E[%dm", couleurE+30);
}
