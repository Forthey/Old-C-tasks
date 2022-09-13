/* Drekalov Nikita, 09.4, 31.10.2019 */
#include <stdlib.h>
#include <time.h>
#include <glut.h>

#include "compl.h"

/*
*** Graphic interface
*/

/* defines for array 'Frame' */
#define ZOOM 1
#define FRAME_W (1920 / ZOOM)
#define FRAME_H (1080 / ZOOM)


/* Create array for display */
static BYTE Frame[FRAME_H][FRAME_W][3];
DOUBLE SyncTime, FPS, W = 400, H = 300;

/* Set FPS and Syncronize time */
void Timer( void )
{
  LONG t;
  static LONG StartTime = -1, FPSTime, FrameCount;

  t = clock();

  if (StartTime == -1)
    StartTime = FPSTime = t;

  SyncTime = (t - StartTime) / (DOUBLE)CLOCKS_PER_SEC;

  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (DOUBLE)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
  }
} /* Enf of 'Timer' function */

/* Set pixel on display */
VOID PutPixel( INT X, INT Y, INT R, INT G, INT B )
{
  if (X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H)
    return;
  Frame[Y][X][0] = B;
  Frame[Y][X][1] = G;
  Frame[Y][X][2] = R;
} /* End of 'PutPixel' function */


/* Init display */
VOID Display( VOID )
{
  DOUBLE x0 = -2, y0 = -2, x1 = 2, y1 = 2, xs, ys, n;
  COMPL Z, C = ComplSet(0.43 + 0.08 * sin(SyncTime + 8), 0.32 + 0.08 * sin(3.7 * SyncTime));

  Timer();

  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Set output pozition */
  glRasterPos2d(-1, 1);

  /* Set pixel size */
  glPixelZoom(ZOOM, -ZOOM);

  /* Output function */
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  for (ys = 0; ys < H; ys++)
    for (xs = 0; xs < W; xs++)
    {
      Z = ComplSet(xs * (x1 - x0) / W + x0, ys * (y1 - y0) / H + y0);
      n = Julia(Z, C);
      PutPixel(xs, ys, n, n * 3, n * 2);
    }

  glFinish();

  glutSwapBuffers();
  /* Sending a signal to redraw the window */
  glutPostRedisplay();
} /* End of 'Display' function */

/* Init keyboard */
VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
    exit(0);
  if (Key == 'f')
    glutFullScreen();
} /* End of 'Keyboard' function */


/* Main program function */
INT main( INT ArgC, CHAR *ArgV[] )
{
  /* Initializing */
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGBA);

  /* Window creation */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(400, 300);
  glutCreateWindow("Mandelbrot *ND4*");

  /* Fill display with blue color */
  glClearColor(0.3, 0.47, 0.8, 1);

  /* Callback functions setup */
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);

  /* Goto main message loop */
  glutMainLoop();

  return 0;
} /* End of 'main' function */