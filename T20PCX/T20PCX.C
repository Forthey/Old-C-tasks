/* Drekalov Nikita, 09.4, 31.10.2019 */
#include <stdlib.h>
#include <glut.h>

#include "pcx.h"

/*
*** Graphic interface
*/

#define ZOOM 1
#define FRAME_W (1600 / ZOOM)
#define FRAME_H (1000 / ZOOM)

/* Create array for display */
static BYTE Frame[FRAME_H][FRAME_W][3];

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
  /* Clear frame */
  glClearColor(0.3, 0.47, 0.8, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glRasterPos2d(-1, 1);

  glPixelZoom(ZOOM, -ZOOM);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();

  glutSwapBuffers();
  /* sending a signal to redraw the window */
  glutPostRedisplay();
} /* End of 'Display' function */

/* Init keyboard */
VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
    exit(239);
  if (Key == 'f')
    glutFullScreen();
} /* End of 'Keyboard' function */


/* main program function */
INT main( INT ArgC, CHAR *ArgV[] )
{
  DrawPCX("m.pcx", rand() % FRAME_W, rand() % FRAME_H);
  /* Initializing */
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGBA);

  /* Window creation */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("PCX Viewer");

  /* Callback functions setup */
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);

  /* Goto main message loop */
  glutMainLoop();

  return 0;
} /* End of 'main' function */