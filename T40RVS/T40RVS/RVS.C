/* FILE NAME: RVS.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 04.01.2020
 * PURPOSE: Work with desk.
 */
#include "rvs.h"

nd4STATE Desk[64];
INT ZoomX, ZoomY, WhiteCnt, BlackCnt;
nd4STATE ND4_Player = ND4_WHITE;

/* Desk initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_DeskInit( VOID )
{
  INT i;

  WhiteCnt = 2;
  BlackCnt = 2;

  for (i = 0; i < 64; i++)
    Desk[i] = ND4_FREE;

  Desk[27] = ND4_WHITE;
  Desk[28] = ND4_WHITE;
  Desk[35] = ND4_BLACK;
  Desk[36] = ND4_BLACK;

  ND4_Player = ND4_WHITE;

  ShowCursor(FALSE);
} /* End of 'ND4_DeskInit' function */

/* Draw desk on display function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ND4_DrawDesk( HDC hDC )
{
  INT y, x, shiftx = 0, shifty = 0;
  HBRUSH hBr, hOldBr;

  hBr = CreateSolidBrush(RGB(255, 255, 255));
  hOldBr = SelectObject(hDC, hBr);
  Rectangle(hDC, 0, 0, 8 * ZoomX, 8 * ZoomY);
  SelectObject(hDC, hOldBr);
  DeleteObject(hBr);
  for (y = 0; y < 8; y++)
  {
    shiftx = 0;
    for (x = 0; x < 8; x++)
    {
      shiftx = ZoomX * x;
      shifty = ZoomY * y;        
      
      hBr = CreateSolidBrush(RGB(0, 40, 0));
      hOldBr = SelectObject(hDC, hBr);
      Rectangle(hDC, x + shiftx + 1, y + shifty + 1, x + shiftx + ZoomX, y + shifty + ZoomY);
      SelectObject(hDC, hOldBr);
      DeleteObject(hBr);
      if (Desk[y * 8 + x] == ND4_WHITE)
      {
        hBr = CreateSolidBrush(RGB(255, 255, 255));
        hOldBr = SelectObject(hDC, hBr);
        Ellipse(hDC, x + shiftx + 1, y + shifty + 1, x + shiftx + ZoomX, y + shifty + ZoomY);
        SelectObject(hDC, hOldBr);
        DeleteObject(hBr);
      }
      else if (Desk[y * 8 + x] == ND4_BLACK)
      {
        hBr = CreateSolidBrush(RGB(255, 0, 0));
        hOldBr = SelectObject(hDC, hBr);
        Ellipse(hDC, x + shiftx + 1, y + shifty + 1, x + shiftx + ZoomX, y + shifty + ZoomY);
        SelectObject(hDC, hOldBr);
        DeleteObject(hBr);
      }
    }
  }
} /* End of 'ND4_DrawDesk' function */

/* Clear 'Step' struct function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_StepClear( VOID )
{
  Step.ND4_UP = 0;
  Step.ND4_DOWN = 0;
  Step.ND4_LEFT = 0;
  Step.ND4_RIGHT = 0;
  Step.ND4_RIGHTUP = 0;
  Step.ND4_RIGHTDOWN = 0;
  Step.ND4_LEFTUP = 0;
  Step.ND4_LEFTDOWN = 0;
} /* End of 'ND4_StepClear' function */

/* Draw line function.
 * ARGUMENTS:
 *   - Coordinates on desk:
 *       INT x, y;
 *   - Current player:
 *       nd4STATE State;
 * RETURNS: None.
 */
VOID ND4_ReDrawPlayer(INT x, INT y, nd4STATE State)
{
  INT mX = x, mY = y, points = 0;;

  while (Step.ND4_UP-- != 0)
  {
    mY--;
  
    Desk[mY * 8 + mX] = State;
    points++;
  }
  mY = y;

  while (Step.ND4_DOWN-- != 0)
  {
    mY++;
    Desk[mY * 8 + mX] = State;
    points++;
  }
  mY = y;

  while (Step.ND4_LEFT-- != 0)
  {
    mX--;
    Desk[mY * 8 + mX] = State;
    points++;
  }
  mX = x;

  while (Step.ND4_RIGHT-- != 0)
  {
    mX++;
    Desk[mY * 8 + mX] = State;
    points++;
  }
  mX = x;

  while (Step.ND4_RIGHTUP-- != 0)
  {
    mY--;
    mX++;
    Desk[mY * 8 + mX] = State;
    points++;
  }
  mY = y;
  mX = x;

  while (Step.ND4_RIGHTDOWN-- != 0)
  {
    mY++;
    mX++;
    Desk[mY * 8 + mX] = State;
    points++;
  }
  mY = y;
  mX = x;

  while (Step.ND4_LEFTUP-- != 0)
  {
    mY--;
    mX--;
    Desk[mY * 8 + mX] = State;
    points++;
  }
  mY = y;
  mX = x;

  while (Step.ND4_LEFTDOWN-- != 0)
  {
    mY++;
    mX--;
    Desk[mY * 8 + mX] = State;
    points++;
  }

  if (State == ND4_WHITE)
    WhiteCnt += points, BlackCnt -= points;
  else
    BlackCnt += points, WhiteCnt -= points;
} /* End of 'ND4_ReDrawPlayer' function */

/* Do one step follow the rules function.
 * ARGUMENTS:
 *   - Coordinates of click on desk:
 *       INT x, y;
 *   - Who is doing the step now:
 *       nd4STATE State;
 * RETURNS:
 *   (BOOL) Can put on {x, y} or not.
 */
