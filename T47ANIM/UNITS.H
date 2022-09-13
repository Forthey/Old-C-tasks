/* FILE NAME: UNITS.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 08.01.2020
 * PURPOSE: units header file.
 */
#ifndef __UNITS_H
#define __UNITS_H

#include "def.h"
#include "anim/anim.h"

extern FLT ND4_MouseWheel;
/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreateBall( VOID );
/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreateCow( VOID );

/* Control unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (nd4UNIT_CTRL *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreateControl( VOID );

/* Unit mand creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreateMand( VOID );

/* Unit pathrinder creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nd4UNIT *) pointer to created unit.
 */
nd4UNIT * ND4_UnitCreatePathrinder( VOID );

#endif /* __UNITS_H */
/* END OF 'UNITS.H' FILE */