/* FILE NAME: MTH.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: Actions with vectors and matrix.
 */
#ifndef __MTH_H_
#define __MTH_H_

#include <commondf.h>
#include <math.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(A) D2R(A)

#define VecSet1(A) VecSet(A, A, A)
#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B), C)
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr3(A, B, C), D)
#define MatrMulMatr5(A, B, C, D, E) MatrMulMatr(MatrMulMatr4(A, B, C, D), E)
#define MatrMulMatr6(A, B, C, D, E, F) MatrMulMatr(MatrMulMatr5(A, B, C, D, E), F)

/* Basic float type */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Big integer type */
typedef ULONG64 UINT64;
typedef LONG64 INT64;
/* Type for vector in space */
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;
/* Type for matrix */
typedef struct tagMATR
{
  DBL M[4][4];
} MATR;

/* Identity matrix */
static MATR UnitMatrix = 
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Create vector function.
 * ARGUMENTS:
 *   - coordinates of vector:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VEC) vector.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC V;

  V.X = X;
  V.Y = Y;
  V.Z = Z;
  return V;
} /* End of 'VecSet' function */

/* Addition two vectors function.
 * ARGUMENTS:
 *   - two vectors:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) sum two vectors.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Subtraction two vectors function.
 * ARGUMENTS:
 *   - two vectors:
 *       VEC V1, V2'
 * RETURNS:
 *   (VEC) result of substraction.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' fuction */

/* Multiplication vector on number function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - number:
 *       DBL Nl
 * RETURNS:
 *   (VEC) result of multiplication.
 */
__inline VEC VecMulNum( VEC V, DBL N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
} /* /* End of 'VecMulNum' fuction */

/* Divine vector on number function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - number:
 *       DBL Nl
 * RETURNS:
 *   (VEC) result of divine.
 */
__inline VEC VecDivNum( VEC V, DBL N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
} /* End of 'VecDivNum' function */

/* Negative vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) result of negative.
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Multiplicate two vectors function.
 * ARGUMENTS: 
 *   - two vectors:
 *       VEC V1, V2;
 * RETURNS:
 *   (DBL) result of multiplication.
 */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Multiplicate two vectors function.
 * ARGUMENTS: 
 *   - two vectors:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result of multiplication.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  VEC VRes;

  VRes.X = V1.Y * V2.Z - V1.Z * V2.Y;
  VRes.Y = V1.Z * V2.X - V1.X * V2.Z;
  VRes.Z = V1.X * V2.Y - V1.Y * V2.X;
  return VRes;
} /* End of 'VecCrossVec' function */

/* Find square vector length function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (DBL) square length of vector.
 */
__inline DBL VecLen2( VEC V )
{
  return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
} /* End of 'VecLen2' function */

/* Find vector length function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (DBL) length of vector.
 */
__inline DBL VecLen( VEC V )
{
  return sqrt(VecLen2(V));
} /* End of 'VecLen' function */

/* Normalize vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) Identity vector.
 */
__inline VEC VecNormalize( VEC V )
{
  return VecDivNum(V, VecLen(V));
} /* End of 'VecLen2' function */

/* Addition two vectors function.
 * ARGUMENTS:
 *   - two vectors:
 *       VEC *VRes, V2;
 * RETURNS:
 *   (VEC) sum two vectors.
 */
__inline VEC VecAddVecEq( VEC *VRes, VEC V )
{
  VRes->X += V.X;
  VRes->Y += V.Y;
  VRes->Z += V.Z;
  return *VRes;
} /* End of 'VecAddVecEq' function */

/* Get identity matrix function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (MATR) idemnity matrix.
 */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Translate vector to matrix function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (MATR) matrix.
 */
__inline MATR MatrTranslate( VEC T )
{
  MATR M = UnitMatrix;

  M.M[3][0] = T.X;
  M.M[3][1] = T.Y;
  M.M[3][2] = T.Z;

  return M;
} /* End of 'MatrTranslate' function */

/* Multiplicate vectoron matrix function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS: 
 *   (VEC) result of multiplication.
 */
