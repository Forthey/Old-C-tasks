/* FILE NAME: LINECHECK.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 04.01.2020
 * PURPOSE: Check 8 lines for neighbours.
 */
#include "rvs.h"

nd4AVSTEPS Step;

/* Check the line up function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckUp( INT x, INT y )
{
  if (y < 1)
  {
    Step.ND4_UP = 0;
    return;
  }

  if (Desk[y * 8 + x - 8] == Desk[y * 8 + x])
  {
    Step.ND4_UP++;
    ND4_LineCheckUp(x, y - 1);
  }
  else if (Desk[y * 8 + x - 8] == !Desk[y * 8 + x])
  {
    Step.ND4_UP++;
    return;
  }
  else
    Step.ND4_UP = 0;
} /* End of 'ND4_LineCheckUp' function */

/* Check the line down function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckDown( INT x, INT y )
{
  if (y > 6)
  {
    Step.ND4_DOWN = 0; 
    return;
  }

  if (Desk[y * 8 + x + 8] == Desk[y * 8 + x])
  {
    Step.ND4_DOWN++;
    ND4_LineCheckDown(x, y + 1);
  }
  else if (Desk[y * 8 + x + 8] == !Desk[y * 8 + x])
  {
    Step.ND4_DOWN++;
    return;
  }
  else
    Step.ND4_DOWN = 0;
} /* End of 'ND4_LineCheckDown' function */

/* Check the line left function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckLeft( INT x, INT y )
{
  if (x < 1)
  {
    Step.ND4_LEFT = 0;
    return;
  }

  if (Desk[y * 8 + x - 1] == Desk[y * 8 + x])
  {
    Step.ND4_LEFT++;
    ND4_LineCheckLeft(x - 1, y);
  }
  else if (Desk[y * 8 + x - 1] == !Desk[y * 8 + x])
  {
    Step.ND4_LEFT++;
    return;
  }
  else
    Step.ND4_LEFT = 0;
} /* End of 'ND4_LineCheckLeft' function */

/* Check the line right function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckRight( INT x, INT y )
{
  if (x > 6)
  {
    Step.ND4_RIGHT = 0;
    return;
  }

  if (Desk[y * 8 + x + 1] == Desk[y * 8 + x])
  {
    Step.ND4_RIGHT++;
    ND4_LineCheckRight(x + 1, y);
  }
  else if (Desk[y * 8 + x + 1] == !Desk[y * 8 + x])
  {
    Step.ND4_RIGHT++;
    return;
  }
  else
    Step.ND4_RIGHT = 0;

} /* End of 'ND4_LineCheckRight' function */

/* Check the line right-up function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckRightUp( INT x, INT y )
{
  if (x > 6 || y < 1)
  {
    Step.ND4_RIGHTUP = 0;
    return;
  }

  if (Desk[y * 8 + x - 7] == Desk[y * 8 + x])
  {
    Step.ND4_RIGHTUP++;
    ND4_LineCheckRightUp(x + 1, y - 1);
  }
  else if (Desk[y * 8 + x - 7] == !Desk[y * 8 + x])
  {
    Step.ND4_RIGHTUP++;
    return;
  }
  else
    Step.ND4_RIGHTUP = 0;
} /* End of 'ND4_LineCheckRightUp' function */

/* Check the line right-down function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckRightDown( INT x, INT y )
{
  if (x > 6 || y > 6)
  {
    Step.ND4_RIGHTDOWN = 0;
    return;
  }

  if (Desk[y * 8 + x + 9] == Desk[y * 8 + x])
  {
    Step.ND4_RIGHTDOWN++;
    ND4_LineCheckRightDown(x + 1, y + 1);
  }
  else if (Desk[y * 8 + x + 9] == !Desk[y * 8 + x])
  { 
    Step.ND4_RIGHTDOWN++;
    return;
  }
  else
    Step.ND4_RIGHTDOWN = 0;
} /* End of 'ND4_LineCheckRightDown' function */

/* Check the line left-up function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckLeftUp( INT x, INT y )
{
  if (x < 1 || y < 1)
  {
    Step.ND4_LEFTUP = 0;
    return;
  }

  if (Desk[y * 8 + x - 9] == Desk[y * 8 + x])
  {
    Step.ND4_LEFTUP++;
    ND4_LineCheckLeftUp(x - 1, y - 1);
  }
  else if (Desk[y * 8 + x - 9] == !Desk[y * 8 + x])
  {
    Step.ND4_LEFTUP++;
    return;
  }
  else
    Step.ND4_LEFTUP = 0;
} /* End of 'ND4_LineCheckLeftUp' function */

/* Check the line left-down function.
 * ARGUMENTS:
 *   - coordinates on desk:
 *       INT x, y;
 * RETURNS: None.
 */
VOID ND4_LineCheckLeftDown( INT x, INT y )
{
  if (x < 1 || y > 6)
  {
    Step.ND4_LEFTDOWN = 0;
    return;
  }

  if (Desk[y * 8 + x + 7] == Desk[y * 8 + x])
  {
    Step.ND4_LEFTDOWN++;
    ND4_LineCheckLeftDown(x - 1, y + 1);
  }
  else if (Desk[y * 8 + x + 7] == !Desk[y * 8 + x])
  {
    Step.ND4_LEFTDOWN++;
    return;
  }
  else
    Step.ND4_LEFTDOWN = 0;
} /* End of 'ND4_LineCheckLeftDown' function */

/* END OF 'LINECHECK.C' FILE */