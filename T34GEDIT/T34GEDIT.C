/* Drekalov Nikita, 09-4, 16.12.2019 */
#include <glut.h>

#include "gfx.h"

/** Support variables **/

/* Saving mouse parameters */
nd4PRESS ND4_State = ND4_ISNT_PRESS;
nd4BUTTON ND4_Button = ND4_NOT_PRESS;
/* Saving mouse coordinates */
static INT Oldx, Oldy;

/* Display work function */
static VOID Display( VOID )
{
  INT i;

  for (i = 0; i < 1500; i += 10)
  {
    ND4_PutLine(i, 1500 - i, 0, i, ND4_RGB(255, 255, 255));
    ND4_PutLine(1500 - i, i, i, 0, ND4_RGB(255, 255, 255));
  }
  /* Clear display */
  glClear(GL_COLOR_BUFFER_BIT);
  ND4_FrameDraw();

} /* End of 'Display' function */

/* Init keyboard */
static VOID Keyboard( BYTE Key, INT X, INT Y )
{
  switch (Key)
  {
    case 27:
      exit(0);
      break;
    case '1':
      glutFullScreen();
      break;
    case 'c':
      ND4_FrameClear(ND4_RGB(0, 0, 0));
      break;
    case '+':
      ND4_Zoom += 0.1;
      break;
    case '-':
      ND4_Zoom -= 0.1;
      break;
    case 'm':
      ND4_DrawRose(X / ND4_Zoom, Y / ND4_Zoom, 80 / ND4_Zoom, 20 / ND4_Zoom, ND4_RGB(0, 255, 255), ND4_RGB(155, 0, 255));
      break;
    case 'v':
      ND4_DrawVroo(X / ND4_Zoom, Y / ND4_Zoom, 80 / ND4_Zoom, 50 / ND4_Zoom, 20 / ND4_Zoom, ND4_RGB(0, 255, 255), ND4_RGB(155, 0, 255));
      break;
    case 'r':
      ND4_PutCirlce(X / ND4_Zoom, Y / ND4_Zoom, 100, ND4_RGB(255, 0, 255));
      break;
    case 'z':
      ND4_PutFillCircle(X / ND4_Zoom, Y / ND4_Zoom, 100, ND4_RGB(255, 0, 255));
      break;
    case 'f':
      ND4_FloodFill(X / ND4_Zoom, Y / ND4_Zoom, ND4_RGB(255, 0, 255));
      break;
    case 's':
      ND4_SpinDraw(X / ND4_Zoom, Y / ND4_Zoom, 50, ND4_RGB(255, 0, 255));
  }
} /* End of 'Keyboard' function */

/* static VOID Reshape( INT W, INT H )
{
  glViewport(0, 0, W, H);

  if (ND4_Frame != NULL)
    free(ND4_Frame);

  if ((ND4_Frame = malloc(W * H * 4)) == NULL)
    ND4_FrameWidth = 0, ND4_FrameHeight = 0;
  else
    ND4_FrameWidth = W, ND4_FrameHeight = H;
} */

/* Mouse click function */
VOID Mouse( INT Button, INT State, INT X, INT Y )
{
  if (State == GLUT_DOWN)
  {
    ND4_State = ND4_DOWN;
    switch (Button)
    {
    case GLUT_LEFT_BUTTON:
      ND4_Button = ND4_LEFT;
      ND4_PutPixel(X / ND4_Zoom, Y / ND4_Zoom, ND4_RGB(rand() % 255, rand() % 255, rand() % 255));
      break;
    case GLUT_RIGHT_BUTTON:
      ND4_Button = ND4_RIGHT;
      ND4_PutPixel(X / ND4_Zoom, Y / ND4_Zoom, ND4_RGB(0, 0, 0));
      break;
    }
    
    Oldx = X;
    Oldy = Y;

  }
  else
    ND4_State = ND4_UP;
}
 /* End of 'Mouse' function */

/* Mouse motion function */
void Motion( INT X, INT Y )
{
  if (ND4_Button == ND4_LEFT && ND4_State == ND4_DOWN)
    ND4_PutLine(Oldx / ND4_Zoom, Oldy / ND4_Zoom, X / ND4_Zoom, Y / ND4_Zoom, ND4_RGB(255, 255, 255));

  if (ND4_Button == ND4_RIGHT && ND4_State == ND4_DOWN)
    ND4_PutLine(Oldx / ND4_Zoom, Oldy / ND4_Zoom, X / ND4_Zoom, Y / ND4_Zoom, ND4_RGB(0, 0, 0));

  Oldx = X;
  Oldy = Y;
} /* End of 'Motion' function */

/* Main program function */
INT main( INT ArgC, CHAR *ArgV[] )
{
  ND4_FrameInit();
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
  glutMouseFunc(Mouse);
  glutMotionFunc(Motion);
  glutPassiveMotionFunc(Motion);
  /* Goto main message loop */
  glutMainLoop();

  return 0;
} /* End of 'main' function */
/* ENF OF 'T34GEDIT.C' FILE */