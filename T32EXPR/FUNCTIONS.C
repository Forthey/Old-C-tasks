/* Drekalov Nikita, 09-4, 06.12.2019 */
#include <stdio.h>

#include "expr.h"
  
/* Creating new function */
static VOID FuncCreate( CHAR *Name )
{
  FUNCLIST **F = &FuncList;
  INT i = 0;

  while (*F != NULL)
    if (strcmp((*F)->Name, Name) == 0)
    {
      printf("Function was added before: ");
      while ((*F)->Name != 0)
        printf("%c", (*F)->Name[i++]);
      printf("\n");
      return;
    }
    else
      F = &(*F)->Next;

  if ((*F = malloc(sizeof(FUNCLIST))) == NULL)
    Error("Not enough place for new func\n");

  strcpy((*F)->Name, Name);
  (*F)->Next = NULL;
} /* End of 'FuncCreate' function */

VOID InitFuncs( VOID )
{
  FuncCreate("sqrt");
  FuncCreate("pow2");
  FuncCreate("mod");
  FuncCreate("sin");
  FuncCreate("cos");
}

VOID DisplayFunc( VOID )
{
  FUNCLIST **F = &FuncList;
  INT i;

  if (*F == NULL)
    return;

  while (*F != NULL)
  {
    i = 0;
    while ((*F)->Name[i] != 0)
      printf("%c", (*F)->Name[i++]);
    printf("\n");
    F = &(*F)->Next;
  }
}

INT FindFunc( CHAR *Name )
{
  FUNCLIST **F = &FuncList;
  INT i = 1;

  while (*F != NULL)
    if (strcmp((*F)->Name, Name) == 0)
      return i;
    else
      F = &(*F)->Next, i++;

  return 0;
}