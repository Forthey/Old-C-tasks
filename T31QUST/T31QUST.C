/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <stdio.h>
#include <conio.h>

#include "qust.h"

VOID main( VOID )
{
  INT key = 1, x;
  QUEUE Q = {NULL};
  STACK S = {NULL};

  SetDbgMemHooks();

  while (key)
  {
    DisplayQueue(&Q);
    DisplayStack(&S);
    printf("0 - exit\n"
      "1 - Put\n"
      "2 - Get\n"
      "5 - Clear\n");
    switch (_getch())
    {
    case '0':
      key = 0;
      ClearQueue(&Q);
      break;
    case '1':
      printf("X: ");
      scanf("%i", &x);
      Put(&Q, x);
      break;
    case '2':
      Get(&Q, &x);
      printf("%i have deleted\n", x);
      break;
    case '3':
      printf("X: ");
      scanf("%i", &x);
      Push(&S, x);
      break;
    case '4':
      Pop(&S, &x);
      break;
    case '5':
      ClearQueue(&Q);
      break;
    }
  }
}