/* Drekalov Nikita, 09-4, 14.10.2019 */
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "sort.h"

#define MAX 1000000

void main( void )
{
  static DBL mas[MAX] = {0};
  int fi, si;
  void (*Fill[])( DBL *A, int N ) = {FillRand, FillIncr, FillDecr, FillEq, FillMostly, FillStep};
  void (*Sort[])( DBL *A, int N ) = {/*BubbleSort1, BubbleSort2, BubbleSort3, BubbleSort4, InsertionSort, SelectionSort,*/ MergeSort, QuickSort, HeapSort};
  char *SNames[] = {/*"Bubble1", "Bubble2", "Bubble3", "Bubble4", "Insertion", "Selection",*/ "Merge", "Quick", "Heap"};
  long t;

  printf("                                   Array sorting\n\n"
         "    FillRand      FillIncr      FillDecr      FillEqup      FillMost      FillStep\n");
 
  for (si = 0; si < sizeof(Sort) / sizeof(Sort[0]); si++)
  {
    printf("%s:\n", SNames[si]);
    for (fi = 0; fi < sizeof(Fill) / sizeof(Fill[0]); fi++)
    {
      Fill[fi](mas, MAX);
      t = clock();
      Sort[si](mas, MAX);
      t = clock() - t;
      if (CheckSort(mas, MAX))
        printf("  %10.5f  ", t / (DBL)CLOCKS_PER_SEC);
      else
        printf("      FAIL    ");
    }
    printf("\n");
  }

  _getch();
}
