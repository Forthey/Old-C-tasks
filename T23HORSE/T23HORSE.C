/* Drekalov Nikita, 09-4, 02.11.2019 */
#include <stdio.h>
#include <conio.h>
#include <commondf.h>

#define N 5
#define M 5

INT Bd[N][M];

VOID Display( VOID )
{
  int i, j;

   for (i = 0; i < N; i++)
  {
    for (j = 0; j < M; j++)
      printf("%3d", Bd[i][j]);
    printf("\n");
  }
}

INT Go( INT X, INT Y, INT Pos)
{
  INT newx, newy, i;
  static INT Dx[8] = {1, 2, 2, 1, -1, -2, -2, -1}, 
    Dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

  if (Pos == N * M + 1)
  {
    Display();
    return 1;
  }
  
  else
    for (i = 0; i < 8; i++)
    {
      newx = X + Dx[i];
      newy = Y + Dy[i];

      if (newx > 0 && newx < M &&
        newy > 0 && newy < N && Bd[newy][newx] == 0)
      {
        Bd[newy][newx] = Pos;
        if (Go(newx, newy, Pos + 1))
          return 1;
        Bd[newy][newx] = 0;
      }
    }
  return 0;
} /* End of 'Go' function */

/* The main function */
VOID main( VOID )
{
  INT x, y, Pos;

  printf("X: ");
  scanf("%d", &x);
  printf("Y: ");
  scanf("%d", &y);
  printf("Pos: ");
  scanf("%i", &Pos);

  Bd[y][x] = 1;

  Go(x, y, 2);

  _getch();
} /* End of 'main' function */