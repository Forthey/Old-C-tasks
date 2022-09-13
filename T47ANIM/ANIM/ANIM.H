/* FILE NAME: ANIM.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 08.01.2020
 * PURPOSE: Animation system main declaration module.
 */
/* END OF 'ANIM.H' FILE */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "../def.h"
#include "rnd/rnd.h"

/***
 * Main animation support
 ***/

/* Types forward declarations */
typedef struct tagnd4UNIT nd4UNIT;
typedef struct tagnd4ANIM nd4ANIM;

/* Maximum animation units count */
#define ND4_MAX_UNITS 100

/* Animation context representation type */
struct tagnd4ANIM
{
  HWND hWnd;                     /* Work window handle */
  INT W, H;                      /* Back buffer size */
  /* Units array data */
  nd4UNIT *Units[ND4_MAX_UNITS]; /* Animation units array */
  INT NumOfUnits;                /* Animation units array size */
  /* Timer handle data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */
  /* Keyboard handle data */
  BYTE
    Keys[256],                   /* Keyboard state (true if key pressed) */
    KeysOld[256],                /* Previous frame keyboard state */
    KeysClick[256];              /* Key 'one-click' info */
  /* Mouse handle data */
  INT
    Mx, My, Mz,                  /* Absolute mouse coordinates */
    Mdx, Mdy, Mdz;               /* Relative mouse coordinates */
  /* Joystick handle data */
  BYTE
    JBut[32],                    /* Joystick button states */
    JButOld[32],                
    JButClick[32];
  INT JPov;                      /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;              /* Joystick axes */
  VEC Cam;
};

/* Base unit fields macro */
#define ND4_UNIT_BASE_FIELDS \
  VOID (*Init)( nd4UNIT *Uni, nd4ANIM *Ani );      \
  VOID (*Close)( nd4UNIT *Uni, nd4ANIM *Ani );     \
  VOID (*Response)( nd4UNIT *Uni, nd4ANIM *Ani );  \
  VOID (*Render)( nd4UNIT *Uni, nd4ANIM *Ani )

/* Base unit field macro type */
struct tagnd4UNIT
{
  ND4_UNIT_BASE_FIELDS;
};

/* Global animation context store data */
extern nd4ANIM ND4_Anim;

/* Animation initialization function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID ND4_AnimInit( HWND hWnd );

/* Animation end function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_AnimClose( VOID );

/* Animation resize function.
 * ARGUMENTS:
 *   - Width and height:
 *       INT W, H;
 * RETURNS: None.
 */
VOID ND4_AnimResize( INT W, INT H );

/* Animation copy frame function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ND4_AnimCopyFrame( VOID );

/* Animation render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_AnimRender( VOID );

/* In/out fulscreen mode function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_AnimFlipFullScreen( VOID );

/* Animation add unit function.
 * ARGUMENTS:
 *   - unit pointer:
 *       nd4UNIT *Uni;
 * RETURNS: None.
 */
VOID ND4_AnimUnitAdd( nd4UNIT *Uni );

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ND4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_AnimUnitCreate( INT Size );

/* Exit of animation function.
 * ARGUMENTS: None.
 * RETURS: None.
 */
VOID ND4_AnimDoExit( VOID );

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_TimerInit( VOID );

/* Timer response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_TimerRespose( VOID );

#endif /* __ANIM_H_ */
/* END OF 'ANIM.H' FILE */