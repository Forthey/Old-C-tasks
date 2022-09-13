/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <stdio.h>
#include <setjmp.h>
#include <stdarg.h>

#include <conio.h>

#include "ugl.h"

#define MAX 100

jmp_buf ExprJumpBuf;

VOID Error( CHAR *Str, ... ) 
{
  va_list ap;       
 
  printf("ERROR: ");
  va_start(ap, Str);
  vprintf(Str, ap);
  va_end(ap);
 
  printf("\n");
  longjmp(ExprJumpBuf, 1);
}

VOID GetStr( CHAR *Name, INT MaxLen )
{
  INT i = 0;
  CHAR ch;

  while ((ch = getchar()) != '\n')
    if (Name != NULL && i < MaxLen - 1)
      Name[i++] = ch;
  if (Name != NULL && i < MaxLen)
    Name[i] = 0;
}

VOID main( VOID )
{
  FILE *F;
  CHAR FileName[MAX];
  QUEUE QRes = {NULL, NULL};

  SetDbgMemHooks();

  if (setjmp(ExprJumpBuf))
  {
    ClearStack(&StackEval);
    ClearQueue(&TokList);
    ClearQueue(&QRes);
    ClearVarTable();
  }
  
  printf("Input file name: ");
  GetStr(FileName, MAX);

  if ((F = fopen(FileName, "r")) != NULL)
  {
    static CHAR Buf[10000];

    while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      Scanner(Buf);

    fclose(F);
  }

  ParseProgram();
  DoCmd(Proga);
  DisplayVarTable();
}