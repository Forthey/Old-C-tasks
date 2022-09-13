/* FILE NAME: RND.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: rendering system depended.
 */
#ifndef __RND_H_
#define __RND_H_

#define GLEW_STATIC
#include <glew.h>

#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "glew32s")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#include "../../def.h"

extern HWND ND4_hRndWnd;                 /* Render window handle */
extern HDC ND4_hRndDC;              /* Render device context handle */
extern INT ND4_RndFrameW, ND4_RndFrameH; /* Render frame width and height */
extern HGLRC ND4_hRndGLRC;               /* OpenGL rendering context */
extern FLT 
 ND4_RndProjSize,                        /* Projection size */
 ND4_RndProjDist,                        /* Projection distance */
 ND4_RndProjFarClip;                     /* Projection far clip */
extern MATR
 ND4_RndMatrView,                        /* View matrix */
 ND4_RndMatrProj,                        /* Projection matrix */ 
 ND4_RndMatrVP;                          /* VP matrix */
extern UINT ND4_RndProgId;

/* Rendering init function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID ND4_RndInit( HWND hWnd );
/* Rendering close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ND4_RndClose( VOID );
/* Rendering resize function.
 * ARGUMENTS: 
 *   - window width and height.
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID ND4_RndResize( INT W, INT H );
/* Copy frame buffer function.
 * ARGUMENTS:
 *   - device context handle:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID ND4_RndCopyFrame( VOID );
/* Set camera function.
 * ARGUMENTS:
 *   - set camera position:
 *       VEC Loc, At, Up;
 * RETURNS: None.
 */
VOID ND4_RndCamSet( VEC Loc, VEC At, VEC Up );
/* Start rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndStart( VOID );
/* End rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ND4_RndEnd( VOID );

/***
 * Primitive support
 ***/

/* Vertex representation type */
typedef struct tagnd4VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Texture coordinates */
  VEC N;  /* Normal */
  VEC4 C; /* Color */
} nd4VERTEX;

/* Primitive topology type */
typedef enum tagnd4PRIM_TYPE
{
  ND4_PRIM_LINE,
  ND4_PRIM_TRISTRIP,
  ND4_PRIM_TRIMESH
} nd4PRIM_TYPE;

/* Primitive representation type */
typedef struct tagnd4PRIM
{
  nd4PRIM_TYPE Type; /* Primitive type */
  INT
    VA,              /* OpenGL vertex array identifier */
    VBuf,            /* OpenGL vertex buffer identifier */
    IBuf;            /* OpenGL index buffer identifier */
  INT NumOfElements; /* Number of vertices or indices */
  MATR Trans;        /* Additional transformation matrix */
} nd4PRIM;

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
                        nd4VERTEX *V, INT NoofV, INT *I, INT NoofI );
/* Delete primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 * RETURNS: None.
 */
VOID ND4_RndPrimFree( nd4PRIM *Pr );
/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID ND4_RndPrimDraw( nd4PRIM *Pr, MATR World );
/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       vg4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ND4_RndPrimLoad( nd4PRIM *Pr, CHAR *FileName );

/* Create sphere function.
 * ARGUMENTS:
 *   - primitive:
 *       nd4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS: None.
 */
BOOL ND4_RndPrimSphereCreate( nd4PRIM *Pr, FLT R, INT W, INT H );

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
UINT ND4_RndShaderLoad( CHAR *ShaderFileNamePrefix );

/* Unload shader program from memory files function.
 * ARGUMENTS:
 *   - shader program Id:
 *        INT ProgId;
 * RETURNS: None.
 */
VOID ND4_RndShaderFree( UINT ProgId );

#endif /* __RND_H_ */
/* END OF 'RND.H' FILE */