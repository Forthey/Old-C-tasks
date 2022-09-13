/* FILE NAME: TIMER.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 09.01.2020
 * PURPOSE: Timer handle data.
 */
#include "anim.h"

static UINT64 
         StartTime,    /* Start program time */
         OldTime,      /* Previous frame time */
         OldTimeFPS,   /* Old time FPS measurement */
         PauseTime,    /* Time during pause period */
         TimePerSec,   /* Timer resolution */
         FrameCounter; /* Frames counter */

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  ND4_Anim.IsPause = FALSE;
  ND4_Anim.FPS = 30.0;
  PauseTime = 0;
} /* End of 'ND4_TimerInit' function */

/* Timer response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_TimerRespose( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  ND4_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  ND4_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (ND4_Anim.IsPause)
  {
    ND4_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    ND4_Anim.DeltaTime = ND4_Anim.GlobalDeltaTime;
    ND4_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    ND4_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /* End of 'ND4_TimerRespose' function */
/* END OF 'TIMER.C' FILE */