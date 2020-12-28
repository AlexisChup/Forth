/*
** Auteur   Bruno Poterie
** Projet   FORTH
** Fichier  interprete.c
** Date     18/11/2020
** Contenu  module de l'interprétation
*/

#include "forth.h"
#include "interprete.h"
#include "dictionnaire.h"
#include "interface.h"
#include "pile.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUF_SIZE 512

// buffer pour le mode string
char BufferModeString[BUF_SIZE+1];

int indexBufferModeString;

int base = 10;

Retcode BufferModeStringInit()
{
	indexBufferModeString = 0;
    BufferModeString[0] = '\0';
    return OK;
}


// variable globale pour indiquer si fini
bool finSession = false;

// variable globale pour indiquer le mode d'interprétation
InterpreteMode modeSession = MODE_EXEC;

// variable globale pour sauvegarder le mode d'interprétation
InterpreteMode ancienModeSession = MODE_EXEC;

// fonction interne : conversion d'un element en valeur numérique
Retcode tokenToNum(char * element, Donnee * val)
{
    char * fin;
	*val = (Donnee)strtol(element,&fin,base);

	if (*fin != 0) // y a-t-il eu une erreur de conversion ?
	{
		return ERR_NUM_OVERFLOW;
	}
    if (*fin != '\0')   // on vérifie si il reste des charactères
    {
        return ERR_NON_NUMERIQUE;
    }
    return OK;
}

// initialisation de l'automate
Retcode InterpreteInit()
{
	finSession = false;
	modeSession = MODE_EXEC;
	return OK;
}

// traiter une unité lexicale
Retcode Interprete(char * element)
{
	RefEntree ref; // va être renseigné par la recherche dans le dictionnaire
	Retcode ret;
	Donnee val;

	// Conversion en lettre capital, sauf si l'on est en mode string (pour ne pas modifier le texte)
	if(modeSession != MODE_STRING)
	{
		char *s = element;
		while (*s) {
			*s = toupper((unsigned char) *s);
			s++;
		}
	}

	switch (modeSession)
	{
	case MODE_EXEC:
		// mode standard - exécution immédiate
		// on commence par regarder dans le dictionnaire
		ret = DicoRecherche(element, &ref);
		// printf("retCode : %d", ret);
		if (ret == OK) // trouvé dans le dictionnaire
		{
			// on regarde le type d'entrée
			switch (ref->type)
			{
			case MOT_NOYAU:
				// y a-t-il du code associé ?
				if (!ref->code)
				{
				    return ERR_DICO_NOCODE;
                    break;
				}
				// si oui, on exécute ce code
				ret = ref->code();
				// et on retourne le code d'exécution
				return ret;
				break;
			case MOT_COMPILE:
				// type non traité
				AfficheErreur(ERR_DICO_TYPE_IGNORE,"entrée de dictionnaire de type compilé, ignoré");
				return ERR_DICO_TYPE_INCONNU;
            case MOT_VARIABLE:
               // y a-t-il du code associé ?
				if (!(ref->code))
				{
				    return ERR_DICO_NOCODE;
					break;
				}
				// si oui, on exécute ce code
				// en lui passant la référence de l'entrée en paramètre
				ret = ref->code(ref->val);
				// et on retourne le code d'exécution
				return ret;
				break;
			case MOT_ANONYME:
				// type non traité
				AfficheErreur(ERR_DICO_TYPE_IGNORE,"entrée de dictionnaire de type anonyme, ignoré");
				return ERR_DICO_TYPE_INCONNU;
			default:
				// type inconnu
				AfficheErreur(ERR_DICO_TYPE_INCONNU,"entrée de dictionnaire de type inconnu");
				return ERR_DICO_TYPE_INCONNU;
			}
		}
		else // on essaie de le convertir en donnée numérique
		{
		    ret = tokenToNum(element,&val);
			switch (ret)
            {
            case OK:    // conversion numérique réussie
                ret = PilePush(val);
                if (ret != OK) { // on vérifie que le push s'est bien passé
                    AfficheErreur(ret,"impossible d'empiler la valeur");
                    return ret;
                }
                return OK;
                break;
            case ERR_NUM_OVERFLOW:
				AfficheErreur(ERR_NUM_OVERFLOW,"débordement de conversion numérique");
				return ERR_NUM_OVERFLOW;
				break;
            default:
                AfficheErreur(ret,"mot inconnu du dictionnaire");
                return ret;
            }
		}
		break;
	case MODE_DEFVAR:
		DicoAddVar(element, &ref);
		modeSession = ancienModeSession;

		break;
	case MODE_COMM:
		// fin du commentaire
		if(!strcmp(element, "COMMEND"))
			modeSession = ancienModeSession;

		break;
	case MODE_STRING:
		if(!strcmp(element, "\""))	// fin du mode string
		{
			BufferModeString[indexBufferModeString] = '\0';

			AfficherChaine(BufferModeString);

			modeSession = ancienModeSession;
		}

		for (int i = 0; i < strlen(element); i++)
		{
			BufferModeString[indexBufferModeString] = element[i];
			indexBufferModeString ++;
		}
		
		break;

	case MODE_DEFMOT:
		AfficheErreur(ERR_MODE_IGNORE,"mode interprete non implémenté");
		return ERR_MODE_IGNORE;
		break;
	default:
		AfficheErreur(ERR_MODE_INCONNU,"mode interprete non connu");
		return ERR_MODE_INCONNU;
	}
	return OK;
}
