/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  interprete.h
** Date     18/11/2020
** Contenu  interface de l'interpréteur principal
*/

#ifndef INTERPRETE_H
#define INTERPRETE_H

#include "forth.h"

// les modes de fonctionnement de l'automate d'interprétation
typedef enum { MODE_EXEC, MODE_COMM, MODE_STRING, MODE_DEFMOT, MODE_DEFVAR } InterpreteMode;

// variable globale pour indiquer si fini
extern bool finSession;

// initialisation de l'automate
extern Retcode InterpreteInit();

// traiter une unité lexicale
extern Retcode Interprete(char * element);

#endif
