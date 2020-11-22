/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  noyau.h
** Date     18/11/2020
** Contenu  interface des routines du noyau
*/

#ifndef PILE_EXTRA_H
#define PILE_EXTRA_H

#include "forth.h"
#include "dictionnaire.h"

/*
** Ce module contient la collection des routines internes qui implémentent
** les mots du vocabulaire demandé. Toutes les fonctions ont le même profil :
**      Retcode <fonc>();
** qui est défini par :
**  typedef Retcode (*CodeMot)();
** Le dit type est utilisé pour passer l'adresse de ces fonctions à d'autres fonctions.
*/

/*
** TOS = Top Of Stack = sommet de la pile
** NOS = Next Of Stack = suivant sur la pile
** NNOS = Next of Next Of Stack = troisième sur la pile (etc)
** NOS(n) = Niéme élément sous le TOS [NOS(0) == TOS, NOS(1)==NOS, ...
*/

/*
** FONCTIONS DIRECTES
** une fonction distincte par mot système
** pas de paramètre
** utilisent la pile et les E/S seulement
*/

extern Retcode Code_Quit(); // quitte la boucle principale
extern Retcode Code_Dup(); // duplique le sommet (tos -- tos tos)
extern Retcode Code_Swap(); // échange les 2 premiers (tos nos -- nos tos)
extern Retcode Code_Roll(); // échange le TOS et le NOS(n)
extern Retcode Code_Plus(); // additionne le TOS et le NOS et empile le résultat
extern Retcode Code_Dot(); // imprime le TOS
extern Retcode Code_Slash(); // vide la ligne en cours de lecture
/*
** TODO
** ajouter les profils des autres fonctions implémentants les mots de la liste fournie
*/

/*
** FONCTIONS INDIRECTES
** servent pour toute une famille d'entrées
** recoivent une entrée dictionnaire en référence
** manipulent la pile et le dictionnaire
*/
extern Retcode Code_RefValue(RefEntree ref); // dépose l'adresse de la valeur dans l'entrée sur le sommet de pile

#endif