__inline VEC VecMulMatr4x4( VEC V, MATR M )
{
  DBL w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

  return VecSet((V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0]) / w,
                (V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1]) / w,
                (V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]) / w);
} /* End of 'VecMulMatrix4x4' function */

/* Scale matrix function.
 * ARGUMENTS:
 *   - vector (scale)
 *       VEC S;
 * RETURNS:
 *   (MATR) scaled matrix.
 */
__inline MATR MatrScale( VEC S )
{
  MATR M = UnitMatrix;

  M.M[0][0] = S.X;
  M.M[1][1] = S.Y;
  M.M[2][2] = S.Z;

  return M;
} /* End of 'MatrScale' function */

/* Rotate matrix 'X' function.
 * ARGUMENTS:
 *   - Angle in dergees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) rotate matrix;
 */
__inline MATR MatrRotateX( DBL AngleInDegrees )
{
  DBL AinR = D2R(AngleInDegrees), si = sin(AinR), co = cos(AinR);
  MATR M = UnitMatrix;

  M.M[1][1] = co;
  M.M[1][2] = -si;
  M.M[2][1] = si;
  M.M[2][2] = co;

  return M;
} /* End of 'MatrRotateX' function */

/* Rotate matrix 'Y' function.
 * ARGUMENTS:
 *   - Angle in dergees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) rotate matrix;
 */
__inline MATR MatrRotateY( DBL AngleInDegrees )
{
  DBL AinR = D2R(AngleInDegrees), si = sin(AinR), co = cos(AinR);
  MATR M = UnitMatrix;

  M.M[0][0] = co;
  M.M[0][2] = -si;
  M.M[2][0] = si;
  M.M[2][2] = co;

  return M;
} /* End of 'MatrRotateY' function */

/* Rotate matrix 'Z' function.
 * ARGUMENTS:
 *   - Angle in dergees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) rotate matrix;
 */
__inline MATR MatrRotateZ( DBL AngleInDegrees )
{
  DBL AinR = D2R(AngleInDegrees), si = sin(AinR), co = cos(AinR);
  MATR M = UnitMatrix;

  M.M[0][0] = co;
  M.M[0][1] = si;
  M.M[1][0] = -si;
  M.M[1][1] = co;

  return M;
} /* End of 'MatrRotateZ' function */

/* Rotate matrix aroud vector function.
 * ARGUMENTS:
 *   - Angle in dergees:
 *       DBL AngleInDegree;
 *   - vector:
 *       VEC R;
 * RETURNS:
 *   (MATR) rotate matrix;
 */
__inline MATR MatrRotate( DBL AngleInDegrees, VEC R )
{
  DBL AinR = D2R(AngleInDegrees), s = sin(AinR), c = cos(AinR);
  MATR M = 
  {
    {
      {c + R.X * R.X * (1 - c), R.X * R.Y * (1 - c) + R.Z * s, R.X * R.Z * (1 - c) - R.Y * s, 0},
      {R.X * R.Y * (1 - c) - R.Z * s, c + R.Y * R.Y * (1 - c), R.Y * R.Z * (1 - c) + R.X * s, 0},
      {R.Z * R.X * (1 - c) + R.Y * s, R.Z * R.Y * (1 - c) - R.X * s, c + R.Z * R.Z * (1 - c), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotate' function */

/* Transform point function.
 * ARGUMENTS:
 *  - coordinates radius-vector:
 *      VEC V;
 *  - matrix:
 *      MATR M;
 *        (VEC) result vector.
 */
__inline VEC PointTransform( VEC V, MATR M )
{
  VEC VRes;

  VRes.X = V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0];
  VRes.Y = V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1];
  VRes.Z = V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2];

  return VRes;
} /* End of 'PointTransform' function */

/* Transform vector function.
 * ARGUMENTS:
 *  - coordinates vector:
 *      VEC V;
 *  - matrix:
 *      MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  VEC VRes;

  VRes.X = V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0];
  VRes.Y = V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1];
  VRes.Z = V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2];

  return VRes;
} /* End of 'VectorTransform' function */

/* Multiplication two matrix function.
 * ARGUMENTS:
 *   - two matrix:
 *       MATR M1, M2;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR MRes = 
  {
    {
      {
        M1.M[0][0] * M2.M[0][0] + M1.M[0][1] * M2.M[1][0] + M1.M[0][2] * M2.M[2][0] + M1.M[0][3] * M2.M[3][0],
        M1.M[0][0] * M2.M[0][1] + M1.M[0][1] * M2.M[1][1] + M1.M[0][2] * M2.M[2][1] + M1.M[0][3] * M2.M[3][1],
        M1.M[0][0] * M2.M[0][2] + M1.M[0][1] * M2.M[1][2] + M1.M[0][2] * M2.M[2][2] + M1.M[0][3] * M2.M[3][2],
        M1.M[0][0] * M2.M[0][3] + M1.M[0][1] * M2.M[1][3] + M1.M[0][2] * M2.M[2][3] + M1.M[0][3] * M2.M[3][3]
      },
      {
        M1.M[1][0] * M2.M[0][0] + M1.M[1][1] * M2.M[1][0] + M1.M[1][2] * M2.M[2][0] + M1.M[1][3] * M2.M[3][0],
        M1.M[1][0] * M2.M[0][1] + M1.M[1][1] * M2.M[1][1] + M1.M[1][2] * M2.M[2][1] + M1.M[1][3] * M2.M[3][1],
        M1.M[1][0] * M2.M[0][2] + M1.M[1][1] * M2.M[1][2] + M1.M[1][2] * M2.M[2][2] + M1.M[1][3] * M2.M[3][2],
        M1.M[1][0] * M2.M[0][3] + M1.M[1][1] * M2.M[1][3] + M1.M[1][2] * M2.M[2][3] + M1.M[1][3] * M2.M[3][3]
      },
      {
        M1.M[2][0] * M2.M[0][0] + M1.M[2][1] * M2.M[1][0] + M1.M[2][2] * M2.M[2][0] + M1.M[2][3] * M2.M[3][0],
        M1.M[2][0] * M2.M[0][1] + M1.M[2][1] * M2.M[1][1] + M1.M[2][2] * M2.M[2][1] + M1.M[2][3] * M2.M[3][1],
        M1.M[2][0] * M2.M[0][2] + M1.M[2][1] * M2.M[1][2] + M1.M[2][2] * M2.M[2][2] + M1.M[2][3] * M2.M[3][2],
        M1.M[2][0] * M2.M[0][3] + M1.M[2][1] * M2.M[1][3] + M1.M[2][2] * M2.M[2][3] + M1.M[2][3] * M2.M[3][3]
      },
      {
        M1.M[3][0] * M2.M[0][0] + M1.M[3][1] * M2.M[1][0] + M1.M[3][2] * M2.M[2][0] + M1.M[3][3] * M2.M[3][0],
        M1.M[3][0] * M2.M[0][1] + M1.M[3][1] * M2.M[1][1] + M1.M[3][2] * M2.M[2][1] + M1.M[3][3] * M2.M[3][1],
        M1.M[3][0] * M2.M[0][2] + M1.M[3][1] * M2.M[1][2] + M1.M[3][2] * M2.M[2][2] + M1.M[3][3] * M2.M[3][2],
        M1.M[3][0] * M2.M[0][3] + M1.M[3][1] * M2.M[1][3] + M1.M[3][2] * M2.M[2][3] + M1.M[3][3] * M2.M[3][3]
      }
    }
  };

  return MRes;
} /* End of 'MatrMulMatr' function */

/* Count determinant 3x3 matrix function.
 * ARGUMENTS:
 *   - matrix elements:
 *       DBL A11, A12, A12, A21, A22, A23, A31, A32, A33;
 * RETURNS:
 *   (DBL) determinant.
 */
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                            DBL A21, DBL A22, DBL A23,
                            DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 + A12 * A23 * A31 -
         A12 * A21 * A33 + A13 * A21 * A32 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Count determinant 3x3 matrix function.
 * ARGUMENTS:
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (DBL) determinant.
 */
__inline DBL MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) -
    M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                              M.M[2][0], M.M[2][2], M.M[2][3],
                              M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) -
    M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                              M.M[2][0], M.M[2][1], M.M[2][2],
                              M.M[3][0], M.M[3][1], M.M[3][2]);
} /* End of 'MatrDeterm' function */

