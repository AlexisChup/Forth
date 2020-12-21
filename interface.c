/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  interface.c
** Date     18/11/2020
** Contenu  gestion des E/S et analyse syntaxique
*/

#include "forth.h"
#include "interface.h"
#include "dictionnaire.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// taille max du buffer d'entrée
#define BUF_SIZE 512
// buffer d'entrée (ligne)
char Buffer[BUF_SIZE+1];
// buffer d'entrée (token)
char Element[BUF_SIZE+1];
// pointeur de parcours du buffer
char * Prev;
// chaine constante de délimitation syntaxe
const char * Delims = " \t\n";

Retcode InterfaceInit()
{
    Buffer[0] = '\0';
    Element[0] = '\0';
    Prev = NULL;
    return OK;
}

// fonction interne
Retcode lireLigne()
{
    char * retb;
    int buflen;
    Retcode ret;
    RefEntree ref;

	Prev = NULL; // positionne le pointeur de parcours

    // prompt à rendre optionnel
    // ret = DicoRecherche("PROMPT", &ref);
    // if (ret == OK)
    // {
	    // fprintf(stdout,"%ld", ref->val);
    // } else {
    fprintf(stdout,">>");
    // }

	// lecture du buffer ligne
	retb = fgets(Buffer,BUF_SIZE+1,stdin);

	// vérification d'erreur
	if (!retb)
    {
        // est-ce la fin de fichier ?
        if (feof(stdin))
            return ERR_EOF;
        else
            return ERR_LECTURE;
    }
    buflen = strlen(Buffer);
    // ligne vide
    if (buflen == 0)
        return OK;
    // on teste ligne trop longue
    // le risque est d'avoir un mot tronqué
	if (buflen >= BUF_SIZE)
    {
        AfficheErreur(ERR_LECTURE,"ligne en entrée trop longue");
        return ERR_LECTURE;
    }
    // éliminer un éventuel EOL laissé par la lecture
    if (Buffer[buflen-1] == '\n')
        Buffer[buflen-1] = '\0';
    return OK;
}

// lire l'élément syntaxique suivant dans la ligne
Retcode ElementSuivant(char **elem)
{
	char * token;   // element lu
	Retcode ret;    // code erreur

	// on boucle jusqu'à lire un token, y compris en lisant de nouvelles lignes
    do
    {// lire le token suivant
        if (Prev == NULL) // on est en début de ligne
            token = strtok(Buffer,Delims);
        else    // ou en milieu (Prev est le token précédent)
            token = strtok(NULL,Delims);
        // si ligne finie, on passe à la suivante
        if (!token)
        {
            // on lit la ligne suivante
            ret = lireLigne();
            if (ret == ERR_EOF)
            {
                // en cas de fin de fichier, on renvoie de suite
                *elem = Element; // pour éviter de pointer sur n'importe quoi
                return ERR_EOF;
            }
            if (ret != OK)
            {
                *elem = Element;
                return ret;
            }
            // et on va recommencer la lecture de l'élément suivant
        }
    } while (!token);
    // une fois un token valable lu, on le renvoie
    Prev = token;
	strncpy(Element,token,BUF_SIZE);
    *elem = Element;
    return OK;
}

//fonction pour ignorer le reste d'une ligne
Retcode PurgerLigne()
{
    Buffer[0] = '\0';
    Prev = NULL;
    return OK;
}


// afficher une valeur
Retcode AfficherDonnee(Donnee val)
{
    fprintf(stdout,"%ld\n",val);
    return OK;
}

// afficher une chaine
Retcode AfficherChaine(char * str)
{
    fprintf(stdout,"%s\n",str);
    return OK;
}

// afficher un caractère
Retcode AfficherChar(char car)
{
    fprintf(stdout,"%c",car);
    return OK;
}

void AfficheErreur(Retcode code,char * mssg)
{
    fprintf(stderr,"%d : %s\n",code,mssg);
}
