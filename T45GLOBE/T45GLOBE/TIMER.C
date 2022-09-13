/* FILE NAME  : TIMER.C
 * PROGRAMMER : ND4
 * LAST UPDATE: 06.01.2020
 * PURPOSE    : Timer implementation module.
 */

#include <time.h>

#include "timer.h"

/* Timer global data */
DOUBLE
  GLB_Time,      /* Total time in seconds */
  GLB_DeltaTime, /* Interframe time in seconds */
  GLB_FPS;       /* Frames per second value */
BOOL
  GLB_IsPause;   /* Pause flag */

/* Timer local data */
static LONG
  StartTime,  /* Program start time in ticks */
  OldTime,    /* Previous frame time in ticks */
  PauseTime,  /* Pause delay time in ticks */
  OldFPSTime, /* Old FPS measure tim in ticks */
  FrameCount; /* Frame counter (for FPS evaluation) */

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID GLB_TimerInit( VOID )
{
  StartTime = OldTime = OldFPSTime = clock();
  PauseTime = 0;
  FrameCount = 0;
  GLB_IsPause = FALSE;
} /* End of 'GLB_TimerInit' function */

/* Timer interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID GLB_TimerResponse( VOID )
{
  LONG t = clock();

  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GLB_DeltaTime = 0;
  }

  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    GLB_FPS = FrameCount / ((DOUBLE)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t;
} /* End of 'GLB_TimerResponse' function */

/* END OF 'TIMER.C' FILE */
