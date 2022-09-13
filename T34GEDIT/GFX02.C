/* Drekalov Nikita, 09-4, 16.12.2019 */
#include "gfx.h"

INT ND4_FontH, ND4_FontW, *ND4_Font, ND4_FontBPL;
/* Put character on display fucntion */
VOID ND4_PutChar( INT X, INT Y, CHAR Ch, DWORD Color )
{
  int i, j;
  
  for (i = 0; i < ND4_FontH; i++)
    for (j = 0; j < ND4_FontW; j++)
    {
      if ((ND4_Font[(BYTE)Ch * ND4_FontH * ND4_FontBPL + (j >> 3) + i * ND4_FontBPL] & (0x80 >> (j & 7))) != 0)
        ND4_PutPixel(X + j, Y + i, Color);
      else
        ND4_PutPixel(X + j, Y + i, ND4_RGB(0, 0, 0));
    }
} /* End of 'ND4_PutChar' fucntion */

/* Put string on display fucntion */
VOID ND4_PutStr( INT X, INT Y, CHAR *Str, DWORD Color )
{
  while (*Str != 0)
    ND4_PutChar(X, Y, *Str++, Color), X += ND4_FontW;
} /* End of 'ND4_PutStr' function */

/* END OF 'GFX02.C' FILE */