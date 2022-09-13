/* FILE NAME: RNDBASE.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 10.01.2020
 * PURPOSE: rendering system base function.
 */
#include <time.h>

#include "rnd.h"

/* Rendering init function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID ND4_RndInit( HWND hWnd )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* Store window and context */
  ND4_hRndWnd = hWnd;
  ND4_hRndDC = GetDC(hWnd);


  /* OpenGL initialization */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(ND4_hRndDC, &pfd);
  DescribePixelFormat(ND4_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(ND4_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  ND4_hRndGLRC = wglCreateContext(ND4_hRndDC);
  wglMakeCurrent(ND4_hRndDC, ND4_hRndGLRC);

  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(hWnd, "Error OpenGL initialization", "ERROR",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Render parameters setup */
  glClearColor(0.5, 0.5, 0.5, 1);
  glEnable(GL_DEPTH_TEST);

  ND4_RndFrameW = 30, 
  ND4_RndFrameH = 30;
  ND4_RndProjSize = 0.1, 
  ND4_RndProjDist = 0.1,
  ND4_RndProjFarClip = 300;
  ND4_RndMatrView = MatrIdentity();
  ND4_RndMatrProj = MatrIdentity();
  ND4_RndMatrVP = MatrIdentity();

  /* Shader initialization */
  ND4_RndProgId = ND4_RndShaderLoad("BIN/SHADERS/A");
} /* End of 'ND4_RndInit' function */

/* Rendering close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(ND4_hRndGLRC);
  ReleaseDC(ND4_hRndWnd, ND4_hRndDC);
} /* End of 'ND4_RndClose' function */

/* Start rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndStart( VOID )
{
  LONG t;
  static LONG save_t = -1;

  t = clock();
  if (t - save_t > 2 * CLOCKS_PER_SEC)
  {
    save_t = t;
    ND4_RndShaderFree(ND4_RndProgId);
    ND4_RndProgId = ND4_RndShaderLoad("BIN\\SHADERS\\A");
  }

  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'ND4_RndStart' function */

/* End rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndEnd( VOID )
{
  glFinish();
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
  glViewport(0, 0, W, H);
  ND4_RndFrameW = W;
  ND4_RndFrameH = H;
  ND4_RndProjSet();
} /* End of 'ND4_RndResize' function */

/* Copy frame buffer function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ND4_RndCopyFrame( VOID )
{
    SwapBuffers(ND4_hRndDC);
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