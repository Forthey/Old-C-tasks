/* FILE NAME: U_COW.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 08.01.2020
 * PURPOSE: Cow unit creation.
 */
#include <time.h>

#include "../anim/anim.h"

typedef struct
{
  ND4_UNIT_BASE_FIELDS;
  nd4PRIM Cow;
  DBL
    PosX,
    PosZ;
} nd4UNIT_COW;

/* Cow unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_COW *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitInit( nd4UNIT_COW *Uni, nd4ANIM *Ani )
{
  ND4_RndPrimLoad(&Uni->Cow, "cow.object");
  Uni->PosX = 0;
  Uni->PosZ = 0;
} /* End of 'ND4_UnitInit' function */

/* Cow unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_COW *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitResponse( nd4UNIT_COW *Uni, nd4ANIM *Ani )
{
  Uni->Cow.Trans = 
    MatrMulMatr(MatrRotateX(sin(Ani->Time)),
    MatrTranslate(VecSet(Uni->PosX, 0, Uni->PosZ)));
} /* End of 'ND4_UnitResponse' function */

/* Cow unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_COW *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitRender( nd4UNIT_COW *Uni, nd4ANIM *Ani )
{
  ND4_RndPrimDraw(&Uni->Cow, MatrIdentity());
} /* End of 'ND4_UnitRender' function */

/* Unit cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreateCow( VOID )
{
  nd4UNIT_COW *Uni;

  if ((Uni = (nd4UNIT_COW *)ND4_AnimUnitCreate(sizeof(nd4UNIT_COW))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)ND4_UnitInit;
  Uni->Response = (VOID *)ND4_UnitResponse;
  Uni->Render = (VOID *)ND4_UnitRender;
  return (nd4UNIT *)Uni;
} /* End of 'ND4_UnitCowCreate' function */
 /* END OF 'U_COW.C' FILE */