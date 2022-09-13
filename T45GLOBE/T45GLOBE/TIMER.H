/* FILE NAME  : TIMER.H
 * PROGRAMMER : ND
 * LAST UPDATE: 06.01.2020
 * PURPOSE    : Timer declaration module.
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include <commondf.h>

/* Timer global data */
extern DOUBLE
  GLB_Time,      /* Total time in seconds */
  GLB_DeltaTime, /* Interframe time in seconds */
  GLB_FPS;       /* Frames per second value */
extern BOOL
  GLB_IsPause;   /* Pause flag */

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID GLB_TimerInit( VOID );

/* Timer interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID GLB_TimerResponse( VOID );

#endif /* __TIMER_H_ */

/* END OF 'TIMER.H' FILE */
