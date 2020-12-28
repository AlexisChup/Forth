#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionnaire.h"
#include "noyau.h"

// déclaration du dictionnaire de mots
RefEntree Dico[NOMBRE_MAX_MOTS];
Index indexDico;

// initialise le dictionnaire et charge les entrées "système"
Retcode DicoInit() 
{
    // initialisation de l'index dans le dictionnaire
    indexDico = 0;

    for (Index index = 0; index < NOMBRE_MAX_MOTS; index++)
    {
        Dico[index] = (RefEntree)(NULL);
    }

    // on ajoute tous les mots du noyau

    // CONTRÔLE GÉNÉRAL
    DicoAdd("QUIT", MOT_NOYAU, DICO_QUIT, DICO_NOYAU, 0L, &Code_Quit, NULL);

    // GESTION DE CONTEXTE
    DicoAdd("BASE", MOT_VARIABLE, DICO_NONE, DICO_SYSVAR, 10L, &Code_RefValue, NULL);
    DicoAdd("\\", MOT_NOYAU, DICO_ANTISLASH, DICO_NOYAU, 0L, &Code_AntiSlash, NULL);
    DicoAdd("COMMBEGIN", MOT_NOYAU, DICO_COMM, DICO_NOYAU, 0L, &Code_Comm, NULL);
    DicoAdd(".\"", MOT_NOYAU, DICO_TXT, DICO_NOYAU, 0L, &Code_Txt, NULL);
    DicoAdd("VARIABLE", MOT_NOYAU, DICO_VARIABLE, DICO_NOYAU, 0L, &Code_Variable, NULL);

    // AFFICHAGE
    DicoAdd(".", MOT_NOYAU, DICO_DOT, DICO_NOYAU, 0L, &Code_Dot, NULL);
    DicoAdd(".S", MOT_NOYAU, DICO_DOTS, DICO_NOYAU, 0L, &Code_Dots, NULL);
    DicoAdd("CR", MOT_NOYAU, DICO_CR, DICO_NOYAU, 0L, &Code_Cr, NULL);
    DicoAdd("SPACE", MOT_NOYAU, DICO_SPACE, DICO_NOYAU, 0L, &Code_Space, NULL);
    DicoAdd("SPACES", MOT_NOYAU, DICO_SPACES, DICO_NOYAU, 0L, &Code_Spaces, NULL);
    DicoAdd("EMIT", MOT_NOYAU, DICO_EMIT, DICO_NOYAU, 0L, &Code_Emit, NULL);
    
    // MANIPULATION DE LA PILE
    DicoAdd("DROP", MOT_NOYAU, DICO_DROP, DICO_NOYAU, 0L, &Code_Drop, NULL);
    DicoAdd("NIP", MOT_NOYAU, DICO_NIP, DICO_NOYAU, 0L, &Code_Nip, NULL);
    DicoAdd("DUP", MOT_NOYAU, DICO_DUP, DICO_NOYAU, 0L, &Code_Dup, NULL);
    DicoAdd("SWAP", MOT_NOYAU, DICO_SWAP, DICO_NOYAU, 0L, &Code_Swap, NULL);
    DicoAdd("OVER", MOT_NOYAU, DICO_OVER, DICO_NOYAU, 0L, &Code_Over, NULL);
    DicoAdd("ROT", MOT_NOYAU, DICO_ROT, DICO_NOYAU, 0L, &Code_Rot, NULL);
    DicoAdd("-ROT", MOT_NOYAU, DICO_MINUSROT, DICO_NOYAU, 0L, &Code_MinusRot, NULL);
    DicoAdd("ROLL", MOT_NOYAU, DICO_ROLL, DICO_NOYAU, 0L, &Code_Roll, NULL);
    DicoAdd("PICK", MOT_NOYAU, DICO_PICK, DICO_NOYAU, 0L, &Code_Pick, NULL);
    
    // OPÉRATIONS LOGIQUES
    DicoAdd("?DUP", MOT_NOYAU, DICO_ASKDUP, DICO_NOYAU, 0L, &Code_AskDup, NULL);
    DicoAdd("TRUE", MOT_NOYAU, DICO_TRUE, DICO_NOYAU, 0L, &Code_True, NULL);
    DicoAdd("FALSE", MOT_NOYAU, DICO_FALSE, DICO_NOYAU, 0L, &Code_False, NULL);
    DicoAdd("<", MOT_NOYAU, DICO_INF, DICO_NOYAU, 0L, &Code_Inf, NULL);
    DicoAdd(">", MOT_NOYAU, DICO_SUP, DICO_NOYAU, 0L, &Code_Sup, NULL);
    DicoAdd("=", MOT_NOYAU, DICO_EGAL, DICO_NOYAU, 0L, &Code_Egal, NULL);
    DicoAdd("<>", MOT_NOYAU, DICO_DIFF, DICO_NOYAU, 0L, &Code_Diff, NULL);
    DicoAdd("0=", MOT_NOYAU, DICO_ZEROEGAL, DICO_NOYAU, 0L, &Code_ZeroEgal, NULL);
    DicoAdd("0<>", MOT_NOYAU, DICO_ZERODIFF, DICO_NOYAU, 0L, &Code_ZeroDiff, NULL);

    // OPÉRATIONS MATHÉMATIQUES
    DicoAdd("NEGATE", MOT_NOYAU, DICO_NEGATE, DICO_NOYAU, 0L, &Code_Negate, NULL);
    DicoAdd("+", MOT_NOYAU, DICO_PLUS, DICO_NOYAU, 0L, &Code_Plus, NULL);
    DicoAdd("-", MOT_NOYAU, DICO_MOINS, DICO_NOYAU, 0L, &Code_Moins, NULL);
    DicoAdd("*", MOT_NOYAU, DICO_MULT, DICO_NOYAU, 0L, &Code_Mult, NULL);
    DicoAdd("/", MOT_NOYAU, DICO_DIV, DICO_NOYAU, 0L, &Code_Div, NULL);
    DicoAdd("MOD", MOT_NOYAU, DICO_MOD, DICO_NOYAU, 0L, &Code_Mod, NULL);
    DicoAdd("/MOD", MOT_NOYAU, DICO_DIVMOD, DICO_NOYAU, 0L, &Code_DivMod, NULL);
    DicoAdd("ABS", MOT_NOYAU, DICO_ABS, DICO_NOYAU, 0L, &Code_Abs, NULL);
    DicoAdd("MIN", MOT_NOYAU, DICO_MIN, DICO_NOYAU, 0L, &Code_Min, NULL);
    DicoAdd("MAX", MOT_NOYAU, DICO_MAX, DICO_NOYAU, 0L, &Code_Max, NULL);
    DicoAdd("@", MOT_NOYAU, DICO_GET, DICO_NOYAU, 0L, &Code_Get, NULL);

    return OK;
}

