/* Drekalov Nikita, 09-4, 06.11.2019 */
#include <math.h>
#include "lab2d3.h"

INT S[MAX][MAX];


VOID LoadSRec( INT x, INT y )
{
  if (Lab[y][x] == 1 || y >= MAX || x >= MAX || y <= 0 || x <= 0)
    return;

  if (S[y + 1][x] > S[y][x])
    S[y + 1][x] = S[y][x] + 1, LoadSRec(x, y + 1);

  if (S[y - 1][x] > S[y][x])
    S[y - 1][x] = S[y][x] + 1, LoadSRec(x, y - 1);

  if (S[y][x - 1] > S[y][x])
    S[y][x - 1] = S[y][x] + 1, LoadSRec(x - 1, y);

  if (S[y][x + 1] > S[y][x])
    S[y][x + 1] = S[y][x] + 1, LoadSRec(x + 1, y);
}


VOID LoadS( VOID )
{
  INT y, x;

  for (y = 0; y < MAX; y++)
    for (x = 0; x < MAX; x++)
      S[y][x] = INFINITY;

  S[Ava.Y][Ava.X] = 0;

  LoadSRec(Ava.X, Ava.Y);
}

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
  *A = *B;
  *B = tmp;
}


VOID CheckPoint( INT X, INT Y, INT i )
{
  INT j, nX = X, nY = Y, A[4], k, m;

  A[0] = S[Y + 1][X];
  A[1] = S[Y - 1][X];
  A[2] = S[Y][X + 1];
  A[3] = S[Y][X - 1];

  for (k = 0; k < 3; k++)
    for (m = 0; m < 3 - k; m++)
      if (A[m] > A[m + 1])
        Swap(&A[m], &A[m + 1]);

  if (A[0] == S[Y + 1][X])
    nX = X, nY = Y + 1;

  if (A[0] == S[Y - 1][X])
    nX = X, nY = Y - 1;

  if (A[0] == S[Y][X - 1])
    nX = X - 1, nY = Y;

  if (A[0] == S[Y][X + 1])
    nX = X + 1, nY = Y;

  for (j = 0; j < NumOfEnemies; j++)
    if (Enemy[j].X == nX && Enemy[j].Y == nY && i != j)
      return;
  Enemy[i].X = nX;
  Enemy[i].Y = nY;
}

VOID EnemyMove( VOID )
{
  INT i;

  for (i = 0; i < NumOfEnemies; i++)
    CheckPoint(Enemy[i].X, Enemy[i].Y, i);
    
}