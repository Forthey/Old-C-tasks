/* Drekalov Nikita, 09-4, 30.10.2019 */
#include <glut.h>
#include <stdlib.h>
#include <time.h>

#include "life.h"

#define ZOOM 2
#define FRAME_W (1920 / ZOOM)
#define FRAME_H (1080 / ZOOM)

static byte Frame[FRAME_H][FRAME_W][3];
static byte Pause = 0;


void PutPix( int X, int Y, int R, int G, int B )
{
  if (X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H)
    return;
  Frame[Y][X][0] = B;
  Frame[Y][X][1] = G;
  Frame[Y][X][2] = R;
}

void Display( void )
{
  /* Clear frame */
  glClearColor(0.3, 0.47, 0.8, 1);
  glClear(GL_COLOR_BUFFER_BIT);


  glRasterPos2d(-1, 1);

  glPixelZoom(ZOOM, -ZOOM);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  if (!Pause)
    LifeStep();

  glFinish();

  glutSwapBuffers();

  glutPostRedisplay();
}


void Keyboard( byte Key, int X, int Y )
{
  if (Key == 27)
    exit(0);
  if (Key == 'f')
    glutFullScreen();
  if (Key == ' ')
    Pause = !Pause;
  if (Key == 'r')
    RandInjection();
  if (Key == 's')
    SticksInjection(X / ZOOM, Y / ZOOM);
  if (Key == 'c')
    FieldClear();
  if (Key == 'w')
    RunnersInjection(X / ZOOM, Y / ZOOM);
  if (Key == 'a')
    BarrelInjection(X / ZOOM, Y/ ZOOM);
  if (Key == 'q')
    BurstInjection(X / ZOOM, Y / ZOOM);
  if (Key == 'e')
    FillRand();
}

int main( int ArgC, char *ArgV[] )
{
  LifeInit();

  /* Initializing */
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGBA);

  /* Window creation */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("Civilization (by ND4)");

  /* Callback functions setup */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  /* Goto main message loop */
  glutMainLoop();

  return 0;
}