/* FILE NAME  : U_CTRL.C
 * PROGRAMMER : VG4
 * LAST UPDATE: 10.01.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Control unit sample.
 */
#include <stdio.h>

#include "../units.h"

#include <mmsystem.h>

#pragma comment(lib, "winmm")

#define ND4_GET_JOYSTICK_AXIS(A) \
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)

/* Animation unit representation type */
typedef struct tagnd4UNIT_CTRL
{
  ND4_UNIT_BASE_FIELDS;
  FLT
    Distance,      /* Camera offset */
    RotateAngle,   /* Camera rotate angle */
    ElevatorAngle; /* Camera elevator angle */
} nd4UNIT_CTRL;

FLT ND4_MouseWheel;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_CTRL *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitInit( nd4UNIT_CTRL *Uni, nd4ANIM *Ani )
{
  Uni->RotateAngle = 30;
  Uni->ElevatorAngle = 47;
  Uni->Distance = 47;
} /* End of 'ND4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_CTRL *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitClose( nd4UNIT_CTRL *Uni, nd4ANIM *Ani )
{
} /* End of 'ND4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_CTRL *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitResponse( nd4UNIT_CTRL *Uni, nd4ANIM *Ani )
{
  VEC L = VecSet(0, 0, Uni->Distance);
  POINT pt;
  INT i;

  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          ND4_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          ND4_Anim.JButClick[i] = ND4_Anim.JBut[i] && !ND4_Anim.JButOld[i];
          ND4_Anim.JButOld[i] = ND4_Anim.JBut[i];
        }

        /* Axes */
        ND4_Anim.JX = ND4_GET_JOYSTICK_AXIS(X);
        ND4_Anim.JY = ND4_GET_JOYSTICK_AXIS(Y);
        ND4_Anim.JZ = ND4_GET_JOYSTICK_AXIS(Z);
        ND4_Anim.JR = ND4_GET_JOYSTICK_AXIS(R);

        /* Point of view */
        ND4_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }

  GetKeyboardState(Ani->Keys);
  GetCursorPos(&pt);
  ScreenToClient(Ani->hWnd, &pt);
  Ani->Mdz = ND4_MouseWheel;
  Ani->Mz += ND4_MouseWheel;
  ND4_MouseWheel = 0;
  Ani->Mdx = -pt.x + Ani->Mx;
  Ani->Mdy = pt.y - Ani->My;
  Ani->Mx = pt.x;
  Ani->My = pt.y;

  for (i = 0; i < 256; i++)
  {
    Ani->Keys[i] >>= 7;
    Ani->KeysClick[i] = Ani->Keys[i] && !Ani->KeysOld[i];
  }
  memcpy(Ani->KeysOld, Ani->Keys, 256);

  if (Ani->KeysClick['P'] && Ani->Keys[VK_CONTROL])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->KeysClick[VK_LEFT] && Ani->Keys[VK_MENU])
    ND4_AnimFlipFullScreen();
  if (Ani->KeysClick[VK_ESCAPE])
    ND4_AnimDoExit();

  Uni->Distance -= Ani->Mdz * 0.005;
  if (Ani->Keys[VK_LBUTTON])
  {
    Uni->RotateAngle += Ani->GlobalDeltaTime * 13 * Ani->Mdx;
    Uni->ElevatorAngle += Ani->GlobalDeltaTime * 13 * Ani->Mdy;
  }
  L = VectorTransform(L,
        MatrMulMatr(MatrRotateX(Uni->ElevatorAngle),
                    MatrRotateY(Uni->RotateAngle)));
  Ani->Cam = L;
  ND4_RndCamSet(L, VecSet(0, 0, 0), VecSet(0, 1, 0));
} /* End of 'ND4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_CTRL *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitRender( nd4UNIT_CTRL *Uni, nd4ANIM *Ani )
{
  static CHAR Buf[100];

  sprintf(Buf, "FPS: %.3f", Ani->FPS);
  SetWindowText(Ani->hWnd, Buf);
} /* End of 'VG4_UnitRender' function */

/* Control unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (nd4UNIT_CTRL *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreateControl( VOID )
{
  nd4UNIT_CTRL *Uni;

  /* Memory allocation */
  if ((Uni = (nd4UNIT_CTRL *)ND4_AnimUnitCreate(sizeof(nd4UNIT_CTRL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)ND4_UnitInit;
  Uni->Close = (VOID *)ND4_UnitClose;
  Uni->Response = (VOID *)ND4_UnitResponse;
  Uni->Render = (VOID *)ND4_UnitRender;
  return (nd4UNIT *)Uni;
} /* End of 'ND4_UnitCreateControl' function */

/* END OF 'U_CTRL.C' FILE */
