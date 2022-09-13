/* Drekalov Nikita, 09-4, 18.11.2019 */

#include <commondf.h>

/* Debug memory allocation support */
#ifndef NDEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((void)0)
#endif /* _DEBUG */
#include <stdlib.h>

#define MAX_STR 111

typedef struct tagTREE TREE;

struct tagTREE
{
  CHAR Text[MAX_STR];
  TREE *Yes, *No;
};

INT SaveTree( CHAR *FileName, TREE *T );
INT LoadTree( CHAR *FileName, TREE **T );
VOID Session( TREE **T );
TREE * Init( CHAR *Text, TREE *N, TREE *Y);
VOID DrawTree( TREE *T );
