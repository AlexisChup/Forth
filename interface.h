/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  interface.h
** Date     18/11/2020
** Contenu  interface de la gestion des E/S et analyse syntaxique
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include "forth.h"

// initialisation de l'interface
extern Retcode InterfaceInit();

// lire l'élément syntaxique suivant dans la ligne
// le buffer est interne à la fonction
// il ne doit PAS étre modifié
extern Retcode ElementSuivant(char **elem);

//fonction pour ignorer le reste d'une ligne
extern Retcode PurgerLigne();

// afficher une valeur
extern Retcode AfficherDonnee(Donnee val);

// afficher une chaine
extern Retcode AfficherChaine(char * str);

// afficher un caractère
extern Retcode AfficherChar(char car);

// routine d'affichage de message d'erruer
extern void AfficheErreur(Retcode code,char * mssg);

#endif
