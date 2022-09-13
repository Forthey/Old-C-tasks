/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: ND4
 * LAST UPDATE: 10.01.2020
 * PURPOSE: primitive handle.
 */
#include <stdio.h>

#include "../anim.h"

/***
 * Primitive support
 ***/

/* Create primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       nd4PRIM *Pr;
 *   - new primitive topology type:
 *       nd4PRIM_TYPE Type;
 *   - new primitive vertex array:
 *       nd4VERTEX *V;
 *   - new primitive vertex array size:
 *       INT NoofV;
 *   - new primitive index array:
 *       INT *I;
 *   - new primitive index array size:
 *       INT NoofI;
 * RETURNS: None.
 */
VOID ND4_RndPrimCreate( nd4PRIM *Pr, nd4PRIM_TYPE Type,
                        nd4VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  memset(Pr, 0, sizeof(nd4PRIM));

  if (V != NULL && NoofV != 0)
  {
    /* Generate vertex array and vertex buffer */
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    /* Fill vertex buffer */
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(nd4VERTEX) * NoofV, V, GL_STATIC_DRAW);

    /* Setup vertex array  */
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(nd4VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(nd4VERTEX),
                          (VOID *)sizeof(VEC)); /* texture cootdinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(nd4VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(nd4VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
  }

  if (I != NULL)
  {
    /* Generate index buffer */
    glGenBuffers(1, &Pr->IBuf);

    /* Fill index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);
  }
  if (NoofI != 0)
    Pr->NumOfElements = NoofI;
  else
    Pr->NumOfElements = NoofV;

  Pr->Type = Type;
  Pr->Trans = MatrIdentity();
} /* End of 'ND4_RndPrimCreate' function */

/* Free primitive memory function.
 * ARGUMENTS:
 *   - pointer to primitive to free:
 *       nd4PRIM *Pr;
 * RETURNS: None.
 */
VOID ND4_RndPrimFree( nd4PRIM *Pr )
{
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);

  glDeleteVertexArrays(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(nd4PRIM));
} /* End of 'ND4_RndPrimFree' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to free:
 *       nd4PRIM *Pr;
 *   - transformation 'world' matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID ND4_RndPrimDraw( nd4PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr3(Pr->Trans, World, ND4_RndMatrVP);
  INT loc,
    pr_type =
      Pr->Type == ND4_PRIM_TRIMESH ? GL_TRIANGLES :
      Pr->Type == ND4_PRIM_LINE ? GL_LINES : GL_POINTS;

  glLoadMatrixf(wvp.M[0]);

  glUseProgram(ND4_RndProgId);
  if ((loc = glGetUniformLocation(ND4_RndProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.M[0]);
  if ((loc = glGetUniformLocation(ND4_RndProgId, "Time")) != -1)
    glUniform1f(loc, ND4_Anim.Time);
  if ((loc = glGetUniformLocation(ND4_RndProgId, "CamX")) != -1)
    glUniform1f(loc, ND4_Anim.Cam.X);
  if ((loc = glGetUniformLocation(ND4_RndProgId, "CamY")) != -1)
    glUniform1f(loc, ND4_Anim.Cam.Y);
  if ((loc = glGetUniformLocation(ND4_RndProgId, "CamZ")) != -1)
    glUniform1f(loc, ND4_Anim.Cam.Z);

 
  glBindVertexArray(Pr->VA);
  if (Pr->IBuf != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(pr_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
  }
  else
    glDrawArrays(pr_type, 0, Pr->NumOfElements);
  glBindVertexArray(0);
} /* End of 'ND4_RndPrimDraw' function */

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       nd4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ND4_RndPrimLoad( nd4PRIM *Pr, CHAR *FileName )
{
  INT vn = 0, fn = 0, vnn = 0, i;
  FILE *F;
  CHAR Buf[1000];
  INT size;
  nd4VERTEX *V;
  INT *Ind;

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

  size = sizeof(nd4VERTEX) * vn + sizeof(INT) * fn * 3;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + vn);

  memset(V, 0, sizeof(nd4VERTEX));

  /* Read vertices and facets data */
  rewind(F);
  vn = fn = vnn = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[vn++].P = VecSet(x, y, z);
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
      Ind[fn++] = n1;
      Ind[fn++] = n2;
      Ind[fn++] = n3;
    }
    /*
    else if (Buf[0] == 'v' && Buf[1] == 'n' && Buf[2] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 3, "%lf%lf%lf", &x, &y, &z);

      V[vnn++].N = VecSet(x, y, z);
    }
    */
  }
  fclose(F);

  for (i = 0; i < fn; i += 3)
  {
    INT 
      P0 = Ind[i],
      P1 = Ind[i + 1], 
      P2 = Ind[i + 2];
    VEC
      V1 = VecSubVec(V[P1].P, V[P0].P),
      V2 = VecSubVec(V[P2].P, V[P0].P),
      N;

    N = VecNormalize(VecCrossVec(V1, V2));   

    V[P0].N = VecNormalize(VecAddVec(V[P0].N, N));
    V[P1].N = VecNormalize(VecAddVec(V[P1].N, N));
    V[P2].N = VecNormalize(VecAddVec(V[P2].N, N));
  }
  /* Shade all vertices */
  for (i = 0; i < vn; i++)
  {
    VEC L = VecNormalize(VecSet(1, 1, 1));
    FLT nl = VecDotVec(V[i].N, L);
    VEC4 c = {0.6, 0.7, 0.8, 1};

    if (nl < 0.1)
      nl = 0.1;
    c.X *= nl;
    c.Y *= nl;
    c.Z *= nl;
    V[i].C = c;
  }
  ND4_RndPrimCreate(Pr, ND4_PRIM_TRIMESH, V, vn, Ind, fn);
  free(V);
  return TRUE;
} /* End of 'ND4_RndPrimLoad' function */

