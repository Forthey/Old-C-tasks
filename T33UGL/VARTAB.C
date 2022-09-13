/* Drekalov Nikita, 09-4, 04.12.2019 */
#include <stdio.h>

#include "ugl.h"


VOID SetValue( CHAR *Name, DBL Value )
{
  VARLIST **ptr = &VarTable;

  while (*ptr != NULL)
    if (strcmp((*ptr)->Name, Name) == 0)
    {
      (*ptr)->Value = Value;
      return;
    }
    else
      ptr = &(*ptr)->Next;

  if ((*ptr = malloc(sizeof(VARLIST))) == NULL)
    Error("Not enough room for new variable");
  strncpy((*ptr)->Name, Name, MAX_NAME - 1);
  (*ptr)->Value = Value;
  (*ptr)->Next = NULL;
}

DBL GetValue( CHAR *Name )
{
  VARLIST **ptr = &VarTable;
  INT i = 0;

  while (*ptr != NULL)
    if (strcmp((*ptr)->Name, Name) == 0)
      return (*ptr)->Value;
    else
      ptr = &(*ptr)->Next;

  Error("Variable not found: ");
  
  while (Name[i] != 0)
    printf("%c", Name[i++]);
  return 0;
}

VOID DisplayVarTable( VOID )
{
  VARLIST **ptr = &VarTable;
  INT i;

  if (*ptr == NULL)
    return;

  printf("\n----Variable table----\n\n");
  while (*ptr != NULL)
  {
    i = 0;
    while ((*ptr)->Name[i] != 0)
      printf("%c", (*ptr)->Name[i++]);
    printf(" = ");
    printf("%f", (*ptr)->Value);
    printf("\n");
    ptr = &(*ptr)->Next;
  }
}

VOID ClearVarTable( VOID )
{
  VARLIST *ptr = VarTable;

  while (ptr != NULL)
  {
    free(ptr);
    ptr = ptr->Next;
  }
}