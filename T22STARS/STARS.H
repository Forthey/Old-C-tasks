/* Drekalov Nikita, 09-4, 01.11.2019 */
#include <commondf.h>

#define FRM_RGBA(R, G, B, A) \
  (((BYTE)(A) << 24) | \
   ((BYTE)(R) << 16) | \
   ((BYTE)(G) <<  8) | \
   (BYTE)(B))
#define FRM_RGB(R, G, B) FRM_RGBA(R, G, B, 0xFF)

typedef DOUBLE DBL;

typedef struct tagVEC
{
  DBL x, y, z;
} VEC;


VOID ProjSet( INT W, INT H );
VOID PutPixel( INT X, INT Y, DWORD Color );
VOID StarsInit( VOID );
VOID StarsMove( DBL DT );
VOID StarsDraw( VOID );
VOID SpeedChange( INT Amount );
VOID RotateAll( DBL Angle );
VOID PutStr( INT X, INT Y, CHAR *Str, DWORD Color );
VOID Turn( DBL SpeedT );
INT FontLoad( CHAR *FileName );
VOID DrawPCX( CHAR *FileName, INT X0, INT Y0 );