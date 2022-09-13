/* FILE NAME: GLOBE.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 06.01.2020
 * PURPOSE: header file.
 */

#ifndef __GLOBE_H_
#define __GLOBE_H_

#include <commondf.h>

#include "mth.h"


VOID ND4_DrawSphere( HDC hDC, INT Xc, INT Yc, INT W, INT H );
VOID ND4_GlobeInit( INT R );

extern MATR GLB_Matrix;
extern DBL GLB_Rx, GLB_Ry, GLB_Mx, GLB_My, GLB_Size;

#endif /* __GLOBE_H_ */
/* END OF 'GLOBE.H' FILE */