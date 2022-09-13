/* FILE NAME: UNIT.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 08.01.2020
 * PURPOSE: unit atcion file.
 */
#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ND4UNIT *Uni;
 *   - animation context:
 *       ND4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitInit( nd4UNIT *Uni, nd4ANIM *Ani )
{

} /* End of 'ND4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ND4UNIT *Uni;
 *   - animation context:
 *       ND4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitClose( nd4UNIT *Uni, nd4ANIM *Ani )
{
} /* End of 'ND4_UnitClose' function */
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ND4UNIT *Uni;
 *   - animation context:
 *       ND4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitResponse( nd4UNIT *Uni, nd4ANIM *Ani )
{
} /* End of 'ND4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ND4UNIT *Uni;
 *   - animation context:
 *       ND4ANIM *Ani;
 * RETURNS: None.
 */
static VOID ND4_UnitRender( nd4UNIT *Uni, nd4ANIM *Ani )
{
} /* End of 'ND4_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ND4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_AnimUnitCreate( INT Size )
{
  nd4UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(nd4UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = ND4_UnitInit;
  Uni->Close = ND4_UnitClose;
  Uni->Response = ND4_UnitResponse;
  Uni->Render = ND4_UnitRender;
  return Uni;
} /* End of 'ND4_AnimUnitCreate' function */
/* END OF 'UNIT.C' FILE */