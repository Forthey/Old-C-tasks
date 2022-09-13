/* FILE NAME: U_BBALL.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 08.01.2020
 * PURPOSE: ball unit work file.
 */

#include "../anim/anim.h"

#define GRIDS_W 100
#define GRIDS_H 100

typedef struct
{
  ND4_UNIT_BASE_FIELDS;
  nd4PRIM Ball;
  DBL
    TimeShift,
    TimeScale,
    PosX,
    PosZ;
} nd4UNIT_BALL;

/* Get random amount -1...1 function.
 * ARGUNETS: None.
 * RETURNS: 
 *   (DBL) Amount.
 */
DBL R1( VOID )
{
  return (DBL)2 * rand() / RAND_MAX - 1;
}/* End of 'R1' function */

/* Get random amount 0...1 function.
 * ARGUNETS: None.
 * RETURNS: 
 *   (DBL) Amount.
 */
DBL R0( VOID )
{
  return (DBL)rand() / RAND_MAX;
}/* End of 'R0' function */

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_BALL *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitInit( nd4UNIT_BALL *Uni, nd4ANIM *Ani )
{
  Uni->PosX = 20 * R1();
  Uni->PosZ = 20 * R1();
  Uni->TimeShift = 2;
  Uni->TimeScale = 10 * R0();
  ND4_RndPrimSphereCreate(&Uni->Ball, 1, 18, 10);
} /* End of 'ND4_UnitInit' function */
/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_BALL *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitResponse( nd4UNIT_BALL *Uni, nd4ANIM *Ani )
{
  Uni->Ball.Trans = 
    MatrTranslate(VecSet(Uni->PosX, Uni->TimeScale * sin(Ani->Time * Uni->TimeScale * Uni->TimeShift + Uni->TimeShift) + 10, Uni->PosZ));
} /* End of 'ND4_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nd4UNIT_BALL *Uni;
 *   - animation context:
 *       nd4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitRender( nd4UNIT_BALL *Uni, nd4ANIM *Ani )
{
  ND4_RndPrimDraw(&Uni->Ball, MatrIdentity());
} /* End of 'ND4_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT_BALL * ND4_UnitCreateBall( VOID )
{
  nd4UNIT_BALL *Uni;

  if ((Uni = (nd4UNIT_BALL *)ND4_AnimUnitCreate(sizeof(nd4UNIT_BALL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)ND4_UnitInit;
  Uni->Response = (VOID *)ND4_UnitResponse;
  Uni->Render = (VOID *)ND4_UnitRender;

  return Uni;
} /* End of 'ND4_UnitCreateBall' function */
/* END OF 'U_BBALL.C' FILE */