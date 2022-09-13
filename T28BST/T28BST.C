/* Drekalov Nikita, 09-4, 15.11.2019 */
#include <stdio.h>

#include <conio.h>

#include "bst.h"

VOID main( VOID )
{
  TREE *Root = NULL;
  INT Key, b;
  BOOL flag = 1;

  SetDbgMemHooks();

  printf("0 - Exit\n"
    "1 - Find or add key\n"
    "2 - Find or add key(2)\n"
    "3 - Draw tree\n"
    "4 - Clear tree\n"
    "5 - Delete current key\n"
    "6 - Balance tree\n"
    "9 - Add keys\n");

  while (flag)
  {
    PutTree(Root);
    printf("\n");
    PutTree2(Root);
    printf("\n");
    switch (_getch())
    {
    case '0':
      flag = 0;
      break;

    case '1':
      printf("Key: ");
      scanf("%i", &Key);
      if (AccessTree(&Root, Key))
        printf("Successful\n");
      else
        printf("Error\n");
      continue;
      break;

    case '2':
      printf("Key: ");
      scanf("%i", &Key);
      if (AccessTree1(&Root, Key))
        printf("Successful\n");
      else
        printf("Error\n");
      continue;
      break;

    case '3':
      DrawTree(Root);
      break;

    case '4':
      ClearTree(&Root);
      break;

    case '5':
      printf("Key: ");
      scanf("%i", &Key);
      if (DeleteKey(&Root, Key))
        printf("Successful\n");
      else
        printf("Error\n");
      continue;
      break;

    case '6':
      Linearize(&Root);
      /* BalanceTree(&Root, Linearize(&Root)); */
      break;

    case '9':
      do
      {
        scanf("%i", &b);
        if (b == 30)
          break;
        AccessTree(&Root, b);
      } while (b != 30);
      break;

    default:
      printf("Invalid number\n");
      continue;
      break;
    }
    printf("0 - Exit\n"
    "1 - Find or add key\n"
    "2 - Find or add key(2)\n"
    "3 - Draw tree\n"
    "4 - Clear tree\n"
    "5 - Delete key\n"
    "9 - Add keys (30 to end)\n");
  }
}