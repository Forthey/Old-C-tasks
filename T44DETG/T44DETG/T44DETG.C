/* FILE NAME: T44DETG.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 05.01.2020
 * PURPOSE: Determinant count 
 */
#include <commondf.h>

#include <stdio.h>
#include <math.h>
#include <conio.h>

typedef DOUBLE DBL;

#define MAX 10

DBL A[MAX][MAX], Det;
INT N;

/* Get matrix from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) Can open file or not.
 */
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
} /* End of 'LoadMatrix' function */


/* Swap two elements function.
 * ARGUMENTS:
 *   - pointers to swap elements:
 *       INT *A, INT *B;
 * RETURNS: None.
 */
VOID Swap( DBL *A, DBL *B )
{
  DBL tmp = *A;
  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

/* Count determinate function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID GaussCount( VOID )
{
  INT i, max_row, max_col, y, x, Row, Col;
  DBL K;

  Det = 1;
  for (i = 0; i < N; i++)
  {
    max_row = max_col = i;

    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_col = x, max_row = y;
    if (A[max_row][max_col] == 0)
    {
      Det = 0;
      break;
    }
    if (max_row != i)
    {
      for (x = i; x < N; x++)
        Swap(&A[i][x], &A[max_row][x]);
      Det = -Det;
    }

    if (max_col != i)
    {
      for (y = 0; y < N; y++)
        Swap(&A[y][i], &A[y][max_col]);
      Det = -Det;
    }

    for (Row = i + 1; Row < N; Row++)
    {
      K = A[Row][i] / A[i][i];

      A[Row][i];

      for (Col = i; Col < N; Col++)
        A[Row][Col] -= A[i][Col] * K;
    }

    Det *= A[i][i];
  }
} /* End of 'GaussCount' function */

/* Main program function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID main( VOID )
{
  LoadMatrix("IN.TXT");
  GaussCount();

  printf("Determinant: %lf", Det);
  _getch();
} /* End of 'main' function */
/* END OF 'T44DETG.C' FILE */