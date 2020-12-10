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

// variable globale pour indiquer si fini
bool finSession = false;

// variable globale pour indiquer le mode d'interprétation
InterpreteMode modeSession = MODE_EXEC;

// fonction interne : conversion d'un element en valeur numérique
Retcode tokenToNum(char * element, Donnee * val)
{
    // TODO : tenir compte de la base numérique en cours (décimal, hexa, etc)
	// * OK pour celui là
    // on bloque ici en décimal
    char * fin;
	*val = (Donnee)strtol(element,&fin,10);
	printf("conv: element=%s val=%ld buff=%p fin=%p *fin=%x\n",element,*val,element,fin,*fin);

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

	// DicoAfficheTous();

	fprintf(stderr,"interp: %s - mode %d\n",element,modeSession);
	switch (modeSession)
	{
	case MODE_EXEC:
		// mode standard - exécution immédiate
		// on commence par regarder dans le dictionnaire
		ret = DicoRecherche(element, &ref);
		// printf("retCode : %d", ret);
		if (ret == OK) // trouvé dans le dictionnaire
		{
			/*
				*DEBUG
			*/
			// fprintf(stdout, "ret : %d\n", ret);
			// fprintf(stdout, "mot : %s\n ", ref->mot);
			// fprintf(stdout, "Type : %d\n", ref->type);
			// fprintf(stdout, "flag : %d\n", ref->flag);
			// fprintf(stdout, "val : %ld\n", ref->val);

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
				// ret = /* TODO exécutez le code associé à l'entrée */;
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
				if (!ref->code)
				// if (/* TODO extrayez le code associé à l'entrée, vérifiez si il existe */)
				{
				    return ERR_DICO_NOCODE;
					break;
				}
				// si oui, on exécute ce code
				// en lui passant la référence de l'entrée en paramètre
				ret = ref->code(ref->val);
				// ret = /* TODO exécutez le code associé à l'entrée */;
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
	case MODE_COMM:
	case MODE_STRING:
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
