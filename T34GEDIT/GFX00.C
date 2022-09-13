/* Drekalov Nikita, 09-4, 16.12.2019 */
#include <stdlib.h>
#include <glut.h>

#include "gfx.h"

/* Create array for display */
DWORD *ND4_Frame = NULL;
INT ND4_FrameWidth, ND4_FrameHeight;
DOUBLE ND4_Zoom;

/* Initializing Frane function */
VOID ND4_FrameInit( VOID )
{
  ND4_FrameWidth = 1920;
  ND4_FrameHeight = 1080;
  ND4_Frame = malloc(ND4_FrameWidth * ND4_FrameHeight * 4);
  ND4_Zoom = 1;
  ND4_FrameClear(ND4_RGB(0, 0, 0));
} /* End of 'ND4_FrameInit' function */

/* Clear Frame with current color fucntion */
VOID ND4_FrameClear( DWORD Color )
{
  INT Y, X;

  for (Y = 0; Y < ND4_FrameHeight; Y++)
    for (X = 0; X < ND4_FrameWidth; X++)
      ND4_Frame[Y * ND4_FrameWidth + X] = Color;
} /* End of 'ND4_FrameClear' function */

/* Draw frame function */
VOID ND4_FrameDraw( VOID )
{
  /* Set output pozition function */
  glRasterPos2d(-1, 1);
  /* Set pixel size function */
  glPixelZoom(ND4_Zoom, -ND4_Zoom);
  /* Output function */
  glDrawPixels(ND4_FrameWidth, ND4_FrameHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE, ND4_Frame);
  /* Finish gl working function */
  glFinish();
  /* Copy the 2nd buffer to 1st fucntion */
  glutSwapBuffers();
  /* Sending a signal to redraw the window fucntion */
  glutPostRedisplay();
} /* End of 'ND4_FrameDraw' function */
/* END OF 'GFX00.C' FILE */