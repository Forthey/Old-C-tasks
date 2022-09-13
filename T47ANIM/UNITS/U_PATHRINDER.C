/* FILE NAME: U_PATHRINDER.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 10.01.2020
 * PURPOSE: Pathrinder unit creation.
 */
#include <time.h>

#include "../anim/anim.h"

typedef struct
{
  ND4_UNIT_BASE_FIELDS;
  nd4PRIM Pathrinder;
  FLT
    PosX,
    PosZ;
} nd4UNIT_PATHRINDER;

/* Pathrinder unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_PATHRINDER *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitInit( nd4UNIT_PATHRINDER *Uni, nd4ANIM *Ani )
{
  ND4_RndPrimLoad(&Uni->Pathrinder, "OBJ's/Nissan_Pathfinder.object");
  Uni->PosX = 20 * R1();
  Uni->PosZ = 20 * R1();
} /* End of 'ND4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ND4UNIT *Uni;
 *   - animation context:
 *       ND4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitClose( nd4UNIT_PATHRINDER *Uni, nd4ANIM *Ani )
{
  ND4_RndPrimFree(&Uni->Pathrinder);
} /* End of 'ND4_UnitClose' function */

/* Pathrinder unit inter frame events han
dle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_PATHRINDER *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitResponse( nd4UNIT_PATHRINDER *Uni, nd4ANIM *Ani )
{
  Uni->Pathrinder.Trans = 
    MatrMulMatr3(MatrRotateX(90),
    MatrRotateY(4 * Uni->PosZ),
    MatrTranslate(VecMulMatr4x4(VecSet(2 * Uni->PosX, 0, -2 * Uni->PosZ + 40 * sin(Ani->Time * Uni->PosZ / 8)), MatrRotateY(4 * Uni->PosZ))));
} /* End of 'ND4_UnitResponse' function */

/* Pathrinder unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_PATHRINDER *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitRender( nd4UNIT_PATHRINDER *Uni, nd4ANIM *Ani )
{
  ND4_RndPrimDraw(&Uni->Pathrinder, MatrIdentity());
} /* End of 'ND4_UnitRender' function */

/* Unit pathrinder creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreatePathrinder( VOID )
{
  nd4UNIT_PATHRINDER *Uni;

  if ((Uni = (nd4UNIT_PATHRINDER *)ND4_AnimUnitCreate(sizeof(nd4UNIT_PATHRINDER))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)ND4_UnitInit;
  Uni->Response = (VOID *)ND4_UnitResponse;
  Uni->Render = (VOID *)ND4_UnitRender;
  return (nd4UNIT *)Uni;
} /* End of 'ND4_UnitPathrinderCreate' function */
 /* END OF 'U_PATHRINDER.C' FILE */