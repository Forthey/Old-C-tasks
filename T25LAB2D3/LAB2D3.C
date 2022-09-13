/* Drekalov Nikita, 09-4, 02.11.2019 */
#include <stdio.h>
#include "lab2d3.h"

#define FONT_MAX_SIZE 16384

BYTE Lab[MAX][MAX], Font[FONT_MAX_SIZE];
XYTYPE Ava, SpawnPnt, Exit;
ENEMY Enemy[MAX_ENEMIES];
INT FontW, FontH, FontBPL, LatenTime = 3.5, NumOfEnemies;

VOID LoadLab( CHAR *FileName )
{
  INT x = 0, y = 0, i = 0, cnt = 0;
  FILE *F;
 
  if ((F = fopen(FileName, "r")) == NULL)
    return;

  while (cnt++ < MAX * MAX)
  {
    switch (fgetc(F))
    {
    case ' ':
      if (y < MAX && x < MAX)
        Lab[y][x] = 0;
      x++;
      break;
    case '*':
      if (y < MAX && x < MAX)
        Lab[y][x] = 1;
      x++;
      break;
    case 'a':
      if (y < MAX && x < MAX)
        Lab[y][x] = 0;
      x++;
      Ava.X = x;
      Ava.Y = y;
      SpawnPnt.X = x;
      SpawnPnt.Y = y;
      break;
    case '\n':
      y++;
      x = 0;
      break;
    case 'e':
      if (y < MAX && x < MAX)
        Lab[y][x] = 0;
      if (NumOfEnemies < MAX_ENEMIES)
      {
      Enemy[i].X = x;
      Enemy[i].Y = y;
      Enemy[i].DeltaTime = 0;
      NumOfEnemies++;
      i++;
      }
      x++;
      break;
    case 'z':
      if (y < MAX && x < MAX)
        Lab[y][x] = 0;
      x++;
      Exit.X = x;
      Exit.Y = y;
      break;
    }
  }
  fclose(F);
}

VOID DrawLab( VOID )
{
  INT x, y, i, flag = 0;

  for (y = 0; y < MAX; y++)
    for (x = 0; x < MAX; x++)
    {
      if (Lab[y][x] == 1)
        PutPixel(x, y, FRM_RGB(255, 255, 255)), flag = 1;
      else if (x == Ava.X && y == Ava.Y)
        PutPixel(x, y, FRM_RGB(0, 255, 0)), flag = 1;
      else 
        for (i = 0; i < MAX_ENEMIES; i++)
          if (x == Enemy[i].X && y == Enemy[i].Y)
          {
            PutPixel(x, y, FRM_RGB(255, 0, 0)), flag = 1; 
            break;
          }
      if (x == Exit.X && y == Exit.Y)
        PutPixel(x, y, FRM_RGB(255, 255, 0)), flag = 1;
      if (!flag)
        PutPixel(x, y, FRM_RGB(0, 0, 0));
      flag = 0;
    }
}

VOID DeathCheck( VOID )
{
  INT i;

  for (i = 0; i < MAX_ENEMIES; i++)
    if (Ava.X == Enemy[i].X && Ava.Y == Enemy[i].Y)
        Ava.X = SpawnPnt.X, Ava.Y = SpawnPnt.Y;
}