// indifférent à maj./min.Retourne dans ptr l'adresse de l'entrée si trouvée
// renvoie 0 si trouvé, un code d'erreur sinon
Retcode DicoRecherche(char * mot, RefEntree *refptr)
{
    RefEntree ref;

    if(indexDico > 0)
    {
        for (Index i = 0; i < indexDico; i++)
        {
            ref = Dico[i];
            if(!strcmp(mot, ref->mot))
            {
                *refptr = ref;

                return OK;
            }
        }
        // le mot est inconnu
        return ERR_DICO_INCONNU;
    } else {
        return ERR_PILE_VIDE;
    }
    
}

// ajoute une entrée au dictionnaire
// initialise les éléments de l'entrée avec les paramètres
// renvoie l'adresse de l'entrée via le double pointeur refptr (vérifier avant que le pointeur passé n'est pas null)
// ne vérifie pas si il y a doublon
// vérifie la taille du mot en entrée
Retcode DicoAdd(char * mot,TypeMot type,IdNoyau id,int flag,Donnee val,CodeMot code,RefEntree *refptr)
{
    RefEntree ref = malloc(sizeof(Entree));

    // ajouter tous les champs de l'entrée
    ref->mot = mot;
    ref->type = type;
    ref->code = code;
    ref->val = val;
    ref->flag = flag;
    
    Dico[indexDico] = ref;
    indexDico += 1;

    // on renvoie l'adresse si refptr n'est pas nulle
    if(refptr != NULL)
        *refptr = ref;

    return OK;
}

// cas particulier de DicoAdd : ajout d'une entrée de type variable
// la fonction dont on passera l'adresse pour créer l'entrée (paramètre code de DicoAdd())
// est Code_RefValue() (définie dans noyau.h)
Retcode DicoAddVar(char * mot, RefEntree *refptr)
{
    RefEntree ref = malloc(sizeof(Entree));

    // ajouter tous les champs de l'entrée
    ref->mot = mot;
    ref->code = &Code_RefValue;

    Dico[indexDico] = ref;
    indexDico += 1;

    // on renvoie l'adresse si refptr n'est pas nulle
    if(refptr != NULL)
        *refptr = ref;

    return OK;
}

// suppression de la part du dictionnaire postérieur à l'entrée, y incluse (au sens de plus récent)
Retcode DicoSupp(RefEntree ref)
{
	Retcode ret;

    ret = DicoRecherche(ref->mot, &ref);

    if(ret != OK)
    {
        // cela veut soit dire que le nom n'existe pas
        // ou bien que le dictionnaire est vide
        // sachant que la fonction DicoRecherche s'occupe déjà
        // de renvoyer le bon code d'erreur, on peut simplement
        // renvoyer ret
        return ret;
    }

    // le mot existe bien et on le supprime
    RefEntree refptr;
    bool isWordFound = false;
    for (Index i = 0; i < indexDico; i++)
    {
        refptr = Dico[i];
        if(!strcmp(ref->mot, refptr->mot))
        {
            // on a trouvé où se trouve le mot dans le dictionnaire
            // on va maintenant déplacer chaque élément
            isWordFound = true;
        }

        if(isWordFound)
        {
            // on recule chaque élément
            Dico[i-1] = Dico[i];
        }
    }

    indexDico --;
    return OK;
}