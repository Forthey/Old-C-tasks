/* Drekalov Nikita, 09-4, 15.11.2019 */
#include <stdio.h>

#include "bst.h"

/* Check or add key funtion */
INT AccessTree( TREE **T, INT Key )
{
  if (*T == NULL)
  {
    /* Add new */
    *T = malloc(sizeof(TREE));
    if (*T == NULL)
    {
      printf("Not enough memory\n");
      return 0;
    }
    (*T)->Key = Key;
    (*T)->Less = (*T)->More = NULL;
    printf("Add a new key\n");
    return 1;
  }
  if ((*T)->Key == Key)
  {
    printf("Key %i is found\n", Key);
    return 1;
  }
  if ((*T)->Key < Key)
    return AccessTree(&(*T)->More, Key);
  return AccessTree(&(*T)->Less, Key);
} /* End of 'AccessTree' function */

INT AccessTree1( TREE **T, INT Key )
{
  if (*T == NULL)
  {
    /* Add new */
    *T = malloc(sizeof(TREE));
    if (*T == NULL)
    {
      printf("Not enough memory\n");
      return 0;
    }
    (*T)->Key = Key;
    (*T)->Less = (*T)->More = NULL;
    printf("Add a new key\n");
    return 1;
  }
  if ((*T)->Key == Key)
  {
    printf("Key %i is found\n", Key);
    return 1;
  }

  while (*T != NULL && (*T)->Key != Key)
   if ((*T)->Key < Key)
     T = &(*T)->More;
   else
     T = &(*T)->Less;

  return T != NULL;
}

VOID DrawTree( TREE *T )
{
  static INT Level;

  Level++;
  if (T != NULL)
  {
    DrawTree(T->More);
    printf("%*c%d\n", Level * 3, ' ', T->Key);
    DrawTree(T->Less);
  }
  Level--;
}

VOID ClearTree( TREE **T )
{
  if (*T != NULL)
  {
    ClearTree(&(*T)->More);
    ClearTree(&(*T)->Less);
    free(*T);
    *T = NULL;
  }
}

VOID PutTree( TREE *T )
{
  if (T == NULL)
    printf("e ");
  else
  {
    printf("%d(", T->Key);
    PutTree(T->Less);
    printf(",");
    PutTree(T->More);
    printf(")");
  }
}

VOID PutTree2( TREE *T )
{
  if (T == NULL)
    printf(" e ");
  else
  {
    PutTree2(T->Less);
    printf("%d", T->Key);
    PutTree2(T->More);
  }
}

INT DeleteKey( TREE **T, INT Key )
{
  while (*T != NULL && (*T)->Key != Key)
   if ((*T)->Key < Key)
     T = &(*T)->More;
   else
     T = &(*T)->Less;

  if (*T != NULL)
  {
    TREE **P = &(*T)->Less;
    
    while (*P != NULL)
      P = &(*P)->More;


    P = &(*T)->More;

    T = &(*T)->Less;

    free(*T);
    return 1;
  }
  else
    return 0;
}

INT Linearize( TREE **T )
{
  INT n = 0;

  while (*T != NULL)
  {
    while ((*T)->Less != NULL)
    {
      TREE **P = &(*T)->Less;
    
      while ((*P)->More != NULL)
        P = &(*P)->More;

      (*P)->More = *T;
      *T = *P;

      (*T)->Less = NULL;
    }
    T = &(*T)->More;

    n++;
  }
  return n;
}

VOID BalanceTree( TREE **T, INT N )
{
}