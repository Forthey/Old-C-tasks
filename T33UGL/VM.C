/* Drekalov Nikita, 09-4, 27.11.2019 */
#include <math.h>

#include "ugl.h"

STACK StackEval = {NULL};

DBL Eval( LIST *Expr )
{
  TOK T, 
    B = {0, 0, 0}, 
    A = {0, 0, 0};

  while (Expr != NULL)
  {
    T = Expr->T;
    Expr = Expr->Next;

    if (T.Id == TOK_NUM || T.Id == TOK_NAME)
      Push(&StackEval, T);
    
    if (T.Op != '@')
    {
      Pop(&StackEval, &B);
      if (B.Id == TOK_NAME)
        B.Num = GetValue(B.Name);
    }
    
    Pop(&StackEval, &A);
    if (A.Id == TOK_NAME && T.Op != '=')
      A.Num = GetValue(A.Name), A.Id = TOK_NUM;
    switch (T.Op)
    {
      case '+':
        A.Num += B.Num;
        break;
      case '-':
        A.Num -= B.Num;
        break;
      case '*':
        A.Num *= B.Num;
        break;
      case '/':
        A.Num /= B.Num;
        break;
      case '%':
        fmod(A.Num, B.Num);
        break;
      case '^':
        A.Num = pow(A.Num, B.Num);
        break;
      case '@':
        A.Num = -A.Num;
        break;
      case '=':
        if (A.Id != TOK_NAME)
          Error("Lvalue required");
        SetValue(A.Name, B.Num);
        break;
      case ',':
        A.Id = TOK_NUM;
        A.Num = B.Num;
        break;
    }
      Push(&StackEval, A);
  }

  Pop(&StackEval, &T);

  return T.Num;
}

VOID DoCmd( CMD *C )
{
  while (C != NULL)
  {
    /* Interpretate current command */
    if (C->Id == CMD_EXPR)
      Eval(C->Expr);
    else if (C->Id == CMD_IF)
      if (Eval(C->Expr))
        DoCmd(C->C1);
      else
        DoCmd(C->C2);
    else if (C->Id == CMD_WHILE)
      while (Eval(C->Expr))
        DoCmd(C->C1);
 
    /* Go to next command */
    C = C->Next;
  }
}