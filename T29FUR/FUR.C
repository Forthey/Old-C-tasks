/* Drekalov Nikita, 09-4, 18.11.2019 */
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "fur.h"

TREE * Init( CHAR *Text, TREE *N, TREE *Y)
{
  TREE *T = malloc(sizeof(TREE));

  if (T == NULL)
    return NULL;

  strncpy(T->Text, Text, MAX_STR - 1);

  T->No = N;
  T->Yes = Y;

  return T;
}

VOID SaveTreeRec( FILE *F, TREE *T )
{
  if (T == NULL)
    return;

  fwrite(T, sizeof(TREE), 1, F);

  SaveTreeRec(F, T->No);
  SaveTreeRec(F, T->Yes);
}

INT SaveTree( CHAR *FileName, TREE *T )
{
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
    return 0;

  SaveTreeRec(F, T);

  fclose(F);
  return 1;
}

VOID LoadTreeRec( FILE *F, TREE **T )
{
  TREE tr;

  if (fread(&tr, sizeof(TREE), 1, F) != 1)
    return;

  *T = Init(tr.Text, NULL, NULL);

  if (tr.No != NULL)
    LoadTreeRec(F, &(*T)->No);
  if (tr.Yes != NULL)
    LoadTreeRec(F, &(*T)->Yes);
}

INT LoadTree( CHAR *FileName, TREE **T )
{
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;

  LoadTreeRec(F, T);

  fclose(F);
  return 1;
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

VOID Session( TREE **T )
{
  CHAR key;

  if (*T == NULL)
    return;

  printf("%s?", (*T)->Text);

  key = _getch();
  printf(key == 'Y' || key == 'y' ? " Да\n" : " Нет\n");
  if ((*T)->Yes != NULL)
    key == 'Y' || key == 'y' ? (T = &(*T)->Yes) : (T = &(*T)->No), Session(T);
  else
  {
    CHAR Ans[MAX_STR], Qst[MAX_STR];

    if (key == 'y' || key == 'Y')    
      return;

    printf("Новое определение: ");
    GetStr(Qst, MAX_STR);
    printf("Введите правильный ответ для определения: ");
    GetStr(Ans, MAX_STR);

    *T = Init(Qst, *T, Init(Ans, NULL, NULL));

    return;
  }
}

VOID DrawTree( TREE *T )
{
  static INT Level;
  INT i;

  Level++;
  if (T != NULL)
  {
    DrawTree(T->No);

    printf("%*c", Level * 10, ' ');
    for (i = 0; i < MAX_STR && T[i].Text != 0; i++)
      printf("%c", T->Text[i] == 0xCD ? ' ' : T->Text[i]);
    printf("\n");
    DrawTree(T->Yes);
  }
  Level--;
  printf("\n");
}
