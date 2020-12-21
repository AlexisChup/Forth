/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  forth.h
** Date     18/11/2020
** Contenu  définitions globales pour l'ensemble des modules
*/

#ifndef FORTH_H
#define FORTH_H

#define VERSION "2.0"

// les types de données manipulés par les modules :
typedef long int Donnee;        // donnée générique sur la pile et ailleurs
typedef unsigned int Index;     // rang indexé sur la pile et autres structures

// la liste des codes d'erreur internes des diverses functions
typedef enum
{
    OK = 0
    ,   ERR_NON_IMPL = -100
    ,   ERR_PILE_VIDE =	-1
    ,   ERR_PILE_PLEINE = -2
    ,   ERR_PILE_OUT = -3
    ,   ERR_DICO_INCONNU = -11
    ,   ERR_DICO_PLEIN = -12
    ,   ERR_DICO_IMPOSSIBLE = -13
    ,   ERR_DICO_DUPLICATA = -14
	,	ERR_DICO_TYPE_INCONNU = -15
	,	ERR_DICO_TYPE_IGNORE = -16
	,   ERR_DICO_NOMTROPLONG = -17
	,   ERR_DICO_NULLREF = -18
	,   ERR_DICO_NOCODE = -19
    ,   ERR_LECTURE = -21
    ,   ERR_ECRITURE = -22
    ,   ERR_EOF = -23
    ,   ERR_NON_NUMERIQUE = -24
    ,   ERR_NUM_OVERFLOW = -25
    ,   ERR_MODE_INCONNU = -31
    ,   ERR_MODE_IMBRIQUE = -32
	,	ERR_MODE_IGNORE = -33
} Retcode;

// Les valeurs booléennes en FORTH
#define FORTH_TRUE (Donnee)-1
#define FORTH_FALSE (Donnee)0

// quelques types et constantes utiles émulant C++
typedef enum { false, true } bool;
// #define NULL (void*)0 // commenté car déjà définie dans ma version de compilation (<stdio.h>)

// définitions du nombre max de mots pour le dictionnaire
#define NOMBRE_MAX_MOTS 100

#endif
