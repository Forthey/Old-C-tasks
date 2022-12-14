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

/* Enumerate IDs */
typedef enum
{
  TOK_OP = 0,
  TOK_NUM = 1,
  TOK_NAME = 2,
  TOK_KEYW,
  TOK_SYMBOL /* for ',' '{' '}' */
} TOKID;

#define TOK_OP_ADD_EQ 300

/* Enumerate operands */
typedef enum
{
  OP_PLUS = '+',
  OP_MINUS = '-',
  OP_MULT = '*',
  OP_DEL = '/',
  OP_MOD = '%',
  OP_POW = '^',
  OP_SKOP = '(',
  OP_SKCL = ')',
  OP_FSKOP = '{',
  OP_FSKCL = '}',
  OP_PR = '=',
  OP_ZAP = ',',
  OP_END = ';',
  OP_LT = '<',
  OP_GT = '>',
  OP_EQ = '=' + TOK_OP_ADD_EQ,
  OP_NE = '!' + TOK_OP_ADD_EQ,
  OP_GE = '>' + TOK_OP_ADD_EQ,
  OP_LE = '<' + TOK_OP_ADD_EQ
} OPERS;

/* Enumerate keywords */
typedef enum
{
  KW_IF, KW_ELSE, KW_WHILE
} KEYWORD;

/* Tokens */
typedef struct
{
  TOKID Id;
  OPERS Op;
  DBL Num;
  CHAR Name [MAX_NAME];
  KEYWORD KeyW;
} TOK;

typedef struct tagLIST LIST;
struct tagLIST
{
  TOK T;
  LIST *Next;
};

typedef enum
{
  CMD_EXPR, CMD_IF, CMD_WHILE
} CMDID;

typedef struct tagCMD CMD;
struct tagCMD
{
  CMDID Id;   /* ID of command */
  LIST *Expr; /* Expression for CMD_EXPR, 'if' for CMD_IF, CMD_WHILE */
  CMD
    *C1,      /* CMD_IF - 1st command, command CMD_WHILE */
    *C2,      /* CMD_IF 2nd command, NULL if hadn't 'else' */
    *Next;    /* On next command */
};

/* List of variables */
typedef struct tagVARLIST VARLIST;
struct tagVARLIST
{
  CHAR Name[MAX_NAME];
  DBL Value;
  VARLIST *Next;
} *VarTable;

/* Queue */
typedef struct
{
  LIST
    *Head, 
    *Tail; 
} QUEUE;

/* Stack */
typedef struct
{
  LIST *Top;
} STACK;

/* Add to queue tail */
VOID Put( QUEUE *Q, TOK T );
/* Get from queue head */
INT Get( QUEUE *Q, TOK *T );
/* Add to stack top */
INT Push( STACK *S, TOK T );
/* Get from stack top */
INT Pop( STACK *S, TOK *T );

VOID DisplayQueue( QUEUE *Q );
VOID ClearQueue( QUEUE *Q );
VOID ClearStack( STACK *StackEval );

/* Scanning tokens */
VOID Scanner( CHAR *S );

VOID ParseExpr( LIST **Expr );

DBL Eval( LIST *Expr );

VOID Error( CHAR *Str, ... );

DBL GetValue( CHAR *Name );
VOID SetValue( CHAR *Name, DBL Value );
VOID DisplayVarTable( VOID );
VOID ClearVarTable( VOID );

VOID ParseProgram( VOID );
VOID DoCmd( CMD *C );

extern STACK StackEval;
extern QUEUE TokList;
extern TOK TokCurrent;
extern CMD *Proga;

