/* Drekalov Nikita, 09-4, 15.11.2019 */
#include <stdio.h>
#include <string.h>

#include "list2.h"

VOID GetStr( CHAR *Name, INT MaxLen )
{
  INT i = 0;
  CHAR ch;

  while ((ch = getchar()) != '\n' && ch != ' ')
    if (Name != NULL && i < MaxLen - 1)
      Name[i++] = ch;
  if (Name != NULL && i < MaxLen)
    Name[i] = 0;
}

VOID DisplayList( LIST *L )
{
  if (L == NULL)
    printf("\n");
  else
  {
    LIST *save = L;
 
    while (L->Prev != NULL)
      L = L->Prev;

    while (L != NULL)
    {
      printf("%s%s", L->Str, L == save ? "(*)" : "");
      printf((L = L->Next) == NULL ? "\n" : ",");
    }
  }
}

INT ListAddToFront( LIST **L, CHAR *NewStr )
{
  LIST *Next = NULL;

  while (*L != NULL)
  {
    Next = *L; 
    L = &(*L)->Prev; 
  }
 
  if ((*L = malloc(sizeof(LIST))) == NULL)
    return 0;
 
  (*L)->Prev = NULL;
  (*L)->Next = Next;
  strcpy((*L)->Str, NewStr); 
  return 1;

}
     
INT ListDelFromFront( LIST **L, CHAR *OldStr )
{
  LIST *Old = NULL;

  if (*L == NULL)
    return 0;

  while ((*L)->Prev != NULL)
  {
    Old = *L; 
    L = &(*L)->Prev; 
  }

  Old = *L;
  strcpy(OldStr, (*L)->Str);
  *L = (*L)->Next;

  free(Old);
  return 1;
}

INT ListAddToEnd( LIST **L, CHAR *NewStr )
{
  
  LIST *Prev = NULL;

  while (*L != NULL)
  {
    Prev = *L; 
    L = &(*L)->Next; 
  }
 
  if ((*L = malloc(sizeof(LIST))) == NULL)
    return 0;
 
  (*L)->Prev = Prev;
  (*L)->Next = NULL;
  strcpy((*L)->Str, NewStr); 

  return 1;
}

INT ListDelFromEnd( LIST **L, CHAR *OldStr )
{
  LIST *Old = NULL;

  if (*L == NULL)
    return 0;

  while ((*L)->Next != NULL)
  {
    Old = *L; 
    L = &(*L)->Next; 
  }

  Old = *L;
  strcpy(OldStr, (*L)->Str);
  *L = (*L)->Prev;
  (*L)->Next = NULL;

  free(Old);
  return 1;
}
