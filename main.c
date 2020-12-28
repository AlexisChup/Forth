/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  main.c
** Date     18/11/2020
*/

#include "forth.h"
#include "pile.h"
#include "dictionnaire.h"
#include "interprete.h"
#include "interface.h"

#include <stdio.h>

int main(int argc, char * argv[])
{
    char *element;
    Retcode ret;

    printf("Micro-Forth ESEO v%s\n",VERSION);

    // phase d'initialisation
    InterfaceInit();
    PileInit();
    DicoInit();
    InterpreteInit();

    // boucle générale
    // lire les mots au clavier
    // les interpreter
    while (finSession==false)
    {
        ret=ElementSuivant(&element);

        switch (ret)
        {
        case OK:
            ret = Interprete(element);
            if (ret != OK){
                PurgerLigne(); //si erreur, on oublie le reste de la ligne d'entré
                AfficheErreur(ret,"erreur lors de l'interpretation");
            }
            break;
        case ERR_EOF:
            finSession = true;
            break;
        default:
            AfficheErreur(ret,"erreur dans la lecture du token suivant");
        }
    }

    printf("Au revoir\n");
    return 0;
}
