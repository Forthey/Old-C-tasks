/* Drekalov Nikita, 09-4, 30.10.2019 */
#include <stdlib.h>

#include "life.h"

#define ZOOM 2
#define H (1080 / ZOOM)
#define W (1920 / ZOOM)

byte *F1, *F2, *Old;

void SetCell( int x, int y, int value )
{
  x = (x + W) % W;
  y = (y + H) % H;

  F2[y * W + x] = value;
}

int GetCell( int x, int y )
{
  x = (x + W) % W;
  y = (y + H) % H;

  if (F1[y * W + x] >= 1)
    return 1;
  return 0;
}

void DrawField( void )
{
  int x, y;

  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
      if (GetCell(x, y))
        PutPix(x, y, Old[y * W + x], 255, 0);
      else
        PutPix(x, y, 0, 0, 0);

}

void SetCell1( int x, int y, int value )
{
  x = (x + W) % W;
  y = (y + H) % H;

  F1[y * W + x] = value;
}

/* Random global fill */
void FillRand( void )
{
  int x, y, max = 0;

  while (max < 200000 / ZOOM)
    for (y = 1; y < H; y = y + rand() % H)
      for (x = 1; x < W; x = x + rand() % W)
        SetCell1(x, y, 1), max++;
 
}

/* Array allocation */
void LifeInit( void )
{
  F1 = malloc(W * H);
  F2 = malloc(W * H);
  Old = malloc(W * H);
}

/* Copy field F2 to F1 */
void CopyToFrom( void )
{
  int i;

  for (i = 0; i < W * H; i++)
    F1[i] = F2[i];

}

/* Get amount of neighbours */
int GetNeighbours( int x, int y )
{
  return 
    GetCell(x - 1, y - 1) + 
    GetCell(x, y - 1) +
    GetCell(x + 1, y - 1) +
    GetCell(x + 1, y) +
    GetCell(x + 1, y + 1) +
    GetCell(x, y + 1) +
    GetCell(x - 1, y + 1) +
    GetCell(x - 1, y);
}

/* Create a new field */
void NewGeneration( void )
{
  int x, y, n, value;

  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
    {
      n = GetNeighbours(x, y);

      if (GetCell(x, y))
        if (n < 2 || n > 3)
          value = 0, Old[y * W + x] = 0;
        else
        {
          value = 1; 
          if (Old[y * W + x] < 200)  
            Old[y * W + x]++;
        }
      else if (n == 3)
        value = 1, Old[y * W + x] = 0;
      else 
        value = 0, Old[y * W + x] = 0;

      SetCell(x, y, value + Old[y * W + x]);
    }
}

/* Field common step */
void LifeStep( void )
{
  NewGeneration();
  CopyToFrom();
  DrawField();
}

/* Random fill */
void RandInjection( void )
{
  int x, y, max = 0;

  while (max < 5000 / ZOOM)
    for (y = 1; y < H; y = y + rand() % H)
      for (x = 1; x < W; x = x + rand() % W)
        F1[y * W + rand() % x] = 1, max++;
  DrawField();
}

/* Create 4 sticks */
void SticksInjection( int x, int y )
{ 
  F1[y * W + x] = 1;
  F1[(y + 1) * W + x - 1] = 1;
  F1[(y + 1) * W + x] = 1;
  F1[(y + 2) * W + x] = 1;
  F1[(y + 1) * W + x + 1] = 1;
  F1[y * W + x + 1] = 1;
  F1[y * W + x + 2] = 1;
  F1[(y - 1) * W + x + 1] = 1;
  F1[(y - 1) * W + x] = 1;
  F1[(y - 2) * W + x] = 1;
  F1[(y - 1) * W + x - 1] = 1;
  F1[y * W + x - 1] = 1;
  F1[y * W + x - 2] = 1;

  DrawField();
}

/* Clear field */
void FieldClear( void )
{
  int i;

  for (i = 0; i < W * H; i++)
    F1[i] = 0;
}

/* Create random directed runner */
void RunnersInjection( int x, int y )
{
  switch (1 + rand() % 4)
  {
    case 1:
      {
        F1[(y + 1) * W + x - 1] = 1;
        F1[(y + 1) * W + x] = 1;
        F1[(y + 1) * W + x + 1] = 1;
        F1[y * W + x + 1] = 1;
        F1[(y - 1) * W + x] = 1;
        break;
      }
    case 2:
      {
        F1[(y - 1) * W + x] = 1;
        F1[y * W + x - 1] = 1;
        F1[(y + 1) * W + x - 1] = 1;
        F1[(y + 1) * W + x] = 1;
        F1[(y + 1) * W + x + 1] = 1;
        break;
      }
    case 3:
      {
        F1[(y + 1) * W + x - 1] = 1;
        F1[y * W + x - 1] = 1;
        F1[(y - 1) * W + x - 1] = 1;
        F1[(y - 1) * W + x] = 1;
        F1[y * W + x + 1] = 1;
        break;
      }
    case 4:
      {
        F1[(y + 1) * W + x] = 1;
        F1[y * W + x + 1] = 1;
        F1[(y - 1) * W + x + 1] = 1;
        F1[(y - 1) * W + x] = 1;
        F1[(y - 1) * W + x - 1] = 1;
        break;
      }
  }
}

/* Create static figue (barrel) */
void BarrelInjection( int x, int y )
{
  F1[y * W + x] = 1;
  F1[y * W + x + 1] = 1;
  F1[(y + 1) * W + x + 1] = 1;
  F1[(y + 1) * W + x] = 1;

}

/* Create animation. Last - 12 sticks */
void BurstInjection( int x, int y )
{
  int k, j;

  if (W - x <= 4 || x <= 4 || H - y <= 4 || y <= 4)
    return;

  for (j = y - 4; j <= y + 4; j++)
    for (k = x - 4; k <= x + 4; k++)
      F1[j * W + k] = 1;

  for (j = y - 6; j < y - 4; j++)
    for (k = x - 6; k < x - 4; k++)
      F1[j * W + k] = 1;

  for (j = y - 6; j < y - 4; j++)
    for (k = x + 5; k <= x + 6; k++)
      F1[j * W + k] = 1;

  for (j = y + 5; j <= y + 6; j++)
    for (k = x - 6; k < x - 4; k++)
      F1[j * W + k] = 1;

  for (j = y + 5; j <= y + 6; j++)
    for (k = x + 5; k <= x + 6; k++)
      F1[j * W + k] = 1;
}  

