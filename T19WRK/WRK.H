/* Drekalov Nikita, 09-4, 30.10.2019 */
typedef struct
{
  int Day, Month, Year;
} DATE;

typedef struct
{
  char Name[30], Surname[47];
  DATE Birthday;
  char Sex;
  int Hours[7];
} WORKER;

void Salary( WORKER *W, int N );
void DateSort( WORKER *W, int N );
void SurnSort( WORKER *W, int N );
void BaseReverse( WORKER *W, int N );
void WorkerDelete( WORKER *W, int N );
void ReadWorker( WORKER *W );
void DisplayWorkers( WORKER *W, int N );
void GetStr( char *Name, int MaxLen );
int SaveDB( char *FileName, WORKER *Base, int N );
int LoadDB( char *FileName, WORKER *Base, int N );