/* FILE NAME: ANIM.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 08.01.2020
 * PURPOSE: animation action file.
 */
/* END OF 'ANIM.C' FILE */
#include "anim.h"

/* Global animation context store data */
nd4ANIM ND4_Anim;

/* Animation initialization function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID ND4_AnimInit( HWND hWnd )
{
  ND4_RndInit(hWnd);

  ND4_TimerInit();

  /* Fill animation context */
  memset(&ND4_Anim, 0, sizeof(nd4ANIM));
  ND4_Anim.hWnd = hWnd;
  ND4_Anim.H = ND4_RndFrameW;
  ND4_Anim.H = ND4_RndFrameH;
} /* End of 'ND4_AnimInit' function */

/* Animation end function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < ND4_Anim.NumOfUnits; i++)
  {
    ND4_Anim.Units[i]->Close(ND4_Anim.Units[i], &ND4_Anim);
    free(ND4_Anim.Units[i]);
  }
  ND4_Anim.NumOfUnits = 0;
  ND4_RndClose();

  memset(&ND4_Anim, 0, sizeof(nd4ANIM));
} /* End of 'ND4_AnimClose' function */

/* Animation resize function.
 * ARGUMENTS:
 *   - Width and height:
 *       INT W, H;
 * RETURNS: None.
 */
VOID ND4_AnimResize( INT W, INT H )
{
  ND4_RndResize(W, H);
  ND4_Anim.W = W;
  ND4_Anim.H = H;
} /* End of 'ND4_AnimResize' function */

/* Animation copy frame function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ND4_AnimCopyFrame( VOID )
{
  ND4_RndCopyFrame();
} /* End of 'ND4_AnimCopyFrame' function */

/* Animation render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_AnimRender( VOID )
{
  INT i;

  ND4_TimerRespose();

  for (i = 0; i < ND4_Anim.NumOfUnits; i++)
    ND4_Anim.Units[i]->Response(ND4_Anim.Units[i], &ND4_Anim);
  ND4_RndStart();
  for (i = 0; i < ND4_Anim.NumOfUnits; i++)
    ND4_Anim.Units[i]->Render(ND4_Anim.Units[i], &ND4_Anim);
  ND4_RndEnd();
} /* End of 'ND4_AnimRender' function */

/* In/out fulscreen mode function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(ND4_Anim.hWnd, &SaveRC);

    hmon = MonitorFromWindow(ND4_Anim.hWnd, MONITOR_DEFAULTTONEAREST);
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(ND4_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(ND4_Anim.hWnd, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, 
      rc.bottom - rc.top + 30, SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(ND4_Anim.hWnd, HWND_TOP, SaveRC.left, SaveRC.top, SaveRC.right - SaveRC.left, 
      SaveRC.bottom - SaveRC.top, SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'ND4_AnimFlipFullScreen' function */

/* Animation add unit function.
 * ARGUMENTS:
 *   - unit pointer:
 *       nd4UNIT *Uni;
 * RETURNS: None.
 */
VOID ND4_AnimUnitAdd( nd4UNIT *Uni )
{
  if (ND4_Anim.NumOfUnits < ND4_MAX_UNITS)
    ND4_Anim.Units[ND4_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &ND4_Anim);
} /* End of 'ND4_AnimAddUnit' function */

/* Exit of animation function.
 * ARGUMENTS: None.
 * RETURS: None.
 */
VOID ND4_AnimDoExit( VOID )
{
  PostMessage(ND4_Anim.hWnd, WM_CLOSE, 0, 0);
} /* End of 'ND4_AnimDoExit' function */ 
/* END OF 'ANIM.C' FILE */