/* FILE NAME: U_MAND.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 10.01.2020
 * PURPOSE: Mand unit creation.
 */
#include <time.h>

#include "../anim/anim.h"

typedef struct
{
  ND4_UNIT_BASE_FIELDS;
  nd4PRIM Mand;
} nd4UNIT_MAND;

/* Mand unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_MAND *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitInit( nd4UNIT_MAND *Uni, nd4ANIM *Ani )
{
  nd4VERTEX V[4];
  INT I[4];

  V[0].P = VecSet(-1, -1, 0);
  V[1].P = VecSet(1, -1, 0);
  V[2].P = VecSet(1, 1, 0);
  V[3].P = VecSet(-1, 1, 0);

  I[0] = 1;
  I[1] = 2;
  I[2] = 3;
  I[3] = 1;
  ND4_RndPrimCreate(&Uni->Mand, GL_TRIANGLE_STRIP, V, 4, I, 2);
} /* End of 'ND4_UnitInit' function */

/* Mand unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_MAND *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitResponse( nd4UNIT_MAND *Uni, nd4ANIM *Ani )
{
} /* End of 'ND4_UnitResponse' function */

/* Mand unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_MAND *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitRender( nd4UNIT_MAND *Uni, nd4ANIM *Ani )
{
  ND4_RndPrimDraw(&Uni->Mand, MatrIdentity());
} /* End of 'ND4_UnitRender' function */

/* Unit mand creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreateMand( VOID )
{
  nd4UNIT_MAND *Uni;

  if ((Uni = (nd4UNIT_MAND *)ND4_AnimUnitCreate(sizeof(nd4UNIT_MAND))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)ND4_UnitInit;
  Uni->Response = (VOID *)ND4_UnitResponse;
  Uni->Render = (VOID *)ND4_UnitRender;
  return (nd4UNIT *)Uni;
} /* End of 'ND4_UnitMandCreate' function */
 /* END OF 'U_MAND.C' FILE */