/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <stdio.h>

#include "expr.h"

VOID Scanner( QUEUE *Q, CHAR *S )
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
    case '=':
    case ',':
      T.Id = TOK_OP;
      T.Op = *S++;
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

        if (FindFunc(Name) != 0)
          T.Id = TOK_FUNC;
        else
          T.Id = TOK_NAME;

        strcpy(T.Name, Name);
        break;
      }
      Error("Unrecognized character '%c'\n", *S);
    }

    Put(Q, T);
    T.Id = -1;
    T.Num = 0;
    T.Op = 0;
    i = 0;
    while (T.Name[i] != 0)
      T.Name[i] = 0, i++;
  }
}