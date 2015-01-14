#ifndef COULEURS_TERMINAL_H
#define COULEURS_TERMINAL_H

#include "stdio.h"
/*!
 * \file couleursTerminal.h
 * \author Mathieu LACROIX
 * \version 0.1
 *
 * Fichier contenant les définitions de fonction pour la coloration du terminal. Les couleurs du terminal sont codées sous forme de nombres :
 *
 *        0 = Black
 *   
 *        1 = Red
 *
 *        2 = Green   
 *
 *        3 = Yellow
 *
 *        4 = Blue    
 *
 *        5 = Magenta
 *
 *        6 = Cyan    
 *
 *        7 = White
 *
 *				9 = Couleur par défaut (blanc pour l'écriture et gris foncé pour le fond)
 *
 *
 *   Attention, il n'y a pas de couleur numéro 8. De plus, les sauts de ligne doivent être faits avec la couleur de fond par défaut.
 *
 *
 *  Pour utiliser ces fonctions dans votre code, il convient d'inclure le fichier couleursTerminal.h dans votre code grâce à l'instruction C : 
 *                  #include "couleursTerminal.h"
 *
 *  Pour compiler votre projet (si le makefile n'a pas été encore écrit), il faut compiler les deux fichiers .c , celui de votre code et le fichier 
 *  couleursTerminal.c. Si votre projet est codé dans le fichier othello.c, il convient alors, pour compiler, de lancer la commande : 
 *                  gcc -Wall othello.c couleursTerminal.c -o othello
 *
 */

 
/*!
 * Change la couleur de la police d'écriture du terminal.
 *
 * \param couleurE : entier égal à 9 ou compris entre 0 et 7
 */ 
void changerCouleurEcritureTerminal(int couleurE);

/*!
 * Change la couleur de fond du terminal
 *
 * \param couleurF : entier égal à 9 ou compris entre 0 et 7
 */ 
void changerCouleurFondTerminal(int couleurF);

/*!
 * Change la couleur de la police d'écriture et de fond du terminal.
 *
 * \param couleurE : entier égal à 9 ou compris entre 0 et 7
 * \param couleurF : entier égal à 9 ou compris entre 0 et 7
 */ 
void changerCouleursTerminal(int couleurE, int couleurF); 
 
 
 
#endif
