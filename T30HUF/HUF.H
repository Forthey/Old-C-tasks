/* Drekalov Nikita, 09-4, 20.11.2019 */
typedef struct tagTREE TREE;

struct tagTREE
{
  CHAR Ch;
  LONG Freq;
  TREE *Left, *Right;
};