/* Create sphere primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       nd4PRIM *Pr;
 *   - sphere radius:
 *       FLT R;
 *   - split parts counts:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ND4_RndPrimSphereCreate( nd4PRIM *Pr, FLT R, INT W, INT H )
{
  INT i, j, k, f;
  FLT
    phi, theta;
  INT size;
  nd4VERTEX *V;
  INT *Ind;

  memset(Pr, 0, sizeof(nd4PRIM));
  size = sizeof(nd4VERTEX) * W * H + sizeof(INT) * (W - 1) * (H - 1) * 2 * 3;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + W * H);

  memset(V, 0, sizeof(nd4VERTEX));
  /* Build vertex array */
  for (theta = 0, i = 0, k = 0; i < H; i++, theta += PI / (H - 1))
    for (phi = 0, j = 0; j < W; j++, phi += 2 * PI / (W - 1))
    {
      V[k].N = VecSet(sin(phi) * sin(theta),
                      cos(theta),
                      cos(phi) * sin(theta));
      V[k].P = VecMulNum(V[k].N, R);
      k++;
    }
  for (i = 0, k = 0, f = 0; i < H - 1; i++, k++)
    for (j = 0; j < W - 1; j++, k++)
    {
      Ind[f++] = k;
      Ind[f++] = k + 1;
      Ind[f++] = k + W;
      Ind[f++] = k + W;
      Ind[f++] = k + 1;
      Ind[f++] = k + W + 1;
    }

  /* Shade all vertices */
  for (i = 0; i < W * H; i++)
  {
    VEC L = VecNormalize(VecSet(1, 1, 1));
    FLT nl = VecDotVec(V[i].N, L);
    VEC4 c = {0.88, 0.45, 0.18, 1};

    if (nl < 0.1)
      nl = 0.1;
    c.X *= nl;
    c.Y *= nl;
    c.Z *= nl;
    V[i].C = c;
  }
  
  ND4_RndPrimCreate(Pr, ND4_PRIM_TRIMESH, V, W * H, Ind, (W - 1) * (H - 1) * 2 * 3);
  free(V);
  return TRUE;
} /* End of 'ND4_RndPrimCreateSphere' function */

/* END OF 'RNDPRIM.C' FILE */