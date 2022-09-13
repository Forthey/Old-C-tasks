/* FILE NAME: RNDDATA.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: rendering system global data.
 */
#include "rnd.h"

/* Render window handle */
HWND ND4_hRndWnd;
/* Render device context handle */
HDC ND4_hRndDCFrame;
/* Render frame bitmap handle */
HBITMAP ND4_hRndBmFrame;
/* Render frame width and height */
INT ND4_RndFrameW, ND4_RndFrameH;
/* Projection parameters */
DBL 
 ND4_RndProjSize, 
 ND4_RndProjDist,
 ND4_RndProjFarClip;
MATR
 ND4_RndMatrView, /* View matrix */
 ND4_RndMatrProj, /* Projection matrix */
 ND4_RndMatrVP;   /* VP matrix */
/* Render frame */
DWORD *ND4_RndFrameBits;
/* END OF 'RNDDATA.C' FILE */