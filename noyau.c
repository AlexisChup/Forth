/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  noyau.c
** Date     18/11/2020
** Contenu  code des routines du noyau
*/

#include "forth.h"
#include "noyau.h"
#include "pile.h"
#include "dictionnaire.h"
#include "interface.h"
#include "interprete.h"
#include <stdio.h>

// code DICO_QUIT
// quitte le programme principal
Retcode Code_Quit()
{
    finSession = true;
    return OK;
}

// code DICO_DUP
// duplique  le TOS
Retcode Code_Dup()
{
    Donnee val;
    // on vérifie qu'il y a au moins 2 éléments
    if (PileTop() < 1)
        return ERR_PILE_VIDE;
    if (PileTop() >= PileMax())
        return ERR_PILE_PLEINE;
    PileGet(&val); // extraire le TOS sans le consommer
    PilePush(val); // le rajouter en TOS
    return OK;
}

// code DICO_SWAP
// échange le TOS et le NOS
Retcode Code_Swap()
{
    Donnee val;
    // on vérifie qu'il y a au moins 2 éléments
    if (PileTop() < 2)
        return ERR_PILE_VIDE;
    PilePopN(&val,1); // extraire le NOS
    PilePush(val); // le replacer en TOS
    return OK;
}

// code DICO_ROLL
// utilise le TOS comme index xN pour effectuer une rotation des xN+1 éléments suivants
// xN 0 1 2 3 ... N-1 N -> N 0 1 2 3 ... N-1
// cas particuliers :
//  (0 ROLL) sans effet
//  (1 ROLL) équivalent à (SWAP)
//  (2 ROLL) équivalent à (ROT)
Retcode Code_Roll()
{
    Donnee val;
    Index index;
    // on vérifie qu'il y a au moins un nombre au sommet
    if (PileTop() < 1)
        return ERR_PILE_VIDE;
    PilePop(&val); // extraire le TOS
    index = (Index)val; // le convertir en décalage
    // cas particulier : 0 ROLL est sans effet (autre que consommer le 0)
    // on optimise en retournant directement
    if (index == 0)
        return OK;
    // on vérifie qu'il y a au moins N+1 éléments
    if (PileTop() < index+1)
        return ERR_PILE_OUT;
    PilePopN(&val,index); // extraite le xNieme élément
    PilePush(val); // le replacer comme TOS
    return OK;
}

// code DICO_PLUS
// tos nos -> tos+nos
Retcode Code_Plus()
{
    Donnee tos,nos,resultat;
    //printf("Code_Plus()\n");
    // on vérifie qu'il y a au moins 2 nombres au sommet
    if (PileTop() < 2)
        return ERR_PILE_VIDE;
    // pop TOS et NOS
    PilePop(&tos);
    PilePop(&nos);
    resultat = tos + nos;
    PilePush(resultat);
    return OK;
}

// code DICO_DOT
// affiche le TOS
Retcode Code_Dot()
{
    Donnee val;
    //printf("Code_Dot()\n");
    // on vérifie qu'il y a au moins 2 nombres au sommet
    if (PileTop() < 1)
        return ERR_PILE_VIDE;
    // pop TOS et NOS
    PilePop(&val);
    AfficherDonnee(val);
    return OK;
}

// code DICO_SLASH
// vide le buffer d'entrée
Retcode Code_Slash()
{
    Retcode ret;
    ret = PurgerLigne();
    return ret;
}

/*
** TODO
** ajouter les autres fonctions immédiates en vous inspirant de celles ci-dessus
*/

/*
** FONCTIONS INDIRECTES ET AUTRES
** autres fonctions utilisés par l'interprétation des mots
** Il s'agit ici de fonctions communes à plusieurs mots
*/

//
// fonction à exécuter lorsque l'on interprete une variable en exécution immédiate :
// on va ajouter en sommet de pile l'adresse de la valeur de ladite variable,
// cad l'adresse du champ "valeur" de l'entrée du dictionnaire passée en paramètre
//
Retcode Code_RefValue(RefEntree ref)
{
    // cette fonction générique est celle installée dans toutes les variables
    // elle met en sommet d epile l'adresse du champ Valeur de l'entrée de dictionnaire passée en référence
    // contrôles
    Donnee val;
    if (!ref)
    {
        AfficheErreur(ERR_DICO_NULLREF,"reference nulle passée en parametre");
        return ERR_DICO_NULLREF;
    }
    if (PileTop()>=PileMax())
    {
        AfficheErreur(ERR_PILE_PLEINE,"pile pleine");
        return ERR_PILE_PLEINE;
    }
    // action
    /*
    ** TODO
    ** récuppérer l'adresse du champ "valeur" de l'entrée donnée,
    ** et la stocker dans la variable val via un transtypage :
    **      val = (Donnee)<....adresse du champ valeur...>;
    */
    PilePush(val);
    //printf("var %p:%s->%p\n",ref,ref->nom,val);
    return OK;
}
