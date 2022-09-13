/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <stdio.h>

#include "qust.h"

/* Add to end */
INT Put( QUEUE *Q, INT NewData )
{
  LIST *NewElement = malloc(sizeof(LIST));


  if (NewElement == NULL)
    return 0;

  NewElement->Data = NewData;
  NewElement->Next = NULL;

  if (Q->Head == NULL)
    Q->Head = Q->Tail = NewElement;
  else
    Q->Tail->Next = NewElement, Q->Tail = NewElement;

  return 1;
}

/* Delete from start */
INT Get( QUEUE *Q, INT *OldData )
{
  LIST *Old;

  if (Q == NULL)
    return 0;

  *OldData = Q->Head->Data;
  Old = Q->Head;
  Q->Head = Q->Head->Next;

  free(Old);

  return 1;
}

VOID DisplayList( LIST *L )
{
  if (L == NULL)
    printf("<empty>\n");

  while (L != NULL)
  {
    printf("%i%s", L->Data, L->Next == NULL ? "\n" : " -> ");
    L = L->Next;
  }
}

VOID DisplayQueue( QUEUE *Q )
{
  DisplayList(Q->Head);
}

VOID DisplayStack( STACK *S )
{
  DisplayList(S->Top);
}

VOID ClearList( LIST **L )
{
  LIST *Old;

  if (*L == NULL)
    return;

  while (*L != NULL)
  {
    Old = *L;
    *L = Old->Next;
    free(Old);
  }
}

/* Clear queue */
VOID ClearQueue( QUEUE *Q )
{
  ClearList(&Q->Head);
}

/* Add to start */
INT Push( STACK *S, INT NewData )
{
  LIST *NewElement = malloc(sizeof(LIST)),
    *tmp;  

  if (NewElement == NULL)
    return 0;

  NewElement->Data = NewData;

  if (S == NULL)
  {
    S->Top = NewElement;
    NewElement->Next = NULL;
  }
  else
  {
    tmp = S->Top;
    S->Top = NewElement;
    NewElement->Next = tmp;
  }
  return 1;
}

/* Delete from start */
INT Pop( STACK *S, INT *OldData )
{
  LIST *Old;

  if (S->Top == NULL)
    return 0;

  *OldData = S->Top->Data; 

  Old = S->Top;
  S->Top = S->Top->Next;

  free(Old);
  return 1;
}