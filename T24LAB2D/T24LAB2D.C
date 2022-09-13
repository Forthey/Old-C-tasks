/* Drekalov Nikita, 09-4, 02.11.2019 */
#include <stdio.h>
#include <commondf.h>
#include <conio.h>

#define MAX 100
#define INFINITY 100000

INT Adj[MAX][MAX], Was[MAX], Path[MAX], PathLen, BestPathLen, BestPath[MAX], 
    Len[MAX] = {INFINITY}, From[MAX] = {-1};
static CHAR Buf[1000];

VOID LabOut( INT *Paths, INT Len )
{
  INT i;

  for (i = 0; i < PathLen; i++)
    printf("%d%s", Paths[i], i == Len - 1 ? "\n" : ",");
  printf("Lenght: %i\n", Len);
}

VOID LabLoad( CHAR *FileName )
{
  INT A, B, n, len;
  FILE *F;

  if ((F = fopen(FileName, "r")) != NULL)
    while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    {
      n = sscanf(Buf, "%d%d%d", &A, &B, &len);
      if (n == 2)
        len = 1;
      if (n > 2)
        Adj[A][B] = Adj[B][A] = len;
    }
}

INT WayAny( INT A, INT B )
{
  INT i;

  Was[A] = 1;

  if (Adj[A][B] == 1)
  { 
    Path[PathLen++] = B;
    LabOut(Path, PathLen);
    return 1;
  }
  for (i = 0; i < MAX; i++)
    if (i != A && i != B && Was[i] == 0 && Adj[A][i] != 0)
    {
      Was[i] = 1;
      Path[PathLen++] = i;
      if (WayAny(i, B))
        return 1;
      PathLen--;
    }
  return 0;
}

VOID WayAll( INT A, INT B )
{
  INT i;
  Was[A] = 1;

  if (Adj[A][B] == 1)
  { 
    Path[PathLen++] = B;
    LabOut(Path, PathLen);
    PathLen--;
    if (PathLen != 0)
      return;
  }
  for (i = 0; i < MAX; i++)
    if (i != A && i != B && Was[i] == 0 && Adj[A][i] != 0)
    {
      Was[i] = 1;
      Path[PathLen++] = i;
      WayAll(i, B);
      Was[i] = 0;
      PathLen--;
    }
}

INT WayBest( INT A, INT B )
{
  INT i;

  Was[A] = 1;

  if (Adj[A][B] == 1)
  { 
    Path[PathLen++] = B;
    LabOut(Path, PathLen);
    if (BestPathLen == 0 || PathLen < BestPathLen)
    {
      BestPathLen = PathLen;
      memcpy(BestPath, Path, sizeof(Path));
    }
    return 1;
  }
  for (i = 0; i < MAX; i++)
    if (i != A && i != B && Was[i] == 0 && Adj[A][i] != 0)
    {
      Was[i] = 1;
      Path[PathLen++] = i;
      if (WayAny(i, B))
        return 1;
      PathLen--;
    }
  return 0;
}

VOID Display( VOID )
{
  int i;
  for (i = 0; i < MAX; i++)
    printf("%i ", Path[i]);
}

VOID FindWay( INT B )
{
  INT i, j, k;
  INT From1[MAX], Len1[MAX], Flag[MAX] = {0};

  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++)
      if (Len[i] > Len[j] + Adj[i][j] && Flag[i] == 0 && i != B)
        Len1[i] = Len[j] + Adj[i][j], Flag[i] = 1, From1[i] = j;
  Display();
}

VOID main( VOID )
{
  INT b, i, j;
 
  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++)
      Adj[i][j] = INFINITY;

  LabLoad("UpgrLab.txt");

  /* printf("A: ");
  scanf("%i", &a); */
  printf("B: ");
  scanf("%i", &b);

  Len[b] = 0;

  FindWay(b);

  /* WayAny(a, b); 

  PathLen = 0;

  WayAll(a, b);

  PathLen = 0;

  WayBest(a, b); */

  _getch();
}