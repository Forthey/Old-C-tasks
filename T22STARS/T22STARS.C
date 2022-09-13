/* Drekalov Nikita, 09.4, 31.10.2019 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <glut.h>

#include <windows.h>

#include "stars.h"

/*
*** Graphic interface
*/

/* defines for array 'Frame' */
#define ZOOM 1

/* Create array for display */
DWORD *FRM_Frame = NULL;

INT FRM_Width = 0, FRM_Height = 0;

DOUBLE SyncTime, DeltaTime, FPS;
BOOL IsPause = 0;
SYSTEMTIME tim;

/* Set time settings */
VOID Timer( VOID )
{
  LONG t;
  static LONG StartTime = -1, FPSTime, FrameCount, PauseTime, OldTime;
 
  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = OldTime = t;
  if (!IsPause)
  {
    SyncTime = (t - StartTime - PauseTime) / (DOUBLE)CLOCKS_PER_SEC;
    DeltaTime = (t - OldTime) / (DOUBLE)CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    DeltaTime = 0;
  }
  OldTime = t;
  FrameCount++;
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (DOUBLE)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
  }
}

/* Set FPS and Syncronize time */

/* Set pixel on display */
VOID PutPixel( INT X, INT Y, DWORD Color )
{
  if (X < 0 || Y < 0 || X >= FRM_Width || Y >= FRM_Height)
    return;

  FRM_Frame[Y * FRM_Width + X] = Color;
} /* End of 'PutPixel' function */


/* Init display */
static VOID Display( VOID )
{
  CHAR Buf[100];

  Timer();

  if (!IsPause)
  {
   StarsMove(DeltaTime);
   memset(FRM_Frame, 0, FRM_Width * FRM_Height * 4);
   StarsDraw();
  }
  GetLocalTime(&tim);

  sprintf(Buf, "%02d:%02d:%02d   %02d.%02d.%d   %d day   %f FPS", tim.wHour, tim.wMinute, tim.wSecond,
    tim.wDay, tim.wMonth, tim.wYear, tim.wDayOfWeek == 0 ? 7 : tim.wDayOfWeek, FPS);

  PutStr(30, 30, Buf, FRM_RGB(0, 255, 0));
  DrawPCX("LOGO30.pcx", 1753, 931);

  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Set output pozition */
  glRasterPos2d(-1, 1);

  /* Set pixel size */
  glPixelZoom(ZOOM, -ZOOM);

  /* Output function */
  glDrawPixels(FRM_Width, FRM_Height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, FRM_Frame);

  glFinish();

  glutSwapBuffers();
  /* Sending a signal to redraw the window */
  glutPostRedisplay();
} /* End of 'Display' function */

/* Init keyboard */
static VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
    exit(0);
  if (Key == 'f')
    glutFullScreen();
  if (Key == 'w')
    SpeedChange(1000);
  if (Key == 's')
    SpeedChange(-1000);
  if (Key == ' ')
    IsPause = !IsPause;
  if (Key == 'a')
    RotateAll(-0.5);
  if (Key == 'd')
    RotateAll(0.5);
  if (Key == 'z')
    Turn(50000);
  if (Key == 'c')
    Turn(-50000);
  if (Key == 'x')
    SpeedChange(50000);
  if (Key == 'X')
    SpeedChange(-50000);
  if (Key == 'q')
    ;
  if (Key == 'e');
} /* End of 'Keyboard' function */

static VOID Reshape( int W, int H )
{
  glViewport(0, 0, W, H);

  if (FRM_Frame != NULL)
    free(FRM_Frame);

  if ((FRM_Frame = malloc(W * H * 4)) == NULL)
    FRM_Width = 0, FRM_Height = 0;
  else
    FRM_Width = W, FRM_Height = H;
  ProjSet(W, H);
}

/* Main program function */
INT main( INT ArgC, CHAR *ArgV[] )
{
  StarsInit();
  FontLoad("VGA_T.FNT");
  /* Initializing */
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGBA);

  /* Window creation */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("Stars *ND4*");

  /* Fill display with blue color */
  glClearColor(0.3, 0.47, 0.8, 1);

  /* Callback functions setup */
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);

  /* Goto main message loop */
  glutMainLoop();

  return 0;
} /* End of 'main' function */