/* Drekalov Nikita, 09-4, 14.10.2019 */
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

static DBL R0( void )
{
  return rand() / (DBL)RAND_MAX;
}

static DBL R1( void )
{
  return 2.0 * rand() / RAND_MAX - 1;
}

void FillRand( DBL *A, int N )
{
  int i;

  for (srand(30), i = 0; i < N; i++)
    A[i] = 30 * R1();
}

void FillIncr( DBL *A, int N )
{
  int i;

  for (srand(30), A[0] = 102 * R1(), i = 1; i < N; i++)
    A[i] = A[i - 1] + 30 * R0();
}

void FillDecr( DBL *A, int N )
{
  int i;

  for (srand(30), i = N - 2, A[i + 1] = 45 * R1(); i >= 0; i--)
    A[i] = A[i + 1] - 30 * R0(); 
}

void FillEq( DBL *A, int N )
{
  int i;

  for (i = 0, A[0] = 78 * R1(); i < N; i++)
    A[i] = A[0];
}

void Swap( DBL *A, DBL *B )
{
  *A += *B;
  *B = *A - *B;
  *A = *A - *B;
}

void FillMostly( DBL *A, int N )
{
  int i;

  FillIncr(A, N);

  for (i = 0; i < N; i++)
    Swap(&A[rand() % N], &A[rand() % N]);
}

void FillStep( DBL *A, int N )
{
  int Barier = 8, i;
  DBL Start = -R0() * 102, End = R0() * 78;

  for (i = 0; i < N; i++)
    A[i] = Start + i * Barier / N * (End - Start) / Barier;
}

void OutMas( DBL *A, int N )
{
  int i;

  for (i = 0; i < N; i++)
    printf("%f%c", A[i], i < N - 1 ? ',' : '\n');
}

int CheckSort( DBL *A, int N )
{
  int i;

  for (i = 0; i < N - 1; i++)
    if (A[i] > A[i + 1])
      return 0;
  return 1;
}