/* FILE NAME: RNDBASE.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: rendering system base function.
 */
#include "rnd.h"

/* Rendering init function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID ND4_RndInit( HWND hWnd )
{
  HDC hDC;

  ND4_RndFrameW = 30, 
  ND4_RndFrameH = 30;
  ND4_RndProjSize = 0.1, 
  ND4_RndProjDist = 0.1,
  ND4_RndProjFarClip = 300;
  ND4_hRndBmFrame = NULL;
  ND4_RndMatrView = MatrIdentity();
  ND4_RndMatrProj = MatrIdentity();
  ND4_RndMatrVP = MatrIdentity();

  ND4_hRndWnd = hWnd;
  hDC = GetDC(hWnd);
  ND4_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
} /* End of 'ND4_RndInit' function */

/* Rendering close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_RndClose( VOID )
{
  DeleteObject(ND4_hRndWnd);
  DeleteObject(ND4_hRndBmFrame);
  DeleteDC(ND4_hRndDCFrame);
} /* End of 'ND4_RndClose' function */

/* Start rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndStart( VOID )
{
  SelectObject(ND4_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(ND4_hRndDCFrame, RGB(0, 0, 0));
  Rectangle(ND4_hRndDCFrame, -1, -1, ND4_RndFrameW + 1, ND4_RndFrameH + 1);
  SelectObject(ND4_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCPenColor(ND4_hRndDCFrame, RGB(255, 255, 255));
} /* End of 'ND4_RndStart' function */

/* End rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndEnd( VOID )
{
} /* End of 'ND4_RndEnd' function */

/* Change matrix projection function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID ND4_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = ND4_RndProjSize;

  if (ND4_RndFrameW > ND4_RndFrameH)
    rx *= (DBL)ND4_RndFrameW / ND4_RndFrameH;
  else
    ry *= (DBL)ND4_RndFrameH / ND4_RndFrameW;

  ND4_RndMatrProj = 
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2, ND4_RndProjDist, ND4_RndProjFarClip);
} /* End of 'ND4_RndProjSet' function */

/* Rendering resize function.
 * ARGUMENTS: 
 *   - window width and height.
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID ND4_RndResize( INT W, INT H )
{
  BITMAPINFOHEADER bmih;

  if (ND4_hRndBmFrame != NULL)
    DeleteObject(ND4_hRndBmFrame);
  
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biPlanes = 1;
  bmih.biBitCount = 32;
  bmih.biCompression = BI_RGB;
  bmih.biWidth = W;
  bmih.biHeight = -H;
  bmih.biSizeImage = W * H * 4;

  ND4_hRndBmFrame = CreateDIBSection(NULL, (BITMAPINFO *)&bmih,
    DIB_RGB_COLORS, &ND4_RndFrameBits, NULL, 0);

  ND4_RndFrameW = W;
  ND4_RndFrameH = H;
  SelectObject(ND4_hRndDCFrame, ND4_hRndBmFrame);
  ND4_RndProjSet();
} /* End of 'ND4_RndResize' function */

/* Copy frame buffer function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ND4_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, ND4_RndFrameW, ND4_RndFrameH, ND4_hRndDCFrame, 0, 0, SRCCOPY);
} /* End of 'ND4_Rnd_CopyFrame' function */

/* Set camera function.
 * ARGUMENTS:
 *   - set camera position:
 *       VEC Loc, At, Up;
 * RETURNS: None.
 */
VOID ND4_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  ND4_RndMatrView = MatrView(Loc, At, Up);
  ND4_RndMatrVP = MatrMulMatr(ND4_RndMatrView, ND4_RndMatrProj);
} /* End of 'ND4_RndCamSet' function */

/* Put pixel function.
 * ARGUMENTS:
 *   - coordinates to put pixel:
 *       INT X, Y;
 *   - pixel color:
 *       DWORD Color;
 * RETURNS: None.
 */
VOID ND4_RndFramePutPixel( INT X, INT Y, DWORD Color )
{
  if (X < 0 || Y < 0 || X >= ND4_RndFrameW || Y >= ND4_RndFrameH)
    return;

  ND4_RndFrameBits[Y * ND4_RndFrameW + X] = Color;
} /* End of 'ND4_RndFramePutPixel' function */

/* Put line between to pixels function.
 * ARGUMENTS:
 *   - coordinates start and end:
 *       INT X1, Y1, X2, Y2;
 *   - line color;
 * RETURNS: None.
 */
VOID ND4_RndFramePutLine( INT X1, INT Y1, INT X2, INT Y2, DWORD Color)
{
  INT X, Y, IncrNE, IncrE, F, dx, dy, sx, count, tmp;

  if ((dy = Y2 - Y1) < 0)
    COM_SWAP(X1, X2, tmp), COM_SWAP(Y1, Y2, tmp), dy = -dy;

  if ((dx = X2 - X1) < 0)
    sx = -1, dx = -dx;
  else
    sx = 1;

  ND4_RndFramePutPixel(X = X1, Y = Y1, Color);

    if (dx >= dy)   
    {   
      F = dy * 2 - dx;    
      IncrE = dy * 2;   
      IncrNE = dy * 2 - dx * 2;  
      count = dx;     
      while (count-- > 0) 
      {       
        if (F > 0)   
          F += IncrNE, Y++;  
        else    
          F += IncrE; 
        X += sx;  
        ND4_RndFramePutPixel(X, Y, Color);  
      }   
    } 
    else 
    {  
      F = dx * 2 - dy;  
      IncrE = dx * 2; 
      IncrNE = dx * 2 - dy * 2;  
      count = dy;    
      while (count-- > 0)
      {     
        if (F > 0)  
          F += IncrNE, X += sx;   
        else    
          F += IncrE;   
        Y++;   
        ND4_RndFramePutPixel(X, Y, Color);  
      } 
    }
} /* End of 'ND4_RndFramePutLine' funcion */
/* END OF 'RNDBASE.C' FILE */