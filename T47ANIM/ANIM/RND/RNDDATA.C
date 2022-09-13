/* FILE NAME: RNDDATA.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 10.01.2020
 * PURPOSE: rendering system global data.
 */
#include "rnd.h"

HWND ND4_hRndWnd;                 /* Render window handle */
HDC ND4_hRndDC;              /* Render device context handle */
INT ND4_RndFrameW, ND4_RndFrameH; /* Render frame width and height */
HGLRC ND4_hRndGLRC;               /* OpenGL rendering context */
FLT 
 ND4_RndProjSize,                 /* Projection size */
 ND4_RndProjDist,                 /* Projection distance */
 ND4_RndProjFarClip;              /* Projection far clip */
MATR
 ND4_RndMatrView,                 /* View matrix */
 ND4_RndMatrProj,                 /* Projection matrix */ 
 ND4_RndMatrVP; 
UINT ND4_RndProgId;
/* VP matrix */

/* END OF 'RNDDATA.C' FILE */