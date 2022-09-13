/* Drekalov Nikita, 09-4, 25.12.2019 */
#include <glut.h>

#include "mt.h"

/* Create array for display */
#define ND4_FrameWidth 1920
#define ND4_FrameHeight 1080

DWORD ND4_Frame[ND4_FrameWidth * ND4_FrameHeight];
DOUBLE ND4_Zoom = 1;


VOID ND4_PutPixel( INT X, INT Y, BYTE Color )
{
  if (X < 0 || Y < 0 || X >= ND4_FrameWidth || Y >= ND4_FrameHeight)
    return;

   ND4_Frame[Y * ND4_FrameWidth + X] = Color;
}
/* Display function */
VOID Display( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT);

  /* Set output pozition */
  glRasterPos2d(-1, 1);

  /* Set pixel size */
  glPixelZoom(ND4_Zoom, -ND4_Zoom);

  /* Output function */
  glDrawPixels(ND4_FrameWidth, ND4_FrameHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, ND4_Frame);

  glFinish();

  glutSwapBuffers();
  /* Sending a signal to redraw the window */
  glutPostRedisplay();
} /* End of 'Display' function */

/* Keyboard function */
VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
    exit(0);
} /* End of 'Keyboard' function */

/* Reshape function */
/* VOID Reshape( int W, int H )
{
  glViewport(0, 0, W, H);

  if (ND4_Frame != NULL)
    free(ND4_Frame);

  if ((ND4_Frame = malloc(W * H * 4)) == NULL)
    ND4_FrameWidth = 0, ND4_FrameHeight = 0;
  else
    ND4_FrameWidth = W, ND4_FrameHeight = H;
} *//* End of 'Reshape' function */

/* main program function */
INT main( INT ArgC, CHAR *ArgV[] )
{
  ND4_FileRead("tst_tst.tst");
  /* Initializing */
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGBA);

  /* Window creation */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("ND4_GEDIT");

  /* Fill display with blue color */
  glClearColor(0.3, 0.47, 0.8, 1);

  /* Callback functions setup */
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);
  /* glutReshapeFunc(Reshape); */

  /* Goto main message loop */
  glutMainLoop();

  return 0;
} /* End of 'main' function */
/* ENF OF 'T35MT.C' FILE */