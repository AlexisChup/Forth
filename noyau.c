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

// CONTRÔLE GÉNÉRAL

// code DICO_QUIT
// quitte le programme principal
Retcode Code_Quit()
{
    finSession = true;
    return OK;
}

// ! GESTION DE CONTEXTE

// imprime le TOS
// TODO
Retcode Code_Comm()
{
    return ERR_NON_IMPL;
}     

// code DICO_ANTISLASH
// vide le buffer d'entrée
Retcode Code_AntiSlash()
{
    Retcode ret;
    ret = PurgerLigne();

    return ret;
}

// définition d’un nouveau mot
// TODO
Retcode Code_Def()
{
    return ERR_NON_IMPL;
}

// définit une variable permanente
// TODO
Retcode Code_Variable()
{
    return ERR_NON_IMPL;
}

// ‘imprime’ le texte jusqu’à rencontrer le mot "
// TODO
Retcode Code_Txt()
{
    return ERR_NON_IMPL;
}      


// AFFICHAGE

// code DICO_DOT
// affiche le TOS et l'enlève de la pile
Retcode Code_Dot()
{
    Donnee val;

    // on vérifie qu'il y a au moins 2 nombres au sommet
    if (PileTop() < 1)
        return ERR_PILE_VIDE;

    // pop TOS et NOS
    PilePop(&val);
    AfficherDonnee(val);

    return OK;
}

// affichage non destructif de la pile active
Retcode Code_Dots()
{
    Donnee val;
    Index indexOfTheStack = PileTop();
    Retcode ret;

    if (indexOfTheStack < 1)
        return ERR_PILE_VIDE;
        
    // index need to be a SIGNED int, otherwize the loop not working correctly
    // indeed, it will loop over negative number
    for (int index = indexOfTheStack - 1; index >= 0; index--)
    {
        ret = PileGetN(&val, index);

        if(ret != OK)
            break;

        AfficherDonnee(val);
    }
    
    return OK;
}

// affiche un retour à la ligne
Retcode Code_Cr()
{
    AfficherChar('\n');
    return OK;
}

// affiche un espace
Retcode Code_Space()
{
    AfficherChar(' ');
    return OK;
}

// affiche <n> espaces, <n> étant la valeur du TOS
Retcode Code_Spaces()
{
    Index indexOfTheStack = PileTop();

    if(indexOfTheStack > 0)
    {
        Donnee val;
        Retcode ret;

        ret = PileGetN(&val, indexOfTheStack - 1);

        if(ret != OK)
            return ERR_NON_IMPL;

        for (Donnee index = 0; index < val; index++)
            Code_Space();
        
        
        return OK;
    } else
        return ERR_PILE_VIDE;

}

// affiche le TOS comme un caractère (code ascii)
// et l'enlève de la pile
Retcode Code_Emit()
{
    Donnee val;
    // on vérifie qu'il y a au moins 2 nombres au sommet
    if (PileTop() < 1)
        return ERR_PILE_VIDE;

    // pop TOS
    PilePop(&val);

    AfficherChar((char) val);
    return OK;
}     


// ! MANIPULATION DE LA PILE

// suprime le TOS
Retcode Code_Drop()
{
    Donnee val;

    if (PileTop() < 1)
        return ERR_PILE_VIDE;

    PilePop(&val);

    return OK;
}

