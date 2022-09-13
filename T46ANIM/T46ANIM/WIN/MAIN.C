/* FILE NAME: MAIN.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: WinAPI windowed application sample.
 */
#include <time.h>

#include "../units.h"

#define WND_CLASS_NAME "Common class"

LRESULT CALLBACK ND4_WindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID FlipFullScreen( HWND hWnd );

/* Main startup program function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - previouse application instance handle
 *     (not used, always NULL):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - command line window show parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) system error level value.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;
  INT i;

  SetDbgMemHooks();

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = ND4_WindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  hWnd = CreateWindow(WND_CLASS_NAME, "Anim", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  for (i = 0; i < 30; i++)
    ND4_AnimUnitAdd(ND4_UnitCreateBall());
  ND4_AnimUnitAdd(ND4_UnitCreateCow());
  ND4_AnimUnitAdd(ND4_UnitCreateControl());
  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 0, 0);
  return msg.wParam;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message type (see WM_***):
 *       UINT Msg;
 *   - message 'word' parameter:
 *       WPARAM wParam;
 *   - message 'long' parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depended;
 */
LRESULT CALLBACK ND4_WindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static nd4PRIM Pr;

  switch (Msg)
  {
  case WM_CREATE:
    ND4_AnimInit(hWnd);
    SetTimer(hWnd, 0, 1, NULL);
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure to close the window?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    else
      return 0;
    return 0;
  case WM_KEYDOWN:
    if (wParam == 'F')
      ND4_AnimFlipFullScreen();
    return 0;
  case WM_MOUSEWHEEL:
    ND4_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_DESTROY:
    ND4_AnimClose();
    KillTimer(hWnd, 0);
    PostQuitMessage(0);
    return 0;
  case WM_GETMINMAXINFO:
    return 0;
  case WM_SIZE:
    ND4_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    ND4_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_TIMER:
    ND4_AnimRender();
    InvalidateRect(hWnd, 0, FALSE);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'ND4_WindowFunc' function */

/* END OF 'MAIN.C' FILE */