/* Drekalov Nikita, 09-4, 18.11.2019 */
#include <stdio.h>
#include <conio.h>

#include "fur.h"

VOID main( VOID )
{
  TREE *ExSys;
  CHAR Key = 1, Ch;

  SetDbgMemHooks();
  
  system("chcp 1251");

  ExSys = Init("??", NULL, NULL);

  while (Key)
  {
    printf("0 - ?????\n"
      "1 - ?????\n"
      "2 - ?????\n"
      "3 - ?????????\n"
      "4 - ?????????\n>");
    switch (Ch = _getch())
    {
    case '0':
      Key = 0;
      printf(" %c\n", Ch);
      break;
    case '1':
      printf(" %c\n", Ch);
      Session(&ExSys);      
      break;
    case '2':
      printf(" %c\n", Ch);
      DrawTree(ExSys);
      break;
    case '3':
      printf(" %c\n", Ch);
      SaveTree("Tree.db", ExSys);
      break;
    case '4':
      printf(" %c\n", Ch);
      LoadTree("Tree.db", &ExSys);
      break;
    }
  }
}