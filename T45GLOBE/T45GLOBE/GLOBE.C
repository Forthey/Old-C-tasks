/* FILE NAME: GLOBE.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 06.01.2020
 * PURPOSE: Draw.
 */
#include <time.h>

#include "globe.h"
#include "timer.h"

#define PI 3.14159265358979323846
#define GRIDS_H 35
#define GRIDS_W 35

VEC G[GRIDS_H][GRIDS_W];
MATR GLB_Matrix;
DBL GLB_Rx, GLB_Ry, GLB_Mx, GLB_My, GLB_Size;

DBL PowerTo( DBL X, DBL N )
{
  if (X < 0)
    return -pow(-X, N);
  return pow(X, N);
}

/* Initialize globe function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_GlobeInit( INT R )
{
  DBL x, y, z, theta, phi;
  INT i, j;

  for (theta = 0, i = 0; i < GRIDS_H; i++, theta += PI / (GRIDS_H - 1))
    for (phi = 0, j = 0; j < GRIDS_W; j++, phi += 2 * PI / (GRIDS_W - 1))
    {
      x = R * sin(theta) * sin(phi);
      y = R * cos(theta);
      z = R * sin(theta) * cos(phi);
      G[i][j] = VecSet(x, y, z);
    }
} /* End of 'ND4_Flobeinit' function */

/* Sphere draw function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 *   - coordinates of centre:
 *       INT Xc, Yc;
 *   - radius:
 *       INT R;
 * RETURNS: None.
 */
VOID ND4_DrawSphere( HDC hDC, INT Xc, INT Yc, INT Ws, INT Hs )
{                                                          
  INT i, j; 
  DBL Wp = 1.0, Hp = 1.0, ProjSet = 1;
  static POINT pts[GRIDS_H][GRIDS_W];

  GLB_TimerResponse();

  if (Ws > Hs)
    Wp = (DBL)Ws / Hs;
  else
    Hp = (DBL)Hs / Ws;

  GLB_Matrix = MatrMulMatr5(MatrRotateX(GLB_Rx), 
               MatrRotateY(GLB_Ry),
               MatrRotateZ(0),
               MatrView(VecSet(GLB_Mx, GLB_My, GLB_Size + 800), VecSet(0, 0, 0), VecSet(0, 1, 0)),
               MatrFrustum(-Wp / 2, Wp / 2, -Hp / 2, Hp / 2, ProjSet, 1000));

  for (i = 0; i < GRIDS_H; i++)
    for (j = 0; j < GRIDS_W; j++)
    {
      VEC P; 

      P = VecMulMatr(G[i][j], GLB_Matrix);

      pts[i][j].x = (P.X + 1) * Ws / 2;
      pts[i][j].y = (-P.Y + 1) * Hs / 2;
    }               

  for (i = 0; i < GRIDS_H; i++)
    for (j = 0; j < GRIDS_W; j++)
      SetPixel(hDC, pts[i][j].x, pts[i][j].y, RGB(155, 0, 255));

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(155, 0, 255));
  for (i = 0; i < GRIDS_H; i++)
  {
    MoveToEx(hDC, pts[i][0].x, pts[i][0].y, NULL);
    for (j = 1; j < GRIDS_W; j++)
      LineTo(hDC, pts[i][j].x, pts[i][j].y);
  }

  for (i = 0; i < GRIDS_W; i++)
  {
    MoveToEx(hDC, pts[0][i].x, pts[0][i].y, NULL);
    for (j = 1; j < GRIDS_H; j++)
      LineTo(hDC, pts[j][i].x, pts[j][i].y);
  }

  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(52, 0, 85));
  for (i = 0; i < GRIDS_H - 1; i++)
    for (j = 0; j < GRIDS_W - 1; j++)
    {
      POINT pts1[4];

      pts1[0] = pts[i][j];
      pts1[1] = pts[i][j + 1];
      pts1[2] = pts[i + 1][j + 1];
      pts1[3] = pts[i + 1][j];

      if ((pts1[0].x - pts1[1].x) * (pts1[0].y + pts1[1].y) +
        (pts1[1].x - pts1[2].x) * (pts1[1].y + pts1[2].y) +
        (pts1[2].x - pts1[3].x) * (pts1[2].y + pts1[3].y) +
        (pts1[3].x - pts1[0].x) * (pts1[3].y + pts1[0].y) <= 0)
        Polygon(hDC, pts1, 4);
    }

  SelectObject(hDC, GetStockObject(NULL_BRUSH));
  for (i = 0; i < GRIDS_H - 1; i++)
    for (j = 0; j < GRIDS_W - 1; j++)
    {
      POINT pts1[4];

      pts1[0] = pts[i][j];
      pts1[1] = pts[i][j + 1];
      pts1[2] = pts[i + 1][j + 1];
      pts1[3] = pts[i + 1][j];

      if ((pts1[0].x - pts1[1].x) * (pts1[0].y + pts1[1].y) +
        (pts1[1].x - pts1[2].x) * (pts1[1].y + pts1[2].y) +
        (pts1[2].x - pts1[3].x) * (pts1[2].y + pts1[3].y) +
        (pts1[3].x - pts1[0].x) * (pts1[3].y + pts1[0].y) > 0)
        Polygon(hDC, pts1, 4);
    }
} /* End of 'ND4_DrawSphere' function */
/* END OF 'GLOBE.C' FILE */