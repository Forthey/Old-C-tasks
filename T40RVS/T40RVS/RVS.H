/* FILE NAME: RVS.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 04.01.2020
 * PURPOSE: Compile another files.
 */
#include <commondf.h>

typedef enum
{
  ND4_WHITE,
  ND4_BLACK,
  ND4_FREE
} nd4STATE;

typedef struct
{
  INT ND4_UP, ND4_DOWN, ND4_LEFT, ND4_RIGHT,
    ND4_RIGHTUP, ND4_RIGHTDOWN, ND4_LEFTUP, ND4_LEFTDOWN;
} nd4AVSTEPS;

extern nd4STATE Desk[64], ND4_Player;
extern INT ZoomX, ZoomY, WhiteCnt, BlackCnt;
extern nd4AVSTEPS Step;

VOID ND4_DeskInit( VOID );
VOID ND4_DrawDesk( HDC hDC );
INT ND4_DeskStep( INT x, INT y, nd4STATE State );
BOOL EndGame( nd4STATE State );

VOID ND4_LineCheckUp( INT x, INT y );
VOID ND4_LineCheckDown( INT x, INT y );
VOID ND4_LineCheckLeft( INT x, INT y );
VOID ND4_LineCheckRight( INT x, INT y );
VOID ND4_LineCheckRightUp( INT x, INT y );
VOID ND4_LineCheckRightDown( INT x, INT y );
VOID ND4_LineCheckLeftUp( INT x, INT y );
VOID ND4_LineCheckLeftDown( INT x, INT y );

VOID ND4_Bot( nd4STATE State );