// suprime le NOS
Retcode Code_Nip()
{
    Donnee val;
    Index indexOfTheStack = PileTop();

    if (indexOfTheStack < 2)
        return ERR_PILE_OUT;

    PilePopN(&val, indexOfTheStack-2);

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

// recopie le NOS au TOS
Retcode Code_Over()
{
    Donnee val;
    Index indexOfTheStack = PileTop();

    if (indexOfTheStack < 2)
        return ERR_PILE_OUT;

    if (indexOfTheStack >= PileMax())
        return ERR_PILE_PLEINE;

    PileGetN(&val, indexOfTheStack-2);
    PilePush(val);

    return OK;
}

// effectue une rotation entre les 3 premiers éléments (TOS/NOS/NNOS --> NOS/NNOS/TOS)
// cas particuliers :
//  (x number of element)
//  (0 ROLL) sans effet
//  (1 ROLL) sans effet
//  (2 ROLL) équivalent à (SWAP)
//  (3 ROLL) équivalent à (ROT)
Retcode Code_Rot()
{
    Index indexOfTheStack = PileTop();

    if (indexOfTheStack == 0)
    {
        return ERR_PILE_VIDE;

    } else if (indexOfTheStack == 1)
    {
        return OK;

    } else if (indexOfTheStack == 2)
    {
        Code_Swap();
        return OK;
    } else 
    {
        Donnee val;
        PilePop(&val);
        PilePushN(val, indexOfTheStack-3);

        return OK;
    }
    
    

    return OK;
}

// effectue une rotation entre les 3 premiers éléments (TOS/NOS/NNOS --> NNOS/TOS/NOS)
// TODO
Retcode Code_MinusRot()
{
    return ERR_NON_IMPL;
}

// duplique le NOS(n) sur le TOS
// TODO
Retcode Code_Pick()
{
    return ERR_NON_IMPL;
}     

// code DICO_ROLL
// utilise le TOS comme index xN pour effectuer une rotation des xN+1 éléments suivants
// xN 0 1 2 3 ... N-1 N -> N 0 1 2 3 ... N-1
// cas particuliers :
//  (0 ROLL) sans effet
//  (1 ROLL) équivalent à (SWAP)
//  (2 ROLL) équivalent à (ROT)
// TODO
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


// ! OPÉRATIONS LOGIQUES

// duplique la valeur du TOS si non-zéro
// TODO
Retcode Code_AskDup()
{
    return ERR_NON_IMPL;
}

// empile -1
// TODO
Retcode Code_True()
{
    return ERR_NON_IMPL;
}

// empile 0
// TODO
Retcode Code_False()
{
    return ERR_NON_IMPL;
}

// empile -1 si le NOS est inférieur au TOS, 0 sinon
// TODO
Retcode Code_Inf()
{
    return ERR_NON_IMPL;
}

// empile -1 si le NOS est supérieur au TOS, 0 sinon
// TODO
Retcode Code_InfEgal()
{
    return ERR_NON_IMPL;
}

// empile -1 si le NOS est égal au TOS, 0 sinon
// TODO
Retcode Code_Egal()
{
    return ERR_NON_IMPL;
}

// empile -1 si le NOS est différent du TOS, 0 sinon
// TODO
Retcode Code_Diff()
{
    return ERR_NON_IMPL;
}

// empile -1 si le TOS élément est égal à 0, 0 sinon
// TODO
Retcode Code_ZeroEgal()
{
    return ERR_NON_IMPL;
}

// empile -1 si le TOS élément est différent de 0, 0 sinon
// TODO
Retcode Code_ZeroDiff()
{
    return ERR_NON_IMPL;
} 

/*
 ! OPÉRATIONS MATHÉMATIQUES
*/

// remplace le TOS par son négatif
// TODO
Retcode Code_Negate()
{
    return ERR_NON_IMPL;
}   

// code DICO_PLUS
// tos nos -> tos+nos
// TODO
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

// empile la différence du TOS et du NOS
// TODO
Retcode Code_Moins()
{
    return ERR_NON_IMPL;
}

// empile le produit du TOS et du NOS
// TODO
Retcode Code_Mult()
{
    return ERR_NON_IMPL;
}

// empile le résultat (diviseur) de la division entière du TOS et du NOS
// TODO
Retcode Code_Div()
{
    return ERR_NON_IMPL;
}

// empile le reste de  la division entière du TOS et du NOS
// TODO
Retcode Code_Mod()
{
    return ERR_NON_IMPL;
}

// empile le reste et le diviseur de la division entière du TOS et du NOS
// TODO
Retcode Code_DivMod()
{
    return ERR_NON_IMPL;
}

// remplace le TOS par sa valeur absolue
// TODO
Retcode Code_Abs()
{
    return ERR_NON_IMPL;
}

// empile le plus petit du TOS et du NOS
// TODO
Retcode Code_Min()
{
    return ERR_NON_IMPL;
}

// empile le plus grand du TOS et du NOS
// TODO
Retcode Code_Max()
{
    return ERR_NON_IMPL;
}      


// code DICO_GET
// lit le contenu pointé par le TOS et le met sur la pile
Retcode Code_Get()
{
    Donnee val;
    Donnee *ptr;

    // on vérifie qu'il y a au moins 2 nombres au sommet
    if (PileTop() < 1)
        return ERR_PILE_VIDE;   

    // on décompose : lire le sommet de la pile comme une donnée
    PilePop(&val);  
    // le convertir en pointeur de donnée
    ptr = (Donnee*)val;
    // lire la donnée pointée
    val = *ptr;
    // l'empliler sur le sommet de la pile
    PilePush(val);

    return OK;
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
// TODO
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
