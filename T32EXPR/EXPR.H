/* Drekalov Nikita, 09-4, 25.11.2019 */
#include <commondf.h>

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

typedef double DBL;

#define MAX_NAME 10

typedef enum
{
  TOK_OP = 0,
  TOK_NUM = 1,
  TOK_NAME = 2,
  TOK_FUNC = 3
} TOKID;

typedef struct
{
  TOKID Id;
  CHAR Op;
  DBL Num;
  CHAR Name [MAX_NAME];
} TOK;

typedef struct tagLIST LIST;
struct tagLIST
{
  TOK T;
  LIST *Next;
};

typedef struct tagVARLIST VARLIST;

struct tagVARLIST
{
  CHAR Name[MAX_NAME];
  DBL Value;
  VARLIST *Next;
} *VarTable;

typedef struct tagFUNCLIST FUNCLIST;

struct tagFUNCLIST
{
  CHAR Name[MAX_NAME];
  FUNCLIST *Next;
} *FuncList;

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

VOID Put( QUEUE *Q, TOK T );
INT Get( QUEUE *Q, TOK *T );
INT Push( STACK *S, TOK T );
INT Pop( STACK *S, TOK *T );

VOID DisplayQueue( QUEUE *Q );
VOID ClearQueue( QUEUE *Q );
VOID ClearStack( STACK *StackEval );

VOID Scanner( QUEUE *Q, CHAR *S );

VOID ParserExpr( QUEUE *QRes, QUEUE *Q );

DBL Eval( QUEUE *Q );

VOID Error( CHAR *Str, ... );

DBL GetValue( CHAR *Name );
VOID SetValue( CHAR *Name, DBL Value );
VOID DisplayVarTable( VOID );
VOID ClearVarTable( VOID );

VOID InitFuncs( VOID );
VOID DisplayFunc( VOID );
INT FindFunc( CHAR *Name );

extern STACK StackEval;