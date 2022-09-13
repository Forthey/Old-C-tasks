/* FILE NAME  : RNDSHD.C
 * PROGRAMMER : ND4
 * LAST UPDATE: 09.01.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Render subsystem implementation module.
 *              Shader handle functions.
 */

#include <stdio.h>

#include "rnd.h"

/***
 * Shaders handle functions
 ***/

/* Text file load to memory function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text or NULL if error is occured.
 */
static CHAR * ND4_RndShaderLoadTextFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *text;

  if ((F = fopen(FileName, "r")) == NULL)
    return NULL;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((text = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(text, 0, flen + 1);

  /* Read text */
  fseek(F, 0, SEEK_SET);
  fread(text, 1, flen, F);

  fclose(F);
  return text;
} /* End of 'ND4_RndShaderLoadTextFile' function */

/* Save text to log file function.
 * ARGUMENTS:
 *   - shader file name:
 *       CHAR *FileName;
 *   - text 1 to save:
 *       CHAR *Stage;
 *   - text 2 to save:
 *       CHAR *Text;
 * RETURNS: None.
 */
static VOID ND4_RndShaderLog( CHAR *FileName, CHAR *Stage, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("ND4{SHAD}30.LOG", "a")) != NULL)
  {
    fprintf(F, "%s\n  %s: %s\n", FileName, Stage, Text);
    fclose(F);
  }
} /* End of 'ND4_RndShaderLog' function */

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT ND4_RndShaderLoad( CHAR *FileNamePrefix )
{
  INT
    i, res,
    shd_type[] =
    {
      GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
      GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
    };
  CHAR *suff[] = {"VERT", "CTRL", "EVAL", "GEOM", "FRAG"};
  INT NS = sizeof(suff) / sizeof(suff[0]);
  UINT prg = 0, shd[sizeof(suff) / sizeof(suff[0])] = {0};
  BOOL isok = TRUE;
  CHAR *txt;
  static CHAR buf[1000];

  /* Load shaders */
  for (i = 0; isok && i < NS; i++)
  {
    /* Load text file */
    sprintf(buf, "%s\\%s.glsl", FileNamePrefix, suff[i]);
    if ((txt = ND4_RndShaderLoadTextFile(buf)) == NULL)
      continue;
    /* Create shader */
    if ((shd[i] = glCreateShader(shd_type[i])) == 0)
    {
      free(txt);
      ND4_RndShaderLog(FileNamePrefix, suff[i], "Error create shader");
      isok = FALSE;
      break;
    }
    /* Attach text to shader  */
    glShaderSource(shd[i], 1, &txt, NULL);
    free(txt);
    /* Compile shader */
    glCompileShader(shd[i]);
    glGetShaderiv(shd[i], GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i], sizeof(buf), &res, buf);
      ND4_RndShaderLog(FileNamePrefix, suff[i], buf);
      isok = FALSE;
      break;
    }
  }

  /* Create program */
  if (isok)
    if ((prg = glCreateProgram()) == 0)
      isok = FALSE;
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NS; i++)
        if (shd[i] != 0)
          glAttachShader(prg, shd[i]);
      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(shd[i], GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(buf), &res, buf);
        ND4_RndShaderLog(FileNamePrefix, "LINK", buf);
        isok = FALSE;
      }
    }

  /* Error handle */
  if (!isok)
  {
    for (i = 0; i < NS; i++)
      if (shd[i] != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i]);
        glDeleteShader(shd[i]);
      }
    if (prg != 0)
      glDeleteProgram(prg);
    return 0;
  }
  return prg;
} /* End of 'ND4_RndShaderLoad' function */

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT Prg;
 * RETURNS: None.
 */
VOID ND4_RndShaderFree( UINT Prg )
{
  UINT i, n, shds[5];

  if (Prg == 0)
    return;
  /* Obtain program shaders count */
  glGetAttachedShaders(Prg, 5, &n, shds);
  for (i = 0; i < n; i++)
  {
    glDetachShader(Prg, shds[i]);
    glDeleteShader(shds[i]);
  }
  glDeleteProgram(Prg);
} /* End of 'ND4_RndShaderFree' function */

/* END OF 'RNDSHD.C' FILE */
