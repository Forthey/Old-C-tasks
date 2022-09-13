/* Drekalov Nikita, 09.4, 31.10.2019 */
#include <math.h>

#include "compl.h"

/* Create complex number */
COMPL ComplSet( DOUBLE A, DOUBLE B )
{
  COMPL Z;

  Z.Re = A;
  Z.Im = B;

  return Z;
} /* Enf of 'ComplSet' function */

/* Sum of complex numbers */
COMPL ComplAddCompl( COMPL Z1, COMPL Z2 )
{
  return ComplSet(Z1.Re + Z2.Re, Z1.Im + Z2.Im);
}

/* Multiplication of complex numbers */
COMPL ComplMulCompl( COMPL Z1, COMPL Z2 )
{
  return ComplSet(Z1.Re * Z2.Re - Z1.Im * Z2.Im, Z1.Re * Z2.Im + Z1.Im * Z2.Re);
} /* Enf of 'ComplMulCompl' function */

/* Module (Normal) of complex number */
DOUBLE ComplNorm( COMPL Z )
{
  return sqrt(Z.Re * Z.Re + Z.Im * Z.Im);
} /* Enf of 'ComplNorm' function */

/* Creating mandelbrot */
INT MandelBrot( COMPL Z )
{
  COMPL Z0 = ComplSet(Z.Re, Z.Im);
  INT n = 0;

  while (n < 255 && ComplNorm(Z) < 2)
  {
    Z = ComplAddCompl(ComplMulCompl(Z, Z), Z0);
    n++;
  }
  return n;
} /* End of 'MandelBrot' function */

/* Creating Julia */
INT Julia( COMPL Z, COMPL C )
{
  INT n = 0;

  while (n < 255 && ComplNorm(Z) < 2)
  {
    Z = ComplAddCompl(ComplMulCompl(Z, Z), C);
    n++;
  }
  return n;
} /* End of 'Julia' function */