/* Drekalov Nikita, 09-4, 30.10.2019 */
#include <stdio.h>
#include <conio.h>

#include "wrk.h"

#define MAX 10

void main( void )
{
  int flag = 1, DBSize = 0;
  static WORKER DB[MAX];
  char fname[100], s;

  printf("     ~~~Database~~~\n\n"
    "0 - Exit the program\n"
    "1 - Register a worker\n"
    "2 - Display all registered workers\n"
    "3 - Delete worker\n"
    "4 - Workers sort\n"
    "5 - Base reverse\n"
    "6 - Save\n"
    "7 - Load\n"
    "8 - Edit\n"
    "9 - Salary\n");
  while (flag)
    switch (_getch())
    {
    case '0':
      {
        flag = 0;
        break;
      }
    case '1':
      {
        if (DBSize < MAX)
          ReadWorker(&DB[DBSize++]);
        else
          printf("Not enough room\n");
        break;
      }
    case '2':
      {
        DisplayWorkers(DB, DBSize);
        break;
      }
    case '3':
      {
        WorkerDelete(DB, DBSize);
        DBSize--;
        break;
      }
    case '4':
      {
        printf("N - Sort by name\n"
          "B - Sort by birthday\n");
        scanf("%c", &s);
        if (s == 'N' || s == 'n')
          SurnSort(DB, DBSize);
        else if (s == 'B' || s == 'b')
          DateSort(DB, DBSize);
        else
          printf("Incorrect choice\n");
        GetStr(NULL, 0);
        break;
      }
    case '5':
      {
        BaseReverse(DB, DBSize);
        break;
      }
    case '6':
      {
        printf("Save file name: ");
        GetStr(fname, sizeof(fname));
        if (SaveDB(fname, DB, DBSize))
          printf("Ok\n");
        else
          printf("Error\n");
        break;
      }
    case '7':
      {
        printf("Load file name: ");
        GetStr(fname, sizeof(fname));
        DBSize = LoadDB(fname, DB, MAX);
        printf("Load %d records\n", DBSize);
        break;
      }
    case '8':
      {
      }
    case '9':
      {
        Salary(DB, DBSize);
        break;
      }
    default:
      {
        printf("Incorrect choise\n"
          "0 - exit the program\n"
          "1 - register a worker\n"
          "2 - Display all registered workers\n"
          "3 - Delete worker\n"
          "4 - Workers sort\n"
          "5 - Base reverse\n"
          "6 - Save\n"
          "7 - Load\n"
          "9 - Salary\n"
          );
      }
    }
}