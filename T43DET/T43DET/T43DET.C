/* FILE NAME: T43DET.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 05.01.2020
 * PURPOSE: Determinant count 
 */
#include <commondf.h>

#include <stdio.h>

#include <conio.h>

typedef DOUBLE DBL;

#define MAX 10

DBL A[MAX][MAX], Determinant = 0;
INT N;

INT P[MAX];
BOOL Parity = 1;

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
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

/* Permaganation function.
 * ARGUMENTS:
 *   - current position:
 *       INT Pos;
 * RETURNS: None.
 */
VOID Go( INT Pos )
{
  INT i;
  DBL prod = 1;

  if (Pos == N)
  {
    for (i = 0; i < N; i++)
      prod *= A[i][P[i]];
    Determinant += (Parity * 2 - 1) * prod;
  }
  else
  {
    for (i = Pos; i < N; i++)
    {
      Swap(&P[Pos], &P[i]);
      if (Pos != i)
        Parity = !Parity;
      Go(Pos + 1);                                 
      if (Pos != i)
        Parity = !Parity;
      Swap(&P[Pos], &P[i]);
    }
  }
} /* End of 'Go' function */

/* Main program function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID main( VOID )
{
  INT i;

  LoadMatrix("IN.txt");

  for (i = 0; i < N; i++)
    P[i] = i;

  Go(0);

  printf("Determinant: %lf", Determinant);
  _getch();
} /* End of 'main' function */