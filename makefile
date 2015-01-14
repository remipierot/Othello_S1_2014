all: othello

othello: othello.o jeu.o organisation.o sauvegarde.o menu.o couleursTerminal.o
	gcc othello.o jeu.o organisation.o sauvegarde.o menu.o couleursTerminal.o -o othello
 
othello.o: othello.c othello.h
	gcc -c othello.c -o othello.o
 
jeu.o: jeu.c othello.h
	gcc -c jeu.c -o jeu.o

couleursterminal.o: couleursTerminal.c othello.h couleursTerminal.h
	gcc -c couleursTerminal.c -o couleursTerminal.o

organisation.o: organisation.c othello.h couleursTerminal.h
	gcc -c organisation.c -o organisation.o

sauvegarde.o: sauvegarde.c othello.h
	gcc -c sauvegarde.c -o sauvegarde.o

menu.o: menu.c othello.h
	gcc -c menu.c -o menu.o

clean:
	rm -rf *o othello
