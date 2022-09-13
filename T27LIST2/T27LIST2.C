/* Drekalov Nikita, 09-4, 15.11.2019 */
#include <stdio.h>
#include <conio.h>

#include "list2.h"

VOID main( VOID )
{
  LIST *L = NULL;
  INT Sw = 1, i;
  CHAR Str[MAX];

  printf("0 - exit\n"
    "1 - add to front\n"
    "2 - del from front\n"
    "3 - add to end\n"
    "4 - del from end\n"
    "5 - add to cur\n"
    "6 - del from cur\n"
    "7 - shift prev\n"
    "8 - shift next\n"
    "9 - clear list\n");
  while (Sw)
  {
    DisplayList(L);

    for (i = 0; i < MAX; i++)
      Str[i] = 0;
    switch (_getch())
    {
    case '0':
      Sw = 0;
      break;
    case '1':
      printf("New string: ");
      GetStr(Str, MAX);
      if (ListAddToFront(&L, Str))
        printf("Successful\n");
      else
        printf("Fail\n");
      break;
    case '2':
      if (ListDelFromFront(&L, Str))
      {
        printf("Deleted: ");
        i = 0;
        while (Str[i] != 0 || i >= MAX)
          printf("%c", Str[i++]);
        i = 0;
      }
      else
        printf("Fail\n");
      break;
    case '3':
      printf("New string: ");
      GetStr(Str, MAX);
      if (ListAddToEnd(&L, Str))
        printf("Successful\n");
      else
        printf("Fail\n");
      break;
    case '4':
      break;
    }
  }
}