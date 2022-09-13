/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <stdio.h>
#include <setjmp.h>
#include <stdarg.h>

#include <conio.h>

#include "expr.h"

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
  CHAR Str[MAX];
  QUEUE Q = {NULL, NULL},
    QRes = {NULL, NULL};
  BOOL key = 1;

  SetDbgMemHooks();

  InitFuncs();

  if (setjmp(ExprJumpBuf))
  {
    ClearStack(&StackEval);
    ClearQueue(&Q);
    ClearQueue(&QRes);
    ClearVarTable();
  }

  printf("Esc - exit    F - show aviable functions\n");
  while (key)
  {
    switch (_getch())
    {
    case 27:
      key = 0;
      break;
    case 'f':
    case 'F':
      DisplayFunc();
      break;
    default:
      printf("Input an expression: ");
      GetStr(Str, MAX);

      Scanner(&Q, Str);
      ParserExpr(&QRes, &Q);
      printf("Result is %g\n", Eval(&QRes));
      DisplayVarTable();
      break;
    }
  }
}