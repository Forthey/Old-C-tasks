/* FILE NAME: T45GLOBE.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 06.01.2020
 * PURPOSE: WinAPI windowed application sample.
 */
#include <stdio.h>

#include "globe.h"
#include "timer.h"

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

  hWnd = CreateWindow(WND_CLASS_NAME, "ND4", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
    {
      SendMessage(hWnd, WM_TIMER, 47, 0);
    }




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
  INT x, y, Key;
  CHAR Buf[20];
  PAINTSTRUCT ps;
  RECT rc;
  HFONT hFnt, hOldFnt;
  static INT W, H;
  static HDC hMemDC;
  static HBITMAP hBm;

  switch (Msg)
  {
  case WM_CREATE:
    GLB_TimerInit();
    ND4_GlobeInit(300);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 1, NULL);
    GLB_Matrix = MatrIdentity();
    return 0;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure to close the window?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    else
      return 0;
    return 0;
  case WM_MOUSEMOVE:
    x = LOWORD(lParam);
    y = HIWORD(lParam);
    return 0;
  case WM_KEYDOWN:
    Key = wParam;
    if (Key == 'F')
      FlipFullScreen(hWnd);
    if (Key == ' ')
      GLB_IsPause = !GLB_IsPause;
    if (Key == 'S')
      GLB_Rx -= 2;
    if (Key == 'W')
      GLB_Rx += 2;
    if (Key == 'A')
      GLB_Ry += 2;
    if (Key == 'D')
      GLB_Ry -= 2;
    if (Key == VK_DOWN)
      GLB_My += 6;
    if (Key == VK_UP)
      GLB_My -= 6;
    if (Key == VK_LEFT)
      GLB_Mx += 6;
    if (Key == VK_RIGHT)
      GLB_Mx -= 6;
    if (Key == 187 /* '+' */)
      GLB_Size -= 4;
    if (Key == 189 /* '+' */)
      GLB_Size += 4;
    return 0;
  case WM_KEYUP:
    GLB_Mx = GLB_My = GLB_Size = GLB_Rx = GLB_Ry = 0;
    return 0;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  case WM_SIZE:
    InvalidateRect(hWnd, NULL, FALSE);
    H = HIWORD(lParam);
    W = LOWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);

    SelectObject(hMemDC, hBm);

    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);    
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(0, 100, 100));
    Rectangle(hMemDC, 0, 0, W + 1, H + 1);
    ND4_DrawSphere(hMemDC, 800, 450, W, H);

     hFnt = CreateFont(20, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
      RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
      FIXED_PITCH | FF_ROMAN, "Bookman Old Style");
    hOldFnt = SelectObject(hMemDC, hFnt);

    rc.left = 10;
    rc.top = 10;
    rc.right = 270;
    rc.bottom = 270;
    SelectObject(hMemDC, GetStockObject(NULL_BRUSH));
    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    Rectangle(hMemDC, rc.left, rc.top, rc.right, rc.bottom);
    SetTextColor(hMemDC, RGB(155, 0, 255));
    SetBkMode(hMemDC, TRANSPARENT);
    DrawText(hMemDC, Buf, sprintf(Buf, "FPS: %.2f", GLB_FPS), &rc, 
      DT_VCENTER | DT_CENTER);

    SelectObject(hMemDC, hOldFnt);
    DeleteObject(hFnt);
    return 0;
  case WM_LBUTTONDOWN:
    x = LOWORD(lParam);
    y = HIWORD(lParam);

    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'ND4_WindowFunc' function */

/* In/out fulscreen mode function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &SaveRC);

    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, 
      rc.bottom - rc.top + 30, SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOP, SaveRC.left, SaveRC.top, SaveRC.right - SaveRC.left, 
      SaveRC.bottom - SaveRC.top, SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'FlipFullScreen' function */
/* END OF 'T45GLOBE.C' FILE */