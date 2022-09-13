/* Drekalov Nikita, 09-4, 20.11.2019 */
#include <stdio.h>
#include <commondf.h>

#include "huf.h"

static LONG Freq[256];
static TREE *Nodes[256];
static INT NumOfNodes;

static VOID PlaceNode( CHAR Ch, LONG Freq, TREE *L, TREE *R )
{
  TREE *T = malloc(sizeof(TREE));
  INT i;

  if (T == NULL)
    return;

  T->Ch = Ch;
  T->Freq = Freq;
  T->Left = L;
  T->Right = R;

  i = NumOfNodes - 1;


  if (i >= 0 && Nodes[i]->Freq < T->Freq)
    Nodes[i + 1] = Nodes[i], i--;

  Nodes[i + 1] = T;
  NumOfNodes++;
}

VOID CountFreq( FILE *F )
{
  INT i;

  memset(Freq, 0, sizeof Freq);

  while ((i = fgetc(F)) != EOF)
    Freq[i]++;

  for (i = 0; i < 256; i++)
    if (Freq[i] > 0)
      printf("%c ((%d)) count: %ld\n", i < 32 ? '.' : i, i,  Freq[i]); 
}

VOID BuildForest( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
    if (Freq[i] > 0)
      PlaceNode(i, Freq[i], NULL, NULL);
}

VOID CollapseForest( VOID )
{
  TREE *Last, *PreLast;

  while (NumOfNodes > 1)
  {
    Last = Nodes[--NumOfNodes];
    PreLast = Nodes[--NumOfNodes];

    PlaceNode(' ', Last->Freq + PreLast->Freq, PreLast, Last);
  }
}

VOID Stat( CHAR *FileName )
{
  FILE *F;

  if ((F = fopen(FileName, "r")) == NULL)
    return;

  CountFreq(F);
  BuildForest();
  CollapseForest();

  fclose(F);
}