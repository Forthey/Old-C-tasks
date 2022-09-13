/* FILE NAME: RND.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: rendering system depended.
 */
#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

extern HWND ND4_hRndWnd;
extern HDC ND4_hRndDCFrame;
extern HBITMAP ND4_hRndBmFrame;
extern INT 
         ND4_RndFrameW, 
         ND4_RndFrameH;
extern DBL 
         ND4_RndProjSize, 
         ND4_RndProjDist,
         ND4_RndProjFarClip;
extern MATR
         ND4_RndMatrView,
         ND4_RndMatrProj,
         ND4_RndMatrVP;
extern DWORD *ND4_RndFrameBits;
/* Rendering init function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID ND4_RndInit( HWND hWnd );
/* Rendering close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_RndClose( VOID );
/* Rendering resize function.
 * ARGUMENTS: 
 *   - window width and height.
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID ND4_RndResize( INT W, INT H );
/* Copy frame buffer function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ND4_RndCopyFrame( HDC hDC );
/* Set camera function.
 * ARGUMENTS:
 *   - set camera position:
 *       VEC Loc, At, Up;
 * RETURNS: None.
 */
VOID ND4_RndCamSet( VEC Loc, VEC At, VEC Up );
/* Start rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndStart( VOID );
/* End rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndEnd( VOID );

/*** Frame buffer acces & drawing functions ***/

/* Put pixel function.
 * ARGUMENTS:
 *   - coordinates to put pixel:
 *       INT X, Y;
 *   - pixel color:
 *       DWORD Color;
 * RETURNS: None.
 */
VOID ND4_RndFramePutPixel( INT X, INT Y, DWORD Color );

/* Put line between to pixels function.
 * ARGUMENTS:
 *   - coordinates start and end:
 *       INT X1, Y1, X2, Y2;
 *   - line color;
 * RETURNS: None.
 */
VOID ND4_RndFramePutLine( INT X1, INT Y1, INT X2, INT Y2, DWORD Color);
typedef struct tagnd4VERTEX
{
  VEC P;
} nd4VERTEX;

typedef struct tagnd4PRIM
{
  nd4VERTEX *V;
  INT 
    NumOfV, 
    *I,
    NumOfI;
  MATR Trans;
} nd4PRIM;

/* Create primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - number of vertex, index:
 *       INT NoofV, NoofI;
 */
BOOL ND4_RndPrimCreate( nd4PRIM *Pr, INT NoofV, INT NoofI );
/* Delete primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 * RETURNS: None.
 */
VOID ND4_RndPrimFree( nd4PRIM *Pr );
/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID ND4_RndPrimDraw( nd4PRIM *Pr, MATR World );
/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       vg4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ND4_RndPrimLoad( nd4PRIM *Pr, CHAR *FileName );

/* Create sphere function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS: None.
 */
BOOL ND4_RndPrimSphereCreate( nd4PRIM *Pr, DBL R, INT W, INT H );

#endif /* __RND_H_ */
/* END OF 'RND.H' FILE */