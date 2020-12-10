/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  pile.h
** Date     18/11/2020
** Contenu  interface de la gestion de la pile de données
*/

#ifndef PILE_H
#define PILE_H

#include "forth.h"

#define MAX_PILE_D 100 // taille de la pile de données

extern Retcode PileInit();	// (ré)initialise la pile de données

extern Retcode PilePush(Donnee val); // ajoute la valeur en paramètre sur le sommet de la pile. Retourne 0 si OK, un code d'erreur sinon
extern Retcode PilePop(Donnee *val); // retire la valeur du sommet de la pile et la retourne via le paramètre. Retourne 0 si OK; un code d'erreur sinon
extern Retcode PileGet(Donnee *val); // récupére la valeur au sommet de la pile et la renvoie via le paramètre. Renvoie 0 si OK; un code d'erreur sinon

extern Retcode PilePushN(Donnee val, Index index); // insére la valeur passée au-dessus de l'élément indiqué par l'index. PushN(val,0) == Push(val). Retour idem
extern Retcode PilePopN(Donnee *val, Index index); // renvoie et retire l'élément indiqué par l'index. PopN(val,0) == Pop(val). Retour idem
extern Retcode PileGetN(Donnee *val, Index index); // récupére la valeur de l'élément indiqué par l'index. GetN(val,0) == Get(val). Retour idem

extern Index PileMax(); // retourne la nombre maximum d'éléments dans la pile
extern Index PileTop(); // retourne le nombre d'éléments actifs dans la pile

#endif
