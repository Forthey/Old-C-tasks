/* Drekalov Nikita, 09-4, 31.10.2019 */

#include <stdio.h>
#pragma pack(push, 1)
#include <pcxhead.h>
#pragma pack(pop)
#include "pcx.h"


/* Decoding PCX function */
VOID DrawPCX( CHAR *FileName, INT X0, INT Y0 )
{
  FILE *F;
  pcxFILEHEAD Head;
  BYTE Pal[256][3], b;
  int i, x, y, w, h;

  /* Open file */
  if ((F = fopen(FileName, "rb")) == NULL)
    return;
  
  /* Read image header */
  if (fread(&Head, sizeof(pcxFILEHEAD), 1, F) != 1 ||
    Head.Manuf != 0x0A ||
    Head.Encode != 1 ||
    Head.PaletteInfo != 1 ||
    Head.PlanesAmount != 1 ||
    Head.BitsPerPixel != 8)
  {
    fclose(F);
    return;
  }

  fseek(F, -769, SEEK_END);
  b = fgetc(F);
  fread(&Pal, 3, 256, F);

  /* Correct palette entries from 0...63 to 0...255 */
  if (b == 0x0A)
    for (i = 0; i < 256; i++)
      for (b = 0; b < 3; b++)
        Pal[i][b] = Pal[i][b] * 255 / 63;

  fseek(F, 128, SEEK_SET);

  /* Decode image pixels */
  x = 0;
  y = 0;
  w = Head.X2 - Head.X1 + 1;
  h = Head.Y2 - Head.Y1 + 1;

  while (y < h)
  {
    /* Decode RLE */
    b = fgetc(F);

    if ((b >> 6) == 3)
      i = b & 0x3F, b = fgetc(F);
    else
      i = 1;

    /* Output bytes */
    while (i-- > 0)
    {
      if (x < w)
        PutPixel(X0 + x, Y0 + y, Pal[b][0], Pal[b][1], Pal[b][2]);
      if (++x >= Head.BytesPerLine)
        x = 0, y++;
    }
  }
  fclose(F);
} /* End of 'DrawPCX' function */