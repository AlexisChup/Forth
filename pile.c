#include <stdio.h>
#include "pile.h"

Donnee stack[MAX_PILE_D];   // pile de données
Index indexOfTheStack;      // index dans la pile de données

Retcode PileInit()
{
    indexOfTheStack = 0;

    for (Index index = 0; index < MAX_PILE_D; index++)
    {
        stack[index] = (Donnee)(NULL);
    }

    return OK;
}

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

Retcode PilePushN(Donnee val, Index index)
{
    if(index <= indexOfTheStack && indexOfTheStack < MAX_PILE_D)
    {
        for (unsigned int index = indexOfTheStack; index > index - 1; index--)
        {
            stack[index] = stack[index-1];
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

Index PileMax()
{
    return MAX_PILE_D;
}

Index PileTop()
{
    return indexOfTheStack;
}