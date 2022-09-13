/* Drekalov Nikita, 09-4, 16.12.2019 */
#include "gfx.h"

/* Saving what logic operand need to use */
static nd4LOGOP ND4_LogOp = ND4_COPY;

/** Low level funcitons **/

/* Copy Color funtion */
VOID ND4_LowPutPixel_COPY( INT X, INT Y, DWORD Color )
{
  ND4_Frame[Y * ND4_FrameWidth + X] = Color;
} /* End of 'ND4_LowPutPixel_COPY' function */

/* Ans Color funtion */
VOID ND4_LowPutPixel_MUL( INT X, INT Y, DWORD Color )
{
  ND4_Frame[Y * ND4_FrameWidth + X] &= Color;
} /* End of 'ND4_LowPutPixel_MUL' function */

/* Add Color funtion */
VOID ND4_LowPutPixel_ADD( INT X, INT Y, DWORD Color )
{
  ND4_Frame[Y * ND4_FrameWidth + X] |= Color;
} /* End of 'ND4_LowPutPixel_ADD' function */

/* XOR Color funtion */
VOID ND4_LowPutPixel_XOR( INT X, INT Y, DWORD Color )
{
  ND4_Frame[Y * ND4_FrameWidth + X] ^= Color;
} /* End of 'ND4_LowPutPixel_XOR' function */

/* Massive of pointers */
VOID (*ND4_PutPixelFuncs[])(INT X, INT Y, DWORD Color) = 
{
  ND4_LowPutPixel_COPY,
  ND4_LowPutPixel_MUL,
  ND4_LowPutPixel_ADD,
  ND4_LowPutPixel_XOR
};

nd4LOGOP ND4_SetLogOp( nd4LOGOP LogOp )
{
  nd4LOGOP Old = ND4_LogOp;

  ND4_LogOp = LogOp;
  return Old;
}

/* Set pixel on display */
VOID ND4_PutPixel( INT X, INT Y, DWORD Color )
{
  if (X < 0 || Y < 0 || X >= ND4_FrameWidth || Y >= ND4_FrameHeight)
    return;

  ND4_PutPixelFuncs[ND4_LogOp](X, Y, Color);
} /* End of 'ND4_PutPixel' function */

/* Get the pixel colour fucntion */
DWORD ND4_GetPix( INT X, INT Y )
{
  if (X < 0 || Y < 0 || X >= ND4_FrameWidth || Y >= ND4_FrameHeight)
    return 0;

  return ND4_Frame[Y * ND4_FrameWidth + X];
} /* End of 'ND4_GetPix' fucntion */
/* END OF 'GFX01.C' FILE */

