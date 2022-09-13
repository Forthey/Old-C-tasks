/* Drekalov Nikita, 09-4, 16.12.2019 */
#ifndef _ND4_GFX_H_
#define _ND4_GFX_H_

#include <commondf.h>

#define ND4_RGBA(R, G, B, A) \
  (((BYTE)(A) << 24) | \
   ((BYTE)(R) << 16) | \
   ((BYTE)(G) <<  8) | \
   (BYTE)(B))
#define ND4_RGB(R, G, B) ND4_RGBA(R, G, B, 0xFF)

/* Checking what button was pressed */
typedef enum
{
  ND4_NOT_PRESS,
  ND4_LEFT,
  ND4_RIGHT
} nd4BUTTON;

/* Checking was pressed button ot not */
typedef enum
{
  ND4_ISNT_PRESS,
  ND4_UP,
  ND4_DOWN
} nd4PRESS;

/* Variable puting pixel */
typedef enum tagnd4LOGOP
{
  ND4_COPY,
  ND4_MUL,
  ND4_ADD,
  ND4_XOR
} nd4LOGOP;

VOID ND4_FrameInit( VOID );
VOID ND4_FrameDraw( VOID );
VOID ND4_FrameClear( DWORD Color );

VOID ND4_PutPixel( INT X, INT Y, DWORD Color );
DWORD ND4_GetPix( INT X, INT Y );

VOID ND4_PutLine( INT X1, INT Y1, INT X2, INT Y2, DWORD Color);
VOID ND4_PutCirlce( INT Xc, INT Yc, INT R, DWORD Color );
VOID ND4_PutFillCircle( INT Xc, INT Yc, INT R, DWORD Color );
VOID ND4_FloodFill( INT X, INT Y, DWORD Color );

VOID ND4_DrawRose( INT Xc, INT Yc, INT L, INT Sh, DWORD ColLight, DWORD ColDark );
VOID ND4_DrawVroo( INT Xc, INT Yc, INT L, INT L2, INT Sh, DWORD ColLight, DWORD ColDark);
VOID ND4_SpinDraw( INT X, INT Y, INT R, DWORD Color );

VOID ND4_CursorDraw( INT Xc, INT Yc, DWORD Color );

nd4LOGOP ND4_SetLogOp( nd4LOGOP LogOp );
extern DWORD *ND4_Frame;
extern INT ND4_FrameWidth, ND4_FrameHeight;
extern DOUBLE ND4_Zoom;

#endif
/* ENF OF 'GFX.H' FILE */