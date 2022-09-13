/* Drekalov Nikita, 09-4, 16.12.2019 */
#include <math.h>

#include "gfx.h"

/* Pseudo swap fucntion */
#define Swap(A, B, C) ((C) = (A), (A) = (B), (B) = (C))

/* Create aline between two doughts function */
VOID ND4_PutLine( INT X2, INT Y2, INT X1, INT Y1, DWORD Color)
{
  INT Count, Dx, Dy, F, IncrNE, IncrE, Tmp, sx;

  if (Y1 > Y2)
    Swap(Y1, Y2, Tmp), Swap(X1, X2, Tmp);

  Dx = X2 - X1;
  Dy = Y2 - Y1;

  if (Dx < 0)
    Dx = - Dx, sx = -1;
  else
    sx = 1;

  ND4_PutPixel(X1, Y1, Color);

  if (Dx >= Dy)
  {
    IncrNE = 2 * Dy - 2 * Dx;
    IncrE = 2 * Dy;
    F = 2 * Dy - Dx;
    Count = Dx;
   
    while (Count-- > 0)
    {
      if (F > 0)
        F += IncrNE, Y1++;
      else
        F += IncrE;
  
      X1 += sx;
      ND4_PutPixel(X1, Y1, Color);
    }
  }
  else
  {
    IncrNE = 2 * Dx - 2 * Dy;
    IncrE = 2 * Dx;
    F = 2 * Dx - Dy;
    Count = Dy;
   
    while (Count-- > 0)
    {
      if (F > 0)
        F += IncrNE, X1 += sx;
      else
        F += IncrE;
  
      Y1++;
      ND4_PutPixel(X1, Y1, Color);
    }
  }
} /* End of 'ND4_PutLine' function */

/* Drawing circle function */
VOID ND4_PutCirlce( INT Xc, INT Yc, INT R, DWORD Color )
{
  INT X = 0, Y = R, F = 1 - R, DeltaE = 3, DeltaSE = 5 - 2 * R;

  ND4_PutPixel(Xc, Yc + R, Color);
  ND4_PutPixel(Xc, Yc - R, Color);
  ND4_PutPixel(Xc + R, Yc, Color);
  ND4_PutPixel(Xc - R, Yc, Color);

  while (X <= Y)
  {
    if (F >= 0)
      Y--, F += DeltaSE, DeltaSE += 4;
    else
      F += DeltaE, DeltaSE += 2;
    DeltaE += 2;
    X++;
    if (X > Y)
      break;
    ND4_PutPixel(Xc + X, Yc + Y, Color);
    ND4_PutPixel(Xc - X, Yc + Y, Color);
    ND4_PutPixel(Xc + X, Yc - Y, Color);
    ND4_PutPixel(Xc - X, Yc - Y, Color);
    ND4_PutPixel(Xc + Y, Yc + X, Color);
    ND4_PutPixel(Xc - Y, Yc + X, Color);
    ND4_PutPixel(Xc + Y, Yc - X, Color);
    ND4_PutPixel(Xc - Y, Yc - X, Color);
  }
} /* End of 'ND4_PutCircle' function */

/* Drawing fill circle function */
VOID ND4_PutFillCircle( INT Xc, INT Yc, INT R, DWORD Color )
{
  INT X = 0, Y = R, F = 1 - R, DeltaE = 3, DeltaSE = 5 - 2 * R, i;

  while (X <= Y)
  {
    if (F >= 0)
    {
      ND4_PutLine(Xc - X, Yc - Y, Xc + X, Yc - Y, Color);
      ND4_PutLine(Xc - X, Yc + Y, Xc + X, Yc + Y, Color);

      ND4_PutLine(Xc - Y, Yc - X, Xc - Y, Yc + X, Color);
      ND4_PutLine(Xc + Y, Yc - X, Xc + Y, Yc + X, Color);
      Y--, F += DeltaSE, DeltaSE += 4;
    }
    else
      F += DeltaE, DeltaSE += 2;

    DeltaE += 2;
    X++;

    if (X > Y)
      break;

    ND4_PutPixel(Xc + X, Yc + Y, Color);
    ND4_PutPixel(Xc - X, Yc + Y, Color);
    ND4_PutPixel(Xc + X, Yc - Y, Color);
    ND4_PutPixel(Xc - X, Yc - Y, Color);
    ND4_PutPixel(Xc + Y, Yc + X, Color);
    ND4_PutPixel(Xc - Y, Yc + X, Color);
    ND4_PutPixel(Xc + Y, Yc - X, Color);
    ND4_PutPixel(Xc - Y, Yc - X, Color);
  }

  X--;
  for (i = 0; i < 2 * X + 1; i++)
    ND4_PutLine(Xc - X, Yc + Y, Xc + X, Yc + Y, Color), Y--;

} /* End of 'ND4_PutFillCircle' function */

/* Drawing rose fucntion */
VOID ND4_DrawRose( INT Xc, INT Yc, INT L, INT Sh, DWORD ColLight, DWORD ColDark )
{
  DOUBLE step = 1.0 / (L + 1), i;

  for (i = 0; i <= L; i += step)
  {
    ND4_PutLine(Xc, Yc + i, Xc + Sh, Yc + Sh, ColLight);
    ND4_PutLine(Xc, Yc - i, Xc - Sh, Yc - Sh, ColLight);
    ND4_PutLine(Xc + i, Yc, Xc + Sh, Yc - Sh, ColLight);
    ND4_PutLine(Xc - i, Yc, Xc - Sh, Yc + Sh, ColLight);

    ND4_PutLine(Xc, Yc + i, Xc - Sh, Yc + Sh, ColDark);
    ND4_PutLine(Xc, Yc - i, Xc + Sh, Yc - Sh, ColDark);
    ND4_PutLine(Xc + i, Yc, Xc + Sh, Yc + Sh, ColDark);
    ND4_PutLine(Xc - i, Yc, Xc - Sh, Yc - Sh, ColDark);
  }
} /* End of 'ND4_DrawRose' fucntion */

/* Drawing vroongel funtion */
VOID ND4_DrawVroo( INT Xc, INT Yc, INT L, INT L2, INT Sh, DWORD ColLight, DWORD ColDark)
{
  ND4_DrawRose(Xc, Yc, Sh * 2, -L2, ColLight, ColDark);
  ND4_DrawRose(Xc, Yc, L, Sh, ColLight, ColDark);
}
/* End of 'ND4_DrawVroo' function */

/* Drawing spin function */
VOID ND4_SpinDraw( INT X, INT Y, INT R, DWORD Color )
{
  DOUBLE i, nX = X + 0.5, nY = Y + 0.5;

  for (i = 0; i < R; i++)
  {
    nX = (nX - X) * cos(i) - (nY - Y) * sin(i);
    nY = (nX - X) * sin(i) + (nY - Y) * cos(i);
    
    ND4_PutLine(X + i, Y + i, nX + i, nY + i, Color);
  }
}
/* End of 'SpinDraw' function */
/* Drawing cursor dunction */
VOID ND4_CursorDraw( INT Xc, INT Yc, DWORD Color )
{
  ND4_PutCirlce(Xc, Yc, 10 / ND4_Zoom, Color);
  ND4_PutCirlce(Xc, Yc, 7 / ND4_Zoom, Color);
  ND4_PutCirlce(Xc, Yc, 4 / ND4_Zoom, Color);
} /* End of 'ND4_CursorDraw' function */
/* END OF 'GFX03.C' FILE */
