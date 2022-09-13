/* Drekalov Nikita, 09-4, 02.11.2019 */
#include <commondf.h>

#define MAX 500
#define FRM_RGBA(R, G, B, A) \
  (((BYTE)(A) << 24) | \
   ((BYTE)(R) << 16) | \
   ((BYTE)(G) <<  8) | \
   (BYTE)(B))
#define FRM_RGB(R, G, B) FRM_RGBA(R, G, B, 0xFF)
#define MAX_ENEMIES 2
#define INFINITY 400000

typedef DOUBLE DBL;

typedef struct
{
  INT X, Y;
} XYTYPE;

typedef struct
{
  INT X, Y;
  BYTE Solution[MAX][MAX];
  DBL DeltaTime;
} ENEMY;                  

extern XYTYPE Ava;
extern BYTE Lab[MAX][MAX];
extern ENEMY Enemy[MAX_ENEMIES];
extern XYTYPE SpawnPnt;
extern XYTYPE Exit;
extern INT LatenTime, NumOfEnemies;

VOID LoadLab( CHAR *FileName );
VOID PutPixel( INT X, INT Y, DWORD Color );
VOID DrawLab( VOID );
VOID LoadS( VOID );
VOID EnemyMove( VOID );
VOID DeathCheck( VOID );