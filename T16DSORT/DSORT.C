/* Drekalov Nikita, 09-4, 28.10.2019 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsort.h"

static UINT64 *B;

void FillRand( UINT64 *A, int N )
{
  int i;

  for (i = 0; i < N; i++)
    A[i] = rand() * (rand() % 40);
}

void NumSort( UINT64 *A, int N )
{
  int i, Count[256], Offset[256], digit_count, shift;
  
  if ((B = malloc(sizeof(UINT64) * N)) == NULL)
    return;

  for (digit_count = 0, shift = 8 ; digit_count < 10; digit_count++, shift += 8)
  {
    memset(Count, 0, sizeof(Count));

    for (i = 0; i < N; i++)
      Count[A[i] >> shift & 255]++;

    for (Offset[0] = 0, i = 1; i < 256; i++)
      Offset[i] = Offset[i - 1] + Count[i - 1];

    for (i = 0; i < N; i++)
      B[Offset[A[i] >> shift & 255]++] = A[i];

    for (i = 0; i < N; i++)
      A[i] = B[i];
  }

  free(B);
}

void OutMas( UINT64 *A, int N )
{
  int i;

  for (i = 0; i < N; i++)
    printf("%lli%c", A[i], i < N - 1 ? ',' : '\n');
}

static void Swap( UINT64 *A, UINT64 *B )
{
  *A += *B;
  *B = *A - *B;
  *A = *A - *B;
}


void QuickSort( UINT64 *A, int N )
{
  UINT64 x; 
  int b = 0, e = N - 1;

  if (N < 2)
    return;
  x = A[N / 2];
  while (b <= e)
  {
    while (A[b] < x)
      b++;
    while (A[e] > x)
      e--;
    if (b <= e)
    {
      if (b != e)
        Swap(&A[b], &A[e]);
      b++;
      e--;
    }
  }
  QuickSort(A, e + 1);
  QuickSort(A + b, N - b);
}

int CheckSort( UINT64 *A, int N )
{
  int i;

  for (i = 0; i < N - 1; i++)
    if (A[i] > A[i + 1])
      return 0;
  return 1;
}