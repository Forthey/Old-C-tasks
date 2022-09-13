/* FILE NAME  : U_CTRL.C
 * PROGRAMMER : VG4
 * LAST UPDATE: 08.01.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Control unit sample.
 */
#include <stdio.h>

#include "../units.h"

/* Animation unit representation type */
typedef struct tagnd4UNIT_CTRL
{
  ND4_UNIT_BASE_FIELDS;
  DBL
    Distance,      /* Camera offset */
    RotateAngle,   /* Camera rotate angle */
    ElevatorAngle; /* Camera elevator angle */
} nd4UNIT_CTRL;

DBL ND4_MouseWheel;

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
    Uni->RotateAngle += Ani->DeltaTime * 30 * Ani->Mdx;
    Uni->ElevatorAngle += Ani->DeltaTime * 30 * Ani->Mdy;
  }
  L = PointTransform(L,
        MatrMulMatr(MatrRotateX(Uni->ElevatorAngle),
                    MatrRotateY(Uni->RotateAngle)));
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

  SetTextColor(Ani->hDC, RGB(255, 255, 255));
  SetBkMode(Ani->hDC, TRANSPARENT);
  TextOut(Ani->hDC, 30, 102, Buf, sprintf(Buf, "FPS: %.3f", Ani->FPS));
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
