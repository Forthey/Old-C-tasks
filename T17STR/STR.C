/* Drekalov Nikita, 09-4, 29.10.2019 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "str.h"

char * Load( char *FileName )
{
  FILE *F;
  int i, c;
  char *str;

  F = fopen(FileName, "r");
  if (F == NULL)
    return NULL;

  for (i = 0; (c = fgetc(F)) != EOF; i++)
    ;
  rewind(F);

  str = malloc(sizeof(char) * i);

  for (i = 0; (c = fgetc(F)) != EOF; i++)
    str[i] = c;
  str[i] = 0;

  fclose(F);

  return str;
}

int LineNum( char *txt, int N )
{
  int i, cnt = 0;

  for (i = 0; i < N; i++)
    if (txt[i] == '\n')
      cnt++;
  return cnt;
}

int LatinChNum( char *txt, int N )
{
  int i, LatinN = 0;

  for (i = 0; i < N; i++)
    if ((txt[i] >= 'A' && txt[i] <= 'Z') || (txt[i] >= 'a' && txt[i] <= 'z'))
      LatinN++;
  return LatinN;
}

int CyrillicChNum( char *txt, int N)
{
  int i, j, CyrillicN = 0;
  char Letters[] = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÐÏÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ";

  for (i = 0; i < N; i++)
   for (j = 0; j < 66; j++)
     if (txt[i] == Letters[j]) 
       CyrillicN++;
  return CyrillicN;
}

int IsPalin( char *txt, int N )
{
  int i = 0;
  N--;
  while (i < N)
  {
    while (isspace((unsigned char)txt[i]))
      i++;
    while (isspace((unsigned char)txt[N]))
      N--;

    if (txt[i++] != txt[N--])
      return 0;
    return 1;
  }
  return 1;
}

int CountWord( char *txt, int (*F)( char *txt, int Start, int End ))
{
  int i = 0, cnt = 0, b, e;

  while (txt[i] != 0)
  {
    while (isspace((unsigned char)txt[i]))
      i++;
    if (txt[i] != 0)
    {
      b = i;
      while (!isspace((unsigned char)txt[i]) && txt[i] != 0)
        i++;
      e = i - 1;
    }
    cnt += F(txt, b, e);
  }

  return cnt;
}

int WordNum( char *txt, int Start, int End )
{
  return 1;
}

int SymmWordsNum( char *txt, int Start, int End )
{
  while (Start < End)
    if (txt[Start++] != txt[End--])
      return 0;
  return 1;
}

int NumSum( char *txt, int Start, int End )
{
  int sum = 0, i;

  for (i = Start; i <= End; i++)
    if (txt[i] >= '0' && txt[i] <= '9')
      sum = sum * 10 + txt[i] - '0';
  return sum;
}

double RealNumSum( char *txt, int Start, int End )
{
  int sumint = 0, i, point = End + 1;
  double sumreal = 0;

  for (i = End; i >= Start; i--)
    if (txt[i] == '.')
      point = i;
  for (i = Start; i < point; i++)
    if (txt[i] >= '0' && txt[i] <= '9')
      sumint = sumint * 10 + txt[i] - '0';
  for (i = End; i > point; i--)
    if (txt[i] >= '0' && txt[i] <= '9')
      sumreal = sumreal / 10 + (double)(txt[i] - '0') / 10;

  return sumint + sumreal;
}

double CountWordR( char *txt, double (*F)( char *txt, int Start, int End ))
{               
  int i = 0, b, e;
  double cnt = 0;

  while (txt[i] != 0)
  {
    while (isspace((unsigned char)txt[i]))
      i++;
    if (txt[i] != 0)
    {
      b = i;
      while (!isspace((unsigned char)txt[i]) && txt[i] != 0)
        i++;
      e = i - 1;
    }
    cnt += F(txt, b, e);
  }
  return cnt;
}