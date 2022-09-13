/* Drekalov Nikita, 09-4, 15.11.2019 */

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

typedef struct tagTREE TREE;

struct tagTREE
{
  INT Key;
  TREE *Less, *More;
};

INT AccessTree( TREE **T, INT Key );
INT AccessTree1( TREE **T, INT Key );
VOID DrawTree( TREE *T );
VOID PutTree( TREE *T );
VOID PutTree2( TREE *T );
VOID ClearTree( TREE **T );
INT DeleteKey( TREE **T, INT Key );
VOID BalanceTree( TREE **T, INT N );
INT Linearize( TREE **T );