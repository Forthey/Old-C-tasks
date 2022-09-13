/* Drekalov Nikita, 09-4, 29.10.2019 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include "str.h"


void main( void )
{
  char *txt = Load("X:\\TXT\\orwell.txt");
  int n = 0;

  if (txt == NULL)
    return;

  while (txt[n] != 0)
    n++;

  setlocale(LC_ALL, "Russian");

  printf("Number of lines: %i\n", LineNum(txt, n));
  printf("Number of latin characters: %i\n", LatinChNum(txt, n));
  printf("Number of cyrillic characters: %i\n", CyrillicChNum(txt, n));
  printf("%s\n", IsPalin(txt, n) ? "Text is palindrome" : "Text is not palindrome");
  printf("Number of words in the text: %i\n", CountWord(txt, WordNum));
  printf("Number of symmetric words: %i\n", CountWord(txt, SymmWordsNum));
  printf("The sum of all numbers from the digits in the word: %i\n", CountWord(txt, NumSum));
  printf("The sum of all real numbers from the digits in the word: %f\n", CountWordR(txt, RealNumSum));

  _getch();
}