/* Drekalov Nikita, 09-4, 14.10.2019 */
#include <stdlib.h>
#include <string.h>
#include "sort.h"

static DBL B[1000000];
void BubbleSort1( DBL *A, int N )
{
  int k, i;

  for (k = 0; k < N - 1; k++)
    for (i = 0; i < N - 1; i++)
      if (A[i] > A[i + 1])
        Swap(&A[i], &A[i + 1]);
}

void BubbleSort2( DBL *A, int N )
{
  int k, i;

  for (k = 0; k < N - 1; k++)
    for (i = 0; i < N - 1 - k; i++)
      if (A[i] > A[i + 1])
        Swap(&A[i], &A[i + 1]);

}

void BubbleSort3( DBL *A, int N )
{
  int i, flag;

  do
  {
    for (flag = 0, i = 0; i < N - 1; i++)
      if (A[i] > A[i + 1])
        Swap(&A[i], &A[i + 1]), flag = 1;
  } while (flag);
}

void BubbleSort4( DBL *A, int N )
{
  int i, last, changed;

  last = N - 2;
  do 
  {
    changed = 0;
    for (i = 0; i <= last; i++)
      if (A[i] > A[i + 1])
        Swap(&A[i], &A[i + 1]), changed = i;
    last = changed - 1;
  } while (last >= 0);
}

void InsertionSort( DBL *A, int N )
{
  DBL x;
  int i, j;

  for (i = 0; i < N; i++)
  {
    x = A[i];
    j = i - 1;
    while (j >= 0 && A[j] > x)
      A[j + 1] = A[j], j--;
    A[j + 1] = x;
  }
}

void SelectionSort( DBL *A, int N )
{
  int i, j, min;

  for (j = 0; j < N - 2; j++)
  {
    for (i = j + 1, min = j; i < N; i++)
      if (A[i] < A[min])
        min = i;
    Swap(&A[min], &A[j]);
  }

}

void ShakerSort( DBL *A, int N )
{
  int i, j;

  for (j = 0; j < N / 2; j++)
  {
    for (i = 0; i < N - 1; i++)
      if (A[i] > A[i + 1])
        Swap(&A[i], &A[i + 1]);
    for (i = N - 1; i > 0; i--)
      if (A[i] < A[i - 1])
        Swap(&A[i], &A[i - 1]);
  }
}

static void MergeSortRec( DBL *A, int N )
{
  int m, k, i, j;

  if (N < 2)
    return;
  m = N / 2;
  MergeSort(A, m);
  MergeSort(A + m, N - m);

  i = 0;
  j = m;
  k = 0;
  
  while (k < N)
    if (j >= N || i < m && A[i] <= A[j])
      B[k++] = A[i++];
    else
      B[k++] = A[j++];
  memcpy(A, B, sizeof(DBL) * N);
}

void MergeSort( DBL *A, int N )
{
  MergeSortRec(A, N);
}


void QuickSort( DBL *A, int N )
{
  DBL x; 
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
 

static void HeapCorrection( DBL *A, int N, int i )
{
  while (1)
  {
    int 
      left = 2 * i + 1, 
      right = 2 * i + 2, 
      big = i;

    if (left < N && A[left] > A[i])
      big = left;
    if (right < N && A[right] > A[big])
      big = right;

    if (big == i)
      return;
    Swap(&A[big], &A[i]);
    i = big;
  }
}

void HeapSort( DBL *A, int N )
{
  int i, k = 1;

  for (i = N / 2; i >= 0; i--)
    HeapCorrection(A, N, i);
  for (i = 1; i < N; i++)
  {
    Swap(&A[0], &A[N - i]);
    HeapCorrection(A, N - i, 0);
  }

}