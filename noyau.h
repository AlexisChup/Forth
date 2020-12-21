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

// contrôle général
extern Retcode Code_Quit(); // quitte la boucle principale

// gestion de contexte
extern Retcode Code_Comm();     // imprime le TOS
extern Retcode Code_AntiSlash();    // vide la ligne en cours de lecture
extern Retcode Code_Def();      // définition d’un nouveau mot 
extern Retcode Code_Variable(); // définit une variable permanente
extern Retcode Code_Txt();      // ‘imprime’ le texte jusqu’à rencontrer le mot "

// affichage
extern Retcode Code_Dot();      // imprime le TOS
extern Retcode Code_Dots();     // affiche de la pile active
extern Retcode Code_Cr();       // affiche un retour à la ligne
extern Retcode Code_Space();    // affiche un espace
extern Retcode Code_Spaces();   // affiche <n> espaces, <n> étant la valeur du TOS
extern Retcode Code_Emit();     // affiche le TOS comme un caractère (code ascii)

// manipulation de la pile
extern Retcode Code_Drop();     // suprime le TOS
extern Retcode Code_Nip();      // suprime le NOS
extern Retcode Code_Dup();      // duplique le sommet (tos -- tos tos)
extern Retcode Code_Swap();     // échange les 2 premiers (tos nos -- nos tos)
extern Retcode Code_Over();     // recopie le NOS au TOS
extern Retcode Code_Rot();      // effectue une rotation entre les 3 premiers éléments (TOS/NOS/NNOS --> NOS/NNOS/TOS)
extern Retcode Code_MinusRot(); // effectue une rotation entre les 3 premiers éléments (TOS/NOS/NNOS --> NNOS/TOS/NOS)
extern Retcode Code_Pick();     // duplique le NOS(n) sur le TOS
extern Retcode Code_Roll();     // échange le TOS et le NOS(n)

// opérations logiques
extern Retcode Code_AskDup();   // duplique la valeur du TOS si non-zéro
extern Retcode Code_True();     // empile -1
extern Retcode Code_False();    // empile 0
extern Retcode Code_Inf();      // empile -1 si le NOS est inférieur au TOS, 0 sinon
extern Retcode Code_InfEgal();  // empile -1 si le NOS est supérieur au TOS, 0 sinon
extern Retcode Code_Egal();     // empile -1 si le NOS est égal au TOS, 0 sinon
extern Retcode Code_Diff();     // empile -1 si le NOS est différent du TOS, 0 sinon
extern Retcode Code_ZeroEgal(); // empile -1 si le TOS élément est égal à 0, 0 sinon
extern Retcode Code_ZeroDiff(); // empile -1 si le TOS élément est différent de 0, 0 sinon

// opérations mathématiques
extern Retcode Code_Negate();   // remplace le TOS par son négatif
extern Retcode Code_Plus();     // additionne le TOS et le NOS et empile le résultat
extern Retcode Code_Moins();    // empile la différence du TOS et du NOS
extern Retcode Code_Mult();     // empile le produit du TOS et du NOS
extern Retcode Code_Div();      // empile le résultat (diviseur) de la division entière du TOS et du NOS
extern Retcode Code_Mod();      // empile le reste de  la division entière du TOS et du NOS
extern Retcode Code_DivMod();   // empile le reste et le diviseur de la division entière du TOS et du NOS
extern Retcode Code_Abs();      // remplace le TOS par sa valeur absolue
extern Retcode Code_Min();      // empile le plus petit du TOS et du NOS
extern Retcode Code_Max();      // empile le plus grand du TOS et du NOS


extern Retcode Code_Get(); // lit le contenu pointé par le TOS et le met sur la pile

/*
** TODO
** ajouter les profils des autres fonctions implémentants les mots de la liste fournie
* OK 
*/

/*
** FONCTIONS INDIRECTES
** servent pour toute une famille d'entrées
** recoivent une entrée dictionnaire en référence
** manipulent la pile et le dictionnaire
*/
extern Retcode Code_RefValue(RefEntree ref); // dépose l'adresse de la valeur dans l'entrée sur le sommet de pile

#endif
