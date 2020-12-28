#include <stdio.h>
#include "pile.h"

Donnee stack[MAX_PILE_D];   // pile de données
Index indexOfTheStack;      // index dans la pile de données

// (ré)initialise la pile de données
Retcode PileInit()
{
    indexOfTheStack = 0;

    for (Index index = 0; index < MAX_PILE_D; index++)
    {
        stack[index] = (Donnee)(NULL);
    }

    return OK;
}

// ajoute la valeur en paramètre sur le sommet de la pile. Retourne 0 si OK, un code d'erreur sinon
Retcode PilePush(Donnee val)
{
    if(indexOfTheStack < MAX_PILE_D)
    {
        stack[indexOfTheStack] = val;
        indexOfTheStack += 1;

        return OK;
    } else 
    {
        printf("Stack overflow !\n");

        return ERR_PILE_PLEINE;
    }
}

// retire la valeur du sommet de la pile et la retourne via le paramètre. Retourne 0 si OK; un code d'erreur sinon
Retcode PilePop(Donnee *val)
{
    if(indexOfTheStack > 0)
    {
        PileGet(val);
        indexOfTheStack -= 1;

        return OK;
    } else 
    {
        *val = (Donnee)(NULL);
        printf("The Stack is empty !\n");

        return ERR_PILE_VIDE;
    }
}

// récupére la valeur au sommet de la pile et la renvoie via le paramètre. Renvoie 0 si OK; un code d'erreur sinon
Retcode PileGet(Donnee *val)
{
    if(indexOfTheStack > 0)
    {
        *val = stack[indexOfTheStack -1];

        return OK;
    }
    else
    {
        *val = (Donnee)(NULL);
        printf("The Stack is empty !, indexStack : %d\n", indexOfTheStack);

        return ERR_PILE_VIDE;
    }
}

// insére la valeur passée au-dessus de l'élément indiqué par l'index. PushN(val,0) == Push(val). Retour idem
Retcode PilePushN(Donnee val, Index index)
{
    if(index <= indexOfTheStack && indexOfTheStack < MAX_PILE_D)
    {
        for (unsigned int i = indexOfTheStack; i > index - 1; i--)
        {
            stack[i] = stack[i-1];
        }
        
        stack[index] = val;
        indexOfTheStack += 1;

        return OK;
    } else 
    {
        printf("You must insert a number with an index :\n\t0 =< index =< %d\n", indexOfTheStack);
        printf("That's why %d isn't correct\n", index);

        return ERR_NON_IMPL;
    }
}

// renvoie et retire l'élément indiqué par l'index. PopN(val,0) == Pop(val). Retour idem
Retcode PilePopN(Donnee *val, Index index)
{
    if(index <= indexOfTheStack-1 && indexOfTheStack > 0)
    {
        *val = stack[index];

        for (unsigned int i = index ; i < indexOfTheStack; i++)
        {
            stack[i] = stack[i+1];
        }

        indexOfTheStack -= 1;

        return OK;
    } else 
    {
        *val = (Donnee)(NULL);
        printf("There is no value in stack for index : %d\n", index);
        
        return ERR_NON_IMPL;
    }
}

// récupére la valeur de l'élément indiqué par l'index. GetN(val,0) == Get(val). Retour idem
Retcode PileGetN(Donnee *val, Index index)
{
    if(index < indexOfTheStack && indexOfTheStack > 0)
    {
        *val = stack[index];

        return OK;
    }
    else
    {
        *val = (Donnee)(NULL);
        printf("There is no value in stack for index : %d\n", index);
        
        return ERR_NON_IMPL;
    }
}

// retourne la nombre maximum d'éléments dans la pile
Index PileMax()
{
    return MAX_PILE_D;
}

// retourne le nombre d'éléments actifs dans la pile
Index PileTop()
{
    return indexOfTheStack;
}