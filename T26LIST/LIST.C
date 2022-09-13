/* Drekalov Nikita, 09-4, 11.11.2019 */
#include <stdio.h>

#include "list.h"

VOID Display( LIST *L )
{
  if (L == NULL)
    printf("<Empty list>\n");
  else
    while (L != NULL)
      printf("%d", L->Data), printf((L = L->Next) == NULL ? "\n" : ",");
}

INT ListAddToFront( LIST **L, INT NewData )
{
  LIST *NewElement = malloc(sizeof(LIST));

  if (NewElement == NULL)
    return 0;

  NewElement->Data = NewData;
  NewElement->Next = *L;
  *L = NewElement;
  return 1;
}

INT ListDelFromFront( LIST **L )
{
  LIST *Old;

  if (*L == NULL)
    return 0;

  Old = *L;
  *L = Old->Next;

  free(Old);
  return 1;
}

INT ListAddToBack( LIST **L, INT NewData )
{
  while (*L != NULL)
    L = &(*L)->Next;

  *L = malloc(sizeof(LIST));

  if (*L == NULL)
    return 0;

  (*L)->Data = NewData;
  (*L)->Next = NULL;

  return 1;
}

INT ListDelFromBack( LIST **L )
{
  if (*L == NULL)
    return 0;

  while ((*L)->Next != NULL)
    L = &(*L)->Next;

  free(*L);
  *L = NULL;
  return 1;
}

INT ListAddToArb( LIST **L, INT NewData, INT Pos )
{
  LIST *OldData = *L, *Tmp = *L;
  INT i = 0;

  while (*L != NULL && i <= Pos)
  {
    L = &(*L)->Next;
    i++;
  }

  if (i < Pos)
    return 0;

  OldData->Data = (*L)->Data;

  (*L)->Data = NewData;

  while (*L != NULL)
  {
    L = &(*L)->Next;
    Tmp->Data = OldData->Data;
    OldData->Data = (*L)->Data;
    (*L)->Data = Tmp->Data;
  }

  *L = malloc(sizeof(LIST));

  (*L)->Data = OldData->Data;
  (*L)->Next = NULL;

  return 1;
  
}