/* Drekalov Nikita, 09-4, 16.12.2019 */
#include "gfx.h"

/* Point stock structure */
typedef struct tagnd4LIST nd4LIST;
struct tagnd4LIST
{
  INT Y, Left, Right;
  nd4LIST *Next;
} *ND4_LineList;

/* Put line on top function */
static VOID ND4_Store( INT L, INT R, INT Y )
{
  nd4LIST *NewElement, *tmp;
  
  if ((NewElement = malloc(sizeof(nd4LIST))) == NULL)
    return;

  if (ND4_LineList == NULL)
  {
    NewElement->Next = NULL;
    ND4_LineList = NewElement;
  }
  else
  {
    tmp = ND4_LineList;
    ND4_LineList = NewElement;
    NewElement->Next = tmp;
  }
  NewElement->Left = L;
  NewElement->Right = R;
  NewElement->Y = Y;
} /* End of 'ND4_Store' function */

/* Delete line from top function */
static BOOL ND4_Restore( INT *L, INT *R, INT *Y )
{
  nd4LIST *Old = ND4_LineList;

  if (ND4_LineList == NULL)
    return FALSE;

  *L = ND4_LineList->Left;
  *R = ND4_LineList->Right;
  *Y = ND4_LineList->Y;

  ND4_LineList = ND4_LineList->Next;

  free(Old);
  return TRUE;
} /* End of 'ND4_Restore' function */

/* Fill with current color function */
VOID ND4_FloodFill( INT X, INT Y, DWORD Color )
{
  DWORD BackColor = ND4_GetPix(X, Y);
  INT L, R, x, i, left;

  if (ND4_GetPix(X, Y) == Color)
    return;

  ND4_Store(X, X, Y);

  while (ND4_Restore(&L, &R, &Y))
  {
    /* Look for left/right border */
    L--;
    while (L >= 0 && ND4_GetPix(L, Y) == BackColor)
      L--;
    L++;
    R++;
    while (R < ND4_FrameWidth && ND4_GetPix(R, Y) == BackColor)
      R++;
    R--;

    /* Draw horisontal line */
    for (i = L; i <= R; i++)
      if (ND4_GetPix(i, Y) == BackColor)
        ND4_PutPixel(i, Y, Color);

    /* Scan for upper/lower lines */
    Y--;
    x = L;
    while (x <= R)
    {
      /* Skip unflood spaces */
      while (x <= R && ND4_GetPix(x, Y) != BackColor)
        x++;
      if (x <= R)
      {
        /* Select horizontal line segment */
        left = x;
        while (x <= R && ND4_GetPix(x, Y) == BackColor)
          x++;
        ND4_Store(left, x - 1, Y);
      }
    }

    Y += 2;

    x = L;
    while (x <= R)
    {
      /* Skip unflood spaces */
      while (x <= R && ND4_GetPix(x, Y) != BackColor)
        x++;
      if (x <= R)
      {
        /* Select horizontal line segment */
        left = x;
        while (x <= R && ND4_GetPix(x, Y) == BackColor)
          x++;
        ND4_Store(left, x - 1, Y);
      }
    }
  }
} /* End of 'ND4_FloodFill' function */
/* END OF 'GFX04.C' FILE */