BOOL ND4_DeskStep( INT x, INT y, nd4STATE State )
{
  if (Desk[y * 8 + x] != ND4_FREE)
    return FALSE;

  ND4_StepClear();

  Desk[y * 8 + x] = State;

  if (Desk[y * 8 + x - 8] == !Desk[y * 8 + x])
    ND4_LineCheckUp(x, y - 1);

  if (Desk[y * 8 + x + 8] == !Desk[y * 8 + x])
    ND4_LineCheckDown(x, y + 1);

  if (Desk[y * 8 + x - 1] == !Desk[y * 8 + x])
    ND4_LineCheckLeft(x - 1, y);

  if (Desk[y * 8 + x + 1] == !Desk[y * 8 + x])
    ND4_LineCheckRight(x + 1, y);

  if (Desk[y * 8 + x - 7] == !Desk[y * 8 + x])
    ND4_LineCheckRightUp(x + 1, y - 1);

  if (Desk[y * 8 + x + 9] == !Desk[y * 8 + x])
    ND4_LineCheckRightDown(x + 1, y + 1);

  if (Desk[y * 8 + x - 9] == !Desk[y * 8 + x])
    ND4_LineCheckLeftUp(x - 1, y - 1);

  if (Desk[y * 8 + x + 7] == !Desk[y * 8 + x])
    ND4_LineCheckLeftDown(x - 1, y + 1);

  if (Step.ND4_UP == 0 && Step.ND4_DOWN == 0 &&
    Step.ND4_LEFT == 0 && Step.ND4_RIGHT == 0 &&
    Step.ND4_RIGHTUP == 0 && Step.ND4_RIGHTDOWN == 0 &&
    Step.ND4_LEFTUP == 0 && Step.ND4_LEFTDOWN == 0)
  {
    Desk[y * 8 + x] = ND4_FREE;
    return FALSE;
  }

  ND4_ReDrawPlayer(x, y, State);

  return TRUE;
} /* End of 'ND4_DeskStep' function */

/* Do one step follow the rules function.
 * ARGUMENTS:
 *   - Coordinates of click on desk:
 *       INT x, y;
 *   - Who is doing the step now:
 *       nd4STATE State;
 * RETURNS:
 *   (INT) 0 if can't do the step, heavy of step if can.
 */
INT ND4_DeskStepCheck( INT x, INT y, nd4STATE State )
{
  INT heavy;

  if (Desk[y * 8 + x] != ND4_FREE)
    return 0;

  ND4_StepClear();

  Desk[y * 8 + x] = State;

  if (Desk[y * 8 + x - 8] == !Desk[y * 8 + x])
    ND4_LineCheckUp(x, y - 1);

  if (Desk[y * 8 + x + 8] == !Desk[y * 8 + x])
    ND4_LineCheckDown(x, y + 1);

  if (Desk[y * 8 + x - 1] == !Desk[y * 8 + x])
    ND4_LineCheckLeft(x - 1, y);

  if (Desk[y * 8 + x + 1] == !Desk[y * 8 + x])
    ND4_LineCheckRight(x + 1, y);

  if (Desk[y * 8 + x - 7] == !Desk[y * 8 + x])
    ND4_LineCheckRightUp(x + 1, y - 1);

  if (Desk[y * 8 + x + 9] == !Desk[y * 8 + x])
    ND4_LineCheckRightDown(x + 1, y + 1);

  if (Desk[y * 8 + x - 9] == !Desk[y * 8 + x])
    ND4_LineCheckLeftUp(x - 1, y - 1);

  if (Desk[y * 8 + x + 7] == !Desk[y * 8 + x])
    ND4_LineCheckLeftDown(x - 1, y + 1);

  if (Step.ND4_UP == 0 && Step.ND4_DOWN == 0 &&
    Step.ND4_LEFT == 0 && Step.ND4_RIGHT == 0 &&
    Step.ND4_RIGHTUP == 0 && Step.ND4_RIGHTDOWN == 0 &&
    Step.ND4_LEFTUP == 0 && Step.ND4_LEFTDOWN == 0)
  {
    Desk[y * 8 + x] = ND4_FREE;
    return 0;
  }

  heavy = Step.ND4_UP + Step.ND4_DOWN + Step.ND4_LEFT + Step.ND4_RIGHT + 
    Step.ND4_RIGHTUP + Step.ND4_RIGHTDOWN + Step.ND4_LEFTUP + Step.ND4_LEFTDOWN;

  Desk[y * 8 + x] = ND4_FREE;

  return heavy;    
} /* End of 'ND4_DeskStepCheck' function */

/* Virtual player function.
 * ARGUMENTS:
 *   - State:
 *       nd4STATE State;
 * RETURNS: None.
 */
VOID ND4_Bot( nd4STATE State )
{
  INT x, y, heavy, HeavyBestX = 0, HeavyBestY = 0, HeavyBestAm = 0;

  for (y = 0; y < 8; y++)
    for (x = 0; x < 8; x++)
      if ((heavy = ND4_DeskStepCheck(x, y, State)) > 0)
        if (heavy > HeavyBestAm)
        {
          HeavyBestAm = heavy;
          HeavyBestX = x;
          HeavyBestY = y;
        }
  ND4_DeskStep(HeavyBestX, HeavyBestY, State);
} /* End of 'ND4_Bot' function */

/* Check end-of-game function.
 * ARGUMENTS:
 *   - who doing the step:
 *       nd4STATE State;
 * RETURNS:
 *   (BOOL) is it end or not.
 */
BOOL EndGame( nd4STATE State )
{
  INT x, y;

  for (y = 0; y < 8; y++)
    for (x = 0; x < 8; x++)     
      if (ND4_DeskStepCheck(x, y, State))
        return FALSE;
  return TRUE;
} /* End of 'ND4_EndGame' function */

/* END OF 'RVS.C' FILE */