/* FILE NAME: T41EYES.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 05.01.2020
 * PURPOSE: WinAPI windowed application sample.
 */
#include <commondf.h>
#include <math.h>

#define WND_CLASS_NAME "Common class"

LRESULT CALLBACK ND4_WindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID FlipFullScreen( HWND hWnd );
VOID ND4_DrawEye( HDC hDC, INT X, INT Y, INT Xe, INT Ye, INT R1, INT R2 );
VOID ND4_DrawPolygon( HDC hDC, INT X, INT Y, INT Sx, INT Sy );

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
  INT x, y, Key, i;
  PAINTSTRUCT ps;
  POINT Mouse;
  HBRUSH hBr, hOldBr;
  static INT W, H, Do = 0;
  static HDC hMemDC;
  static HBITMAP hBm;
  static POINTS Eyes[300];

  for (i = 0; i < 300 && Do == 0; i++)
  {
    Eyes[i].x = rand() % 1880;
    Eyes[i].y = rand() % 1000;
  }

  Do = 1;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);

    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 1, NULL);
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
    if (Key == 70)
      FlipFullScreen(hWnd);
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

    GetCursorPos(&Mouse);
    ScreenToClient(hWnd, &Mouse);
    hBr = CreateSolidBrush(RGB(150, 150, 150));
    hOldBr = SelectObject(hMemDC, hBr); 
    Rectangle(hMemDC, 0, 0, W, H);
    SelectObject(hMemDC, hOldBr);
    DeleteObject(hBr);

    for (i = 0; i < 300; i++)
      ND4_DrawEye(hMemDC, Mouse.x, Mouse.y, Eyes[i].x, Eyes[i].y, 40, 20);

    ND4_DrawPolygon(hMemDC, Mouse.x, Mouse.y, 200, 100);
    ND4_DrawPolygon(hMemDC, Mouse.x, Mouse.y, -200, 100);
    ND4_DrawPolygon(hMemDC, Mouse.x, Mouse.y, 100, 200);
    ND4_DrawPolygon(hMemDC, Mouse.x, Mouse.y, 100, 400);
    return 0;
  case WM_LBUTTONDOWN:
    x = LOWORD(lParam);
    y = HIWORD(lParam);

    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'ND4_WindowFunc' function */

VOID ND4_DrawEye( HDC hDC, INT X, INT Y, INT Xe, INT Ye, INT R1, INT R2 )
{
  HBRUSH hBr, hOldBr;
  INT EyeX, EyeY;
  DOUBLE k;

  hBr = CreateSolidBrush(RGB(255, 255, 255));
  hOldBr = SelectObject(hDC, hBr); 
  Ellipse(hDC, Xe - R1 - R2, Ye + R1 + R2, Xe + R1 + R2, Ye - R1 - R2);
  SelectObject(hDC, hOldBr);
  DeleteObject(hBr);

  k = R1 / sqrt(X * X - 2 * X * Xe + Xe * Xe + Y * Y - 2 * Y * Ye + Ye * Ye);


  if (k <= 1)
  {
    EyeX = Xe + (X - Xe) * k;
    EyeY = Ye + (Y - Ye) * k;

    hBr = CreateSolidBrush(RGB(0, 0, 0));
    hOldBr = SelectObject(hDC, hBr); 
    Ellipse(hDC, EyeX - R2, EyeY - R2, EyeX + R2, EyeY + R2);
    SelectObject(hDC, hOldBr);
    DeleteObject(hBr);
  }
  else
  {
    hBr = CreateSolidBrush(RGB(0, 0, 0));
    hOldBr = SelectObject(hDC, hBr); 
    Ellipse(hDC, X - R2, Y - R2, X + R2, Y + R2);
    SelectObject(hDC, hOldBr);
    DeleteObject(hBr);
  }
}

/* Drawing polygon function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 *   - mouse coordinates:
 *       INT X, Y;
 *   - shift relative to the {600, 300}:
 *       INT Sx, Sy;
 * RETURNS: None.
 */
VOID ND4_DrawPolygon( HDC hDC, INT X, INT Y, INT Sx, INT Sy )
{
  HBRUSH hBr, hOldBr;
  DOUBLE k, sine, cosine, alpha;
  INT dx = 600 + Sx - X, dy = 200 + Sy - Y, i, Xc, Yc;
  POINT pnts[3] =
  {
    {600 + Sx, 300 + Sy}, {600 + Sx, 100 + Sy}, {500 + Sx, 200 + Sy}
  }, pnts1[3];

  
  Xc = (pnts[0].x + pnts[1].x + pnts[2].x) / 3;
  Yc = (pnts[0].y + pnts[1].y + pnts[2].y) / 3;

  k = sqrt(dx * dx + dy * dy);
  sine = dy / k;
  cosine = dx / k;

  alpha = atan2(sine, cosine);

  for (i = 0; i < 3; i++)
  {
    pnts1[i].x = Xc + (pnts[i].x - Xc) * cos(alpha) - (pnts[i].y - Yc) * sin(alpha);
    pnts1[i].y = Yc + (pnts[i].x - Xc) * sin(alpha) + (pnts[i].y - Yc) * cos(alpha);
  }
  hBr = CreateSolidBrush(RGB(170, 90, 170));
  hOldBr = SelectObject(hDC, hBr); 
  Polygon(hDC, pnts1, 3);
  SelectObject(hDC, hOldBr);
  DeleteObject(hBr);
}


VOID DrawArrow( HDC hDC, POINT *ms, INT Xc, INT Yc, INT L, INT W, INT S )
{

}
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
/* END OF 'T41EYES.C' FILE */