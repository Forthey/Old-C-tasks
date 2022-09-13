/* Drekalov Nikita, 09-4, 27.11.2019 */
#include "ugl.h"

QUEUE TokList;
TOK TokCurrent;
INT IsEOTL;
CMD *Proga;

/* Go to next token */
#define NextTok() \
  (IsEOTL ?                                                      \
     Error("Unexpected end-of-data") :                           \
     Get(&TokList, &TokCurrent) ?  (void)0 : (void)(IsEOTL = 1))
 
/* Check current token */
#define IsTokAnyOp() \
  (!IsEOTL && TokCurrent.Id == TOK_OP)
#define IsTokAnySym() \
  (!IsEOTL && TokCurrent.Id == TOK_SYMBOL)
#define IsTokAnyNum() \
  (!IsEOTL && TokCurrent.Id == TOK_NUM)
#define IsTokAnyName() \
  (!IsEOTL && TokCurrent.Id == TOK_NAME)
 
#define IsTokOp(C) \
  (IsTokAnyOp() && TokCurrent.Op == (C))
#define IsTokSym(C) \
  (IsTokAnySym() && TokCurrent.Op == (C))

#define IsTokKw(Keyword) \
  (!IsEOTL && TokCurrent.Id == TOK_KEYW && TokCurrent.KeyW == KW_ ## Keyword)

/* Parse tokens */
#define ParseAnyTok() \
  NextTok()
#define ParseAnyOp() \
  (IsTokAnyOp() ? NextTok() : Error("Expected any operator"))
#define ParseOp(C) \
  (IsTokOp(C) ? NextTok() : Error("Expected operator: %c", (C)))
#define ParseSym(C) \
  (IsTokSym(C) ? NextTok() : Error("Expected symbol: %c", (C)))
#define ParseNum(X) \
  (IsTokAnyNum() ? (*(X) = TokCurrent.Num, NextTok()) : Error("Expected number"))
#define ParseKw(Keyword) \
  (IsTokKw(Keyword) ? NextTok() : Error("Expected keywork: \"" #Keyword "\""))

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

VOID ParseExpr( LIST **Expr )
{
  TOK T = {0, 0, 0};

  enum
  {
    STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
  } state = STATE_PREFIX;

  while (state != STATE_END)
  {
    if (state == STATE_SUFFIX)
       state = STATE_DONE;

    switch (state)
    {
    case STATE_PREFIX:
      if (IsTokAnyNum() || IsTokAnyName())
        Put(&Queue1, TokCurrent), state = STATE_SUFFIX, ParseAnyTok();
      else if (IsTokOp('('))
        Push(&Stack2, TokCurrent), ParseAnyTok();
      else if (IsTokOp('{'))
        Push(&Stack2, TokCurrent), ParseAnyTok();
      else if (IsTokOp('-'))
        {
          T.Op = '@';
          Push(&Stack2, T);
        }
      else
      {
        Error("Error in STATE_PREFIX\n");
        ClearQueue(&Queue1);
        ClearStack(&Stack2);
      }
      break;
    case STATE_SUFFIX:
      if (IsTokAnyOp())
      {
        DropOpers(TokCurrent.Op);
        if (IsTokOp('}') || IsTokOp(')') || IsTokOp(';'))
          continue;
        else
        {
          Push(&Stack2, TokCurrent);
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
    case STATE_DONE:
      DropOpers(')');
      if (Stack2.Top != NULL)
        Error("Wait for operand or ')'\n");
      Queue1.Head = NULL;
      state = STATE_END;
      break;
    }
  }
  ClearQueue(&Queue1);
  ClearStack(&Stack2);
}

VOID CmdInit( CMD **C )
{
  if ((*C = malloc(sizeof(CMD))) == NULL)
    Error("No memory");

  (*C)->Id = CMD_EXPR;
  (*C)->Expr = NULL;
  
  (*C)->C1 = (*C)->C2 = (*C)->Next = NULL;
}

VOID CmdClear( CMD *C )
{
  if (C == NULL)
    return;

  while (C->Expr != NULL)
  {
    free(C->Expr);
    C->Expr = C->Expr->Next;
  }

  CmdClear(C->C1);
  CmdClear(C->C2);
  
  free(C);
}

VOID ParseCmd( CMD **C )
{
  *C = NULL;

  if (IsTokKw(IF))
  {
    CmdInit(C);
    (*C)->Id = CMD_IF;
    ParseKw(IF);
    ParseOp('(');
    ParseExpr(&(*C)->Expr);
    ParseOp(')');
    ParseCmd(&(*C)->C1);
    if (IsTokKw(ELSE))
    {
      ParseKw(ELSE);
      ParseCmd(&(*C)->C2);
    }
  }
  else if (IsTokKw(WHILE))
  {
    CmdInit(C);
    (*C)->Id = CMD_WHILE;
    ParseKw(IF);
    ParseOp('(');
    ParseExpr(&(*C)->Expr);
    ParseOp(')');
    ParseCmd(&(*C)->C1);
  }
  else if (IsTokSym('{'))
  {
    ParseSym('{');
    while (!IsTokSym('}'))
    {
      CmdInit(C);
      ParseCmd(C);
      C = &(*C)->Next;
    }
    ParseSym('}');
  }
  else
  {
    CmdInit(C);
    (*C)->Id = CMD_EXPR;
    ParseExpr(&(*C)->Expr);
    ParseSym(';');
  }
}

VOID ParseProgram( VOID )
{
  CMD **cmd = &Proga;

  Proga = NULL;
  IsEOTL = 0;
  NextTok();
  while (!IsEOTL)
  {
    ParseCmd(cmd);
    cmd = &(*cmd)->Next;
  }
}