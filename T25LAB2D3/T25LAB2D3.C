/* Drekalov Nikita, 09-4, 02.11.2019 */
#include <time.h>
#include <stdlib.h>
#include <glut.h>

#include "lab2d3.h"

/* defines for array 'Frame' */
#define ZOOM 20

/* Create array for display */
DWORD *FRM_Frame = NULL;

INT FRM_Width = 0, FRM_Height = 0, IsPause = 0;
DBL DeltaTime, SyncTime, FPS;
BOOL End = 0;

/* Set pixel on display */
VOID PutPixel( INT X, INT Y, DWORD Color )
{
  if (X < 0 || Y < 0 || X >= FRM_Width || Y >= FRM_Height)
    return;

  FRM_Frame[Y * FRM_Width + X] = Color;
} /* End of 'PutPixel' function */

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
    SyncTime = (t - StartTime - PauseTime) / (DBL)CLOCKS_PER_SEC;
    DeltaTime = (t - OldTime) / (DBL)CLOCKS_PER_SEC;
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
    FPS = FrameCount / ((t - FPSTime) / (DBL)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
  }
}

/* Init display */
static VOID Display( VOID )
{
  INT i;

  Timer();
  /* Set output pozition */
  glRasterPos2d(-1, 1);

  /* Set pixel size */
  glPixelZoom(ZOOM, -ZOOM);

  for (i = 0; i < NumOfEnemies; i++)
  {
    Enemy[i].DeltaTime += DeltaTime;
    if (Enemy[i].DeltaTime > 0.5)
    {
      LoadS();
      EnemyMove();
      Enemy[i].DeltaTime = 0;
    }
  }
  glClear(GL_COLOR_BUFFER_BIT);
  DeathCheck();
  DrawLab();

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
}

void Special( int Key, int X, int Y )
{
  switch (Key)
  {
  case GLUT_KEY_LEFT:
    if (Ava.X > 0 && Lab[Ava.Y][Ava.X - 1] == 0)
      Ava.X--;
    if (Ava.X == Exit.X && Ava.Y == Exit.Y)
      Ava.X = MAX, Ava.Y = MAX, End = 1;
    break;
  case GLUT_KEY_RIGHT:
    if (Ava.X < MAX - 1 && Lab[Ava.Y][Ava.X + 1] == 0)
      Ava.X++;
    if (Ava.X == Exit.X && Ava.Y == Exit.Y)
      Ava.X = MAX, Ava.Y = MAX, End = 1;
    break;
  case GLUT_KEY_UP:
    if (Ava.Y < MAX - 1 && Lab[Ava.Y - 1][Ava.X] == 0)
      Ava.Y--;
    if (Ava.X == Exit.X && Ava.Y == Exit.Y)
        Ava.X = MAX, Ava.Y = MAX, End = 1;
    break;
  case GLUT_KEY_DOWN:
    if (Ava.Y < MAX - 1 && Lab[Ava.Y + 1][Ava.X] == 0)
      Ava.Y++;
   if (Ava.X == Exit.X && Ava.Y == Exit.Y)
        Ava.X = MAX, Ava.Y = MAX, End = 1;
    break;
  }
}

/* Main program function */
INT main( INT ArgC, CHAR *ArgV[] )
{
  LoadLab("Labyrinth2.txt");
  /* Initializing */
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGBA);

  /* Window creation */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("Packman *ND4*");

  /* Fill display with blue color */
  glClearColor(0.3, 0.47, 0.8, 1);

  /* Callback functions setup */
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutSpecialFunc(Special);

  /* Goto main message loop */
  glutMainLoop();

  return 0;
} /* End of 'main' function */