/* Drekalov Nikita, 09-4, 25.11.2019 */
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
  int Data;
  LIST *Next;
};
 
typedef struct
{
  LIST
    *Head, 
    *Tail; 
} QUEUE;

typedef struct
{
  LIST *Top;
} STACK;

INT Put( QUEUE *Q, INT NewData );
INT Get( QUEUE *Q, INT *OldData );
INT Push( STACK *S, INT NewData );
INT Pop( STACK *S, INT *OldData );

VOID DisplayQueue( QUEUE *Q );
VOID DisplayStack( STACK *S );
VOID ClearQueue( QUEUE *Q );