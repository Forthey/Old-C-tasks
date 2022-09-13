/* Drekalov Nikita, 09-4, 28.20.2019 */
#include <stdio.h>
#include <stdlib.h>

#include "fsort.h"

void Swap( DBL *x, DBL *y )
{
  DBL tmp = *x;
  *x = *y;
  *y = tmp;
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

int Count( FILE *F )
{
  int c = 0;

  while (fscanf(F, "%*f") != EOF)
    c++;
  return c;
}
  
void FileSort( void )
{
  DBL *A;
  int n, i;
  FILE *F;
  
  if ((F = fopen("IN.TXT", "r")) == NULL)
    return;
  n = Count(F);
  rewind(F);
  if ((A = malloc(sizeof(double) * n)) == NULL)
  {
    fclose(F);
    return;
  }
  for (i = 0; i < n; i++)
    fscanf(F, "%lf", &A[i]);
  fclose(F);
  QuickSort(A, n);
  if ((F = fopen("OUT.TXT", "w")) == NULL)
  {
    free(A);
    return;
  }
  for (i = 0; i < n; i++)
    fprintf(F, "%f%c ", A[i], i == (n - 1) ? '\n' : ',');
  fclose(F);
  free(A);
}