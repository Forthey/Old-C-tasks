/* Drekalov Nikita, 09-4, 30.10.2019 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "wrk.h"

static int *cost;

void GetStr( char *Name, int MaxLen )
{
  int i = 0;
  char ch;

  while ((ch = getchar()) != '\n' && (ch = getchar()) != 32)
    if (Name != NULL && i < MaxLen - 1)
      Name[i++] = ch;
  if (Name != NULL && i < MaxLen)
    Name[i] = 0;
}
void ReadWorker( WORKER *W )
{
  printf("Name: %s", W->Name);
  GetStr(W->Name, sizeof W->Name);
  printf("Surname: ");
  GetStr(W->Surname, sizeof W->Surname);
  printf("Birthday:\n  Day: ");
  scanf("%d", &W->Birthday.Day);
  GetStr(NULL, 0);
  printf("  Month: ");
  scanf("%d", &W->Birthday.Month);
  GetStr(NULL, 0);
  printf("  Year: ");
  scanf("%d", &W->Birthday.Year);
  GetStr(NULL, 0);
  printf("Gender (m/f):");
  scanf("%c", &W->Sex);
  GetStr(NULL, 0);
  printf("Office hours:\n  Monday: ");
  scanf("%d", &W->Hours[0]);
  GetStr(NULL, 0);
  printf("  Tuesday: ");
  scanf("%d", &W->Hours[1]);
  GetStr(NULL, 0);
  printf("  Wednesday: ");
  scanf("%d", &W->Hours[2]);
  GetStr(NULL, 0);
  printf("  Thursday: ");
  scanf("%d", &W->Hours[3]);
  GetStr(NULL, 0);
  printf("  Friday: ");
  scanf("%d", &W->Hours[4]);
  GetStr(NULL, 0);
  printf("  Saturday: ");
  scanf("%d", &W->Hours[5]);
  GetStr(NULL, 0);
  printf("  Sunday: ");
  scanf("%d", &W->Hours[6]);
  GetStr(NULL, 0);
}

void DisplayWorkers( WORKER *W, int N )
{
  int i;

  for (i = 0; i < N; i++)
  {
    printf("Worker No %i:\n", i + 1);
    printf("  Name: %s", (W + i)->Name);
    printf("\n  Surname: %s", (W + i)->Surname);
    printf("\n  Birthday:\n"
      "    Day: %02d\n"
      "    Month: %02d\n"
      "    Year: %d\n", 
      (W + i)->Birthday.Day, 
      (W + i)->Birthday.Month, 
      (W + i)->Birthday.Year);
    printf("  Sex: %c", (W + i)->Sex);
    printf("  Office hours:\n"
      "    Monday: %d\n"
      "    Tuesday: %d\n"
      "    Wednesday: %d\n"
      "    Thursday: %d\n"
      "    Friday: %d\n"
      "    Saturday: %d\n"
      "    Sunday: %d\n\n",
      (W + i)->Hours[0],
      (W + i)->Hours[1],
      (W + i)->Hours[2],
      (W + i)->Hours[3],
      (W + i)->Hours[4],
      (W + i)->Hours[5],
      (W + i)->Hours[6]);
  }
}

int SaveDB( char *FileName, WORKER *Base, int N )
{
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
  return 0;
  fwrite(Base, sizeof(WORKER), N, F);
  fclose(F);
  return 1;
}int LoadDB( char *FileName, WORKER *Base, int MaxSize )
{
 int N;
 FILE *F;
 if ((F = fopen(FileName, "rb")) == NULL)
 return 0;
 N = fread(Base, sizeof(WORKER), MaxSize, F);

 fclose(F);
 return N;
}static void SwapWorkers( WORKER *A, WORKER *B ){  WORKER tmp = *A;  *A = *B;  *B = tmp;}void WorkerDelete( WORKER *W, int N ){  int i;  printf("No: ");  scanf("%i", &i);  while (i < N)    W[i - 1] = W[i++];}void BaseReverse( WORKER *W, int N ){  int i = 0;  while (i < N)    SwapWorkers(&W[i++], &W[N--]);}static int IsNameLess( WORKER A, WORKER B )
{
 int n = strcmp(A.Surname, B.Surname);

 if (n == 0)
   return strcmp(A.Name, B.Name) < 0;
 return n < 0;
}void SurnSort( WORKER *W, int N ){  int i, j;  for (i = 0; i < N; i++)    for (j = 1; j < N - i - 1; j++)      if (IsNameLess(W[i], W[j]))        SwapWorkers(&W[i], &W[j]);}int IsDateLess( WORKER A, WORKER B )
{
  if (A.Birthday.Year == B.Birthday.Year)
  if (A.Birthday.Month == B.Birthday.Month)
   return A.Birthday.Day < B.Birthday.Day;
  else
   return A.Birthday.Month < B.Birthday.Month;
  else
   return A.Birthday.Year < B.Birthday.Year;
}void DateSort( WORKER *W, int N ){  int i, j;  for (i = 0; i < N; i++)    for (j = 1; j < N - i - 1; j++)      if (IsDateLess(W[i], W[j]))        SwapWorkers(&W[i], &W[j]);}void Salary( WORKER *W, int N ){  int i, j, Daycnt[7], costh;  cost = malloc(sizeof(int) * N);  for (i = 0; i < N; i++)    cost[i] = 0;  printf("Amount of days:\n  Monday: ");  scanf("%i", &Daycnt[0]);  GetStr(NULL, 0);  printf("  Tuesday: ");  scanf("%i", &Daycnt[1]);  GetStr(NULL, 0);  printf("  Wednesday: ");  scanf("%i", &Daycnt[2]);  GetStr(NULL, 0);  printf("  Thursday: ");  scanf("%i", &Daycnt[3]);  GetStr(NULL, 0);  printf("  Friday: ");  scanf("%i", &Daycnt[4]);  GetStr(NULL, 0);  printf("  Saturday: ");  scanf("%i", &Daycnt[5]);  GetStr(NULL, 0);  printf("  Sunday: ");  scanf("%i", &Daycnt[6]);  GetStr(NULL, 0);    printf("Hour cost: ");  scanf("%i", &costh);  GetStr(NULL, 0);  for (i = 0; i < N; i++)    for (j = 0; j < 7; j++)      cost[i] += Daycnt[j] * W[i].Hours[j] * costh;   for (i = 0; i < N; i++)    printf("Salary for No %i: %i\n", i + 1, cost[i]);}void EditWorkers( WORKER *W, int N ){  int i, j;  printf("Worker No: ");  scanf("%i", &i);  GetStr(NULL, 0);  if (!(i >= 1 && i <= N))  {    printf("Worker doesn't exist\n");    return;  }  printf("What do you want to change?\n"    "1 - Name\n"    "2 - Surname\n"    "3 - Birthday\n"    "4 - Sex\n"    "5 - Worked hours\n");  switch (_getch())  {  case '1':    {      printf("Current name: %s\n"        "New name: ", W[i].Name);      for (j = 0; j < 30; j++)        W[i].Name[j] = 0;      GetStr(W[i].Name, sizeof W[i].Name);      break;    }  case '2':    {      printf("Current surname: %s\n"        "New name: ", W[i].Surname);      for (j = 0; j < 47; j++)        W[i].Surname[j] = 0;      GetStr(W[i].Surname, sizeof W[i].Surname);      break;    }  case '3':    {      printf("Current birthday: %02d %02d %02d"        "Input new birthday(DD MM YYYY): ", W[i].Birthday.Day, W[i].Birthday.Month, W[i].Birthday.Year);      scanf("%i", &W[i].Birthday.Day);      scanf("%i", &W[i].Birthday.Month);      scanf("%i", &W[i].Birthday.Year);      GetStr(NULL, 0);    }  }}