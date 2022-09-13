/* Drekalov Nikita, 09-4, 28.10.2019 */
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "dsort.h"
#define MAX 100000

void main( void )
{
  UINT64 mas[MAX];
  long t1, t2;

  FillRand(mas, MAX);
  t1 = clock();
  NumSort(mas, MAX);
  t1 = clock() - t1;
  //OutMas(mas, MAX);
  t2 = clock();
  QuickSort(mas, MAX);
  t2 = clock() - t2;
  //OutMas(mas, MAX);
  printf("Digital sort time: %f\n", (double)t1 / CLOCKS_PER_SEC);
  printf("Quick sort time: %f\n", (double)t2 / CLOCKS_PER_SEC);

  _getch();
}