/* Inverse matrix function.
 * ARGUMENTS:
 *   - matrix: 
 *       MATR M;
 * RETURNS:
 *   (MATR) inversed matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
   
  if (det == 0)
    return UnitMatrix;

  /* build adjoint matrix */
  r.M[0][0] =
    MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][0] =
    MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][1] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[2][0], M.M[2][2], M.M[2][3],
                  M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[2][0], M.M[2][1], M.M[2][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[2][0], M.M[2][1], M.M[2][2],
                  M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][2] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                 M.M[1][1], M.M[1][2], M.M[1][3],
                 M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][2] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][3] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3]);
  r.M[1][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[1][0], M.M[1][2], M.M[1][3],
                  M.M[2][0], M.M[2][2], M.M[2][3]);
  r.M[2][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[2][0], M.M[2][1], M.M[2][3]);
  r.M[3][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[1][0], M.M[1][1], M.M[1][2],
                  M.M[2][0], M.M[2][1], M.M[2][2]);

  /* делим на определитель */
  r.M[0][0] /= det;
  r.M[1][0] /= det;
  r.M[2][0] /= det;
  r.M[3][0] /= det;
  r.M[0][1] /= det;
  r.M[1][1] /= det;
  r.M[2][1] /= det;
  r.M[3][1] /= det;
  r.M[0][2] /= det;
  r.M[1][2] /= det;
  r.M[2][2] /= det;
  r.M[3][2] /= det;
  r.M[0][3] /= det;
  r.M[1][3] /= det;
  r.M[2][3] /= det;
  r.M[3][3] /= det;

  return r;
} /* End of 'MatrInverse' function */

/* Viewer function.
 * ARGUMENTS:
 *   - move vectors:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) ViewMatrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC D = VecNormalize(VecSubVec(At, Loc)), 
      R = VecNormalize(VecCrossVec(D, Up1)),
      U = VecCrossVec(R, D);
  MATR m =
  {
    {
      {R.X, U.X, -D.X, 0},
      {R.Y, U.Y, -D.Y, 0},
      {R.Z, U.Z, -D.Z, 0},
      {-VecDotVec(Loc, R), -VecDotVec(Loc, U), VecDotVec(Loc, D), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

/* View frustum matrix.
 * ARGUMENTS:
 *   - parameters of display:
 *       DBL l, r, b, t, n, f;
 * RETURNS:
 *   (MATR) View frustum matrix.
 */
__inline MATR MatrFrustum( DBL l, DBL r, DBL b, DBL t, DBL n, DBL f )
{
  MATR M = 
  {
    {
      {2 * n / (r - l), 0, 0, 0},
      {0, 2 * n / (t - b), 0, 0},
      {(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1},
      {0, 0, -(2 * n * f) / (f - n), 0}
    }
  };

  return M;
} /* End of 'MatrFrustum' function */

/* Orthogonal matrix function.
 * ARGUMENTS:
 *   - parameters of display:
 *       DBL left, right, bottom, top, near, far;
 * RETURNS:
 *   (MATR) View orthogonal matrix.
 */
__inline MATR MatrOrtho( DBL l, DBL r, DBL b, DBL t, DBL n, DBL f )
{
  MATR M =
  {
    {
      {2 / (r - l), 0, 0, 0},
      {0, 2 / (t - b), 0, 0},
      {0, 0, -2 / (f - n), 0},
      {-(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1}
    }
  };

  return M;
} /* End of 'MatrOrtho' function */
#endif /* __MTH_H_ */