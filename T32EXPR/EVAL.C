/* Drekalov Nikita, 09-4, 27.11.2019 */
#include <math.h>

#include "expr.h"

STACK StackEval = {NULL};

DBL Eval( QUEUE *Q )
{
  TOK T, 
    B = {0, 0, 0}, 
    A = {0, 0, 0};

  while (Get(Q, &T))
  {
    if (T.Id == TOK_NUM || T.Id == TOK_NAME)
      Push(&StackEval, T);
    else
    {
      if (T.Id == TOK_FUNC)
      {
        Pop(&StackEval, &B);
        if (B.Id == TOK_NAME)
          B.Num = GetValue(B.Name), B.Id = TOK_NUM;
        switch (FindFunc(T.Name))
        {
          case 0:
            Error("Error in program\n");
            break;
          case 1:
            B.Num = sqrt(B.Num);
            break;
          case 2:
            B.Num = pow(B.Num, 2);
            break;
          case 3:
            B.Num = abs(B.Num);
            break;
          case 4:
            B.Num = sin(B.Num);
            break;
          case 5:
            B.Num = cos(B.Num);
            break;
        }
        Push(&StackEval, B);
        continue;
      }
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
  }

  Pop(&StackEval, &T);

  return T.Num;
}