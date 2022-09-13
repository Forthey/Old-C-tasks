/* FILE NAME: T40RVS.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 03.01.2020
 * PURPOSE: WinAPI windowed application sample.
 */
#include "rvs.h"

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

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
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
  HFONT hFnt, hOldFnt;
  RECT rc;
  PAINTSTRUCT ps;
  CHAR Buf[100];
  POINT pt;
  static INT W, H;
  static HDC hMemDC, hMemDCAnd, hMemDCXor;
  static HBITMAP hBm, hBmAnd, hBmXor;
  static BITMAP bm_logo;


  wsprintf(Buf, "1st: %d\n2nd: %d", WhiteCnt, BlackCnt);

  switch (Msg)
  {
  case WM_CREATE:
    ND4_DeskInit();
    hBmAnd = LoadImage(NULL, "Hand.bmp", IMAGE_BITMAP, 0, 0,
      LR_LOADFROMFILE);
    hBmXor = LoadImage(NULL, "Handxr.bmp", IMAGE_BITMAP, 0, 0,
      LR_LOADFROMFILE);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCAnd = CreateCompatibleDC(hDC);
    hMemDCXor = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    SelectObject(hMemDCAnd, hBmAnd);
    SelectObject(hMemDCXor, hBmXor);
    GetObject(hBmXor, sizeof(bm_logo), &bm_logo);

    SetTimer(hWnd, 30, 1, NULL);
    break;
  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure to close the window?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
      DestroyWindow(hWnd);
    else
      return 0;
    break;
  case WM_KEYDOWN:
    Key = wParam;
    if (Key == 70)
      FlipFullScreen(hWnd);
    break;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    break;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);

    SelectObject(hMemDC, hBm);

    ZoomY = H / 8;
    ZoomX = W / 8;

    hFnt = CreateFont((W > H ? H / 8 : W / 8) / 2, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
      RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
      FIXED_PITCH | FF_ROMAN, "Bookman Old Style");
    hOldFnt = SelectObject(hMemDC, hFnt);

    rc.left = 10;
    rc.top = 8 * ZoomY;
    rc.right = 30 + ZoomX;
    rc.bottom = rc.top + ZoomY;
    SelectObject(hMemDC, GetStockObject(NULL_BRUSH));
    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    Rectangle(hMemDC, rc.left, rc.top, rc.right, rc.bottom);
    SetTextColor(hMemDC, RGB(155, 0, 255));
    SetBkMode(hMemDC, TRANSPARENT);
    DrawText(hMemDC, Buf, strlen(Buf), &rc, 
      DT_VCENTER | DT_CENTER);

    SelectObject(hMemDC, hOldFnt);
    DeleteObject(hFnt);

    InvalidateRect(hWnd, NULL, FALSE);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    break;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    break;
  case WM_ERASEBKGND:
    break;
  case WM_TIMER:
    ND4_DrawDesk(hMemDC);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    BitBlt(hMemDC,
      pt.x - bm_logo.bmWidth / 2, pt.y - bm_logo.bmHeight / 2,
      bm_logo.bmWidth, bm_logo.bmHeight,
      hMemDCAnd, 0, 0, SRCAND);
    BitBlt(hMemDC,
      pt.x - bm_logo.bmWidth / 2, pt.y - bm_logo.bmHeight / 2,
      bm_logo.bmWidth, bm_logo.bmHeight,
      hMemDCXor, 0, 0, SRCINVERT);

    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_LBUTTONDOWN:
    x = LOWORD(lParam);
    y = HIWORD(lParam);

    if (x >= 8 * ZoomX || y >= 8 * ZoomY || y == 0 || x == 0)
      break;

    if (EndGame(ND4_Player))
    {
      ShowCursor(TRUE);

      if (WhiteCnt > BlackCnt)
      {
        if (MessageBox(hWnd, "White won\nRetry?", "Winner", MB_RETRYCANCEL) == IDCANCEL)
          DestroyWindow(hWnd);
        else
          ND4_DeskInit();
      }
      else if (WhiteCnt < BlackCnt)
      {
        if (MessageBox(hWnd, "Red won", "Winner", MB_RETRYCANCEL) == IDCANCEL)
          DestroyWindow(hWnd);
        else
          ND4_DeskInit();
      }
      else if (MessageBox(hWnd, "Nichya", "Nichya", MB_RETRYCANCEL) == IDCANCEL)
        DestroyWindow(hWnd);
      else
        ND4_DeskInit();

      return 0;
    }
    x = x / ZoomX;
    y = y / ZoomY;
    if (ND4_Player == ND4_WHITE && ND4_DeskStep(x, y, ND4_Player))
    {
      WhiteCnt++;
      ND4_Player = !ND4_Player;
    }
    else if (ND4_Player == ND4_BLACK)
    {
      ND4_Bot(ND4_BLACK);
      BlackCnt++;
      ND4_Player = !ND4_Player;
    }
    InvalidateRect(hWnd, NULL, FALSE);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    break;
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

    SetWindowPos(hWnd, HWND_TOPMOST, rc.left, rc.top, rc.right - rc.left, 
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
/* END OF 'T40RVS.C' FILE */