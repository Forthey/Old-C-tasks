/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <stdio.h>

#include "ugl.h"

VOID UpdateKeyword( TOK *T )
{
  INT i;
  struct
  {
    CHAR *Name;
    KEYWORD KeyW;
  } Kws[] = 
  {
    {"if", KW_IF},
    {"else", KW_ELSE},
    {"while", KW_WHILE}
  };

  for (i = 0; i < sizeof(Kws) / sizeof(Kws[0]); i++)
    if (strcmp(Kws[i].Name, T->Name) == 0)
    {
      T->Id = TOK_KEYW;
      T->KeyW = Kws[i].KeyW;
      return;
    }
}

VOID Scanner( CHAR *S )
{
  TOK T = {0, 0, 0};
  INT i = 0;
  CHAR Name[MAX_NAME];

  while (*S != 0)
  {
    switch (*S)
    {
    case ' ':
    case '\n':
      S++;
      continue;      
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':
    case '(':
    case ')':
    case '{':
    case '}':
    case '=':
    case ',':
    case '>':
    case '<':
    case '!':
    case ';':
      T.Id = TOK_OP;
      T.Op = *S++;
      if (*S == '=' && (T.Op == '<' || T.Op == '>' || T.Op == '!' || T.Op == '='))
        T.Op += TOK_OP_ADD_EQ, S++;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
      T.Id = TOK_NUM;
      T.Num = 0;
  
      while (*S >= '0' && *S <= '9')
        T.Num = T.Num * 10 + *S++ - '0';
      if (*S == '.')
      {
        DBL denum = 1;

        S++;
        while (*S >= '0' && *S <= '9')
          T.Num += (*S++ - '0') / (denum *= 10);
      }
      break;
    default:
      if (isalpha((UCHAR)*S))
      {
        do
        {
          if (i < MAX_NAME - 1)
            Name[i++] = *S;
          S++;
        } while (isalpha((UCHAR)*S) || isdigit((UCHAR)*S));

        Name[i] = 0;

        T.Id = TOK_NAME;
        strcpy(T.Name, Name);

        UpdateKeyword(&T);
        break;
      }
      Error("Unrecognized character '%c'\n", *S);
    }

    Put(&TokList, T);
    T.Id = -1;
    T.Num = 0;
    T.Op = 0;
    i = 0;
    while (T.Name[i] != 0)
      T.Name[i] = 0, i++;
  }
}