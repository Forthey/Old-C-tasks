/* Drekalov Nikita, 09-4, 11.11.2019 */

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


typedef struct tagLIST LIST;

struct tagLIST
{
  INT Data;
  LIST *Next;
};

VOID Display( LIST *L );
INT ListAddToFront( LIST **L, INT NewData );
INT ListDelFromFront( LIST **L );
INT ListAddToBack( LIST **L, INT NewData );
INT ListDelFromBack( LIST **L );
INT ListAddToArb( LIST **L, INT NewData, INT Pos );