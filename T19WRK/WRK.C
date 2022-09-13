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
}
{
 int N;
 FILE *F;
 if ((F = fopen(FileName, "rb")) == NULL)
 return 0;
 N = fread(Base, sizeof(WORKER), MaxSize, F);

 fclose(F);
 return N;
}
{
 int n = strcmp(A.Surname, B.Surname);

 if (n == 0)
   return strcmp(A.Name, B.Name) < 0;
 return n < 0;
}
{
  if (A.Birthday.Year == B.Birthday.Year)
  if (A.Birthday.Month == B.Birthday.Month)
   return A.Birthday.Day < B.Birthday.Day;
  else
   return A.Birthday.Month < B.Birthday.Month;
  else
   return A.Birthday.Year < B.Birthday.Year;
}