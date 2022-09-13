/* Drekalov Nikita, 09-4, 25.12.2019 */
#ifndef _ND4_GFX_H_
#define _ND4_GFX_H_

#include <commondf.h>

#define ND4_RGBA(R, G, B, A) \
  (((BYTE)(A) << 24) | \
   ((BYTE)(R) << 16) | \
   ((BYTE)(G) <<  8) | \
   (BYTE)(B))
#define ND4_RGB(R, G, B) ND4_RGBA(R, G, B, 0xFF)

VOID ND4_FileRead( CHAR *tstFileName );
VOID ND4_PutPixel( INT X, INT Y, DWORD Color );

extern BYTE Buf;
#endif
/* END OF 'MT.H' FILE */