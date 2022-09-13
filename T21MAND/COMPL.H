/* Drekalov Nikita, 09.4, 31.10.2019 */
#include <commondf.h>

/* Complex number */
typedef struct
{
  DOUBLE Re, Im;
} COMPL;

/* Set pixel on display */
VOID PutPixel( INT X, INT Y, INT R, INT G, INT B );
/* Creating complex number */
COMPL ComplSet( DOUBLE A, DOUBLE B );
/* Creating mandelbrot */
INT MandelBrot( COMPL Z );
/* Creating Julia */
INT Julia( COMPL Z, COMPL C );
