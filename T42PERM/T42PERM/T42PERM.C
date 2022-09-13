/* FILE NAME: T42PERM.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 05.01.2020
 * PURPOSE: Write in file 
 */
#include <commondf.h>

#include <stdio.h>
#include <conio.h>

#define N 5

INT P[N], Parity = 1, ParityOld;

/* Save to file function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID SavePerm( VOID )
{
  INT i;

  freopen("PERM.txt", "a", stdout);

  for (i = 0; i < N - 1; i++)
    printf("%d,", P[i]);
  printf("%d - %s\n", P[N - 1], Parity ? "even" : "odd");


} /* End of 'SavePerm' function */

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

  if (Pos == N)
    SavePerm();
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

/* Main program function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID main( VOID )
{
  INT i;

  P[0] = 1;

  for (i = 1; i < N; i++)
    P[i] = P[i - 1] + 1;
  Go(0);

  _getch();
} /* End of 'main' functon */
