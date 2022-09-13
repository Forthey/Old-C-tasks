/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: primitive handle.
 */
#include <stdio.h>

#include "rnd.h"

/* Create primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - number of vertex, index:
 *       INT NoofV, NoofI;
 */
BOOL ND4_RndPrimCreate( nd4PRIM *Pr, INT NoofV, INT NoofI )
{
  INT Size;

  memset(Pr, 0, sizeof(nd4PRIM));
  Size = sizeof(nd4VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(Size)) == NULL)
    return FALSE;

  Pr->I = (INT *)(Pr->V+ NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'ND4_RndPrimCreate' function */

/* Delete primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 * RETURNS: None.
 */
VOID ND4_RndPrimFree( nd4PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(nd4PRIM));
} /* End of 'ND4_RndPrimFree' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID ND4_RndPrimDraw( nd4PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr3(Pr->Trans, World, ND4_RndMatrVP);
  POINT *pts;
  INT i;

  if ((pts = malloc(sizeof(POINT) * Pr->NumOfI)) == NULL)
    return;

  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC P = VecMulMatr4x4(Pr->V[i].P, wvp);

    pts[i].x = (P.X + 1) * ND4_RndFrameW / 2;
    pts[i].y = (-P.Y + 1) * ND4_RndFrameH / 2;
  }

  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    ND4_RndFramePutLine(pts[Pr->I[i]].x, pts[Pr->I[i]].y, pts[Pr->I[i + 1]].x, pts[Pr->I[i + 1]].y, RGB(155, 0, 255));
    ND4_RndFramePutLine(pts[Pr->I[i + 1]].x, pts[Pr->I[i + 1]].y, pts[Pr->I[i + 2]].x, pts[Pr->I[i + 2]].y, RGB(155, 0, 255));
    ND4_RndFramePutLine(pts[Pr->I[i + 2]].x, pts[Pr->I[i + 2]].y, pts[Pr->I[i]].x, pts[Pr->I[i]].y, RGB(155, 0, 255));
  }

  free(pts);
} /* End of 'ND4_RndPrimDraw' function */

/* Create sphere function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS: None.
 */
BOOL ND4_RndPrimSphereCreate( nd4PRIM *Pr, DBL R, INT W, INT H )
{
  INT i, k, j, f;
  DBL theta, phi;

  if (!ND4_RndPrimCreate(Pr, W * H, (W - 1) * (H - 1) * 2 * 3))
    return FALSE;

  /* Build vertex array */
  for (theta = 0, i = 0, k = 0; i < H; i++, theta += PI / (H - 1))
    for (phi = 0, j = 0; j < W; j++, phi += 2 * PI / (W - 1))
      Pr->V[k++].P = VecSet(R * sin(phi) * sin(theta),
                            R * cos(theta),
                            R * cos(phi) * sin(theta));

  for (i = 0, k = 0, f = 0; i < H - 1; i++, k++)
    for (j = 0; j < W - 1; j++, k++)
    {
      Pr->I[f++] = k;
      Pr->I[f++] = k + 1;
      Pr->I[f++] = k + W;

      Pr->I[f++] = k + W;
      Pr->I[f++] = k + 1;
      Pr->I[f++] = k + W + 1;
    }
  return TRUE;
} /* End of 'ND4_RndPrimSphere' function */
/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       vg4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ND4_RndPrimLoad( nd4PRIM *Pr, CHAR *FileName )
{
  INT vn = 0, fn = 0;
  FILE *F;
  CHAR Buf[1000];

  memset(Pr, 0, sizeof(nd4PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and index quantities */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      vn++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      fn++;
  }

  if (!ND4_RndPrimCreate(Pr, vn, fn * 3))
  {
    fclose(F);
    return FALSE;
  }

  /* Read vertices and facets data */
  rewind(F);
  vn = fn = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[vn++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      /* Read one of possible facet references */
      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      n1--;
      n2--;
      n3--;
      Pr->I[fn++] = n1;
      Pr->I[fn++] = n2;
      Pr->I[fn++] = n3;
    }
  }
  fclose(F);
  return TRUE;
} /* End of 'ND4_RndPrimLoad' function */
/* END OF 'RNDPRIM.C' FILE */