/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <stdio.h>

#include "ugl.h"

/* Add to queue tail */
VOID Put( QUEUE *Q, TOK T )
{                                        
  LIST *NewElement = malloc(sizeof(LIST));

  if (NewElement == NULL)
    Error("No memory");

  NewElement->T = T;

  NewElement->Next = NULL;

  if (Q->Head == NULL)
  {
    Q->Head = Q->Tail = NewElement;
    Q->Head->Next = NULL;
  }
  else
    Q->Tail->Next = NewElement, Q->Tail = NewElement;

}

/* Get from queue head */
INT Get( QUEUE *Q, TOK *T )
{
  LIST *Old;

  if (Q == NULL || Q->Head == NULL)
    return 0;


  *T = Q->Head->T;

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
    if (L->T.Id == TOK_NUM)
      printf("%f", L->T.Num);
    if (L->T.Id == TOK_OP)
      printf("%c", L->T.Op);

    if (L->Next == NULL)
      printf("\n");
    else
      printf(" ");
    L = L->Next;
  }
}

VOID DisplayQueue( QUEUE *Q )
{
  DisplayList(Q->Head);
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

VOID ClearStack( STACK *StackEval )
{
  ClearList(&StackEval->Top);
}

/* Add to stack top */
INT Push( STACK *S, TOK T )
{
  LIST *NewElement = malloc(sizeof(LIST)),
    *tmp;  

  if (NewElement == NULL)
    return 0;

  NewElement->T = T;

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

/* Get from stack top */
INT Pop( STACK *S, TOK *T )
{
  LIST *Old;

  if (S->Top == NULL)
    return 0;

  *T = S->Top->T; 

  Old = S->Top;
  S->Top = S->Top->Next;

  free(Old);
  return 1;
}