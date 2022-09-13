/* Drekalov Nikita, 09-4, 15.11.2019 */
#include <commondf.h>

#define MAX 20

typedef struct tagLIST LIST;
struct tagLIST
{
  CHAR Str[MAX];
  LIST *Next, *Prev;
};

VOID GetStr( CHAR *Name, INT MaxLen );

VOID DisplayList( LIST *L );

INT ListAddToFront( LIST **L, CHAR *NewStr );
INT ListDelFromFront( LIST **L, CHAR *OldStr );
INT ListAddToEnd( LIST **L, CHAR *NewStr );
INT ListDelFromEnd( LIST **L, CHAR *OldStr );
