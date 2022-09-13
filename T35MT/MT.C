/* Drekalov Nikita, 09-4, 25.12.2019 */
#include <stdio.h>
#include <math.h>

#include "mt.h"

BYTE *Buf;

/* Decoding tst format function */
VOID ND4_TstDecoding( LONG BufSize, LONG W, LONG H, LONG N )
{
  LONG y, x, n = 0;

  /* for (n = 0; n < N; n++) */
    for (y = H * n + H; y >= 0; y--)
      for (x = W * n; x < W * n + W; x++)
        ND4_PutPixel(x, y, Buf[y * W + x]);
} /* End of 'TstDecoding' function */

VOID ND4_FileRead( CHAR *tstFileName )
{
  LONG i = 0, W = 0, H = 0, N = 0, ch, BufSize = 0, j;
  FILE *F;

  if ((F = fopen(tstFileName, "rb")) == NULL)
    return;

  for (i = 0; i < 4; i++)
    ch = fgetc(F);

  for (i = 6; i >= 0; i -= 2)
  {
    ch = fgetc(F);
    N += ch * pow(16, i);
  }

  for (i = 6; i >= 0; i -= 2)
  {
    ch = fgetc(F);
    W += ch * pow(16, i);
  }

  for (i = 6; i >= 0; i -= 2)
  {
    ch = fgetc(F);
    H += ch * pow(16, i);
  }

  Buf = malloc(W * H * N);

  for (j = 0; j < N; j++)
    for (i = W * H - 1; i >= 0; i--)
    {
      ch = fgetc(F);
  
      Buf[BufSize++] = ch;
    }
  ND4_TstDecoding(BufSize, W, H, N);
}
/* END OF 'MT.C' FILE */