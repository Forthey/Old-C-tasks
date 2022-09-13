/* Drekalov Nikita, 09-4, 27.11.2019 */
#include "expr.h"

QUEUE Queue1;
STACK Stack2;

INT GetPrior( CHAR Op )
{
  switch (Op)
  {
  case '(':
    return 0;
  case ')':
    return 1;
  case ',':
    return 2;
  case '=':
    return 3;
  case '+':
  case '-':
  case '@':
    return 4;
  case '*':
  case '/':
  case '%':
    return 5;
  case '^':
    return 6;
  default:
    return 3;
  }
}

VOID DropOpers( CHAR Op )
{
  while (Stack2.Top != NULL && GetPrior(Stack2.Top->T.Op) >= GetPrior(Op))
  {
    TOK T;

    Pop(&Stack2, &T);
    Put(&Queue1, T);
  }
}

VOID ParserExpr( QUEUE *QRes, QUEUE *Q )
{
  TOK T = {0, 0, 0};

  enum
  {
    STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END, STATE_FUNC
  } state = STATE_PREFIX;

  while (state != STATE_END)
  {
    if (state <= STATE_SUFFIX)
      if (!Get(Q, &T))
        if (state == STATE_SUFFIX)
          state = STATE_DONE;
        else
          Error("Unexpected end of expression\n");
    if (T.Id == TOK_FUNC)
      state = STATE_FUNC;

    switch (state)
    {
    case STATE_PREFIX:
      if (T.Id == TOK_NUM || T.Id == TOK_NAME)
        Put(&Queue1, T), state = STATE_SUFFIX;
      else if (T.Id == TOK_OP && T.Op == '(' || T.Op == '-')
        if (T.Op == '-')
        {
          T.Op = '@';
          Push(&Stack2, T);
        }
        else
          Push(&Stack2, T);
      else
      {
        Error("Wait for number or '('\n");
        ClearQueue(&Queue1);
        ClearStack(&Stack2);
      }
      break;
    case STATE_SUFFIX:
      if (T.Id == TOK_OP)
      {
        DropOpers(T.Op);
        if (T.Op == ')')
          if (Pop(&Stack2, &T))
            continue;
          else
          {
            Error("Wait for operand or ')'\n");
            ClearQueue(&Queue1);
            ClearStack(&Stack2);
          }
        else
        {
          Push(&Stack2, T);
          state = STATE_PREFIX;
        }
      }
      else
      {
        Error("Wait for operand or ')'\n");
        ClearQueue(&Queue1);
        ClearStack(&Stack2);
      }
      break;
    case STATE_FUNC:
      if (T.Id == TOK_FUNC)
        Push(&Stack2, T);
      state = STATE_PREFIX;
      break;
    case STATE_DONE:
      DropOpers(')');
      if (Stack2.Top != NULL)
        Error("Wait for operand or ')'\n");
      *QRes = Queue1;
      Queue1.Head = NULL;
      state = STATE_END;
      break;
    }
  }
  ClearQueue(&Queue1);
  ClearStack(&Stack2);
}