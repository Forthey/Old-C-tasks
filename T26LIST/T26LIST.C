/* Drekalov Nikita, 09-4, 11.11.2019 */
#include <stdio.h>
#include <conio.h>

#include "list.h"

VOID main( VOID )
{
  LIST *Start = NULL;
  INT NewElement;
  BOOL True = 1;
  SetDbgMemHooks();

  printf("0 - Exit\n"
    "1 - Add to list front\n"
    "2 - Delete from list back\n"
    "3 - Add to list back\n"
    "4 - Delete from list back\n"
    "7 - List clear\n");
  while (True)
  {
    switch (_getch())
  {
    case '0':
      True = 0;
      break;
    case '1':
      printf("Data amount: ");
      scanf("%i", &NewElement);
      if (!ListAddToFront(&Start, NewElement))
        printf("Sorry, something went wrong\n");
      break;
    case '2':
      if (!ListDelFromFront(&Start))
        printf("Error! The list is empty\n");
      break;
    case '3':
      printf("Data amount: ");
      scanf("%i", &NewElement);
      if (!ListAddToBack(&Start, NewElement))
        printf("Sorry, something went wrong\n");
      break;
    case '4':
      if (!ListDelFromBack(&Start))
        printf("Error! The list is Empty\n");
      break;
    case '7':
      while (ListDelFromFront(&Start))
        if (Start == NULL)
          printf("Succesful\n");
      break;
    default:
      printf("Incorrect choice\n");
      continue;
      break;
  }
    Display(Start);
  }
}