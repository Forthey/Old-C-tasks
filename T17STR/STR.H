/* Drekalov Nikita, 09-4, 29.10.2019 */
char * Load( char *FileName );
int LineNum( char *txt, int N );
int LatinChNum( char *txt, int N );
int CyrillicChNum( char *txt, int N);
int IsPalin( char *txt, int N );
int CountWord( char *txt, int (*F)( char *txt, int Start, int End ));
int SymmWordsNum( char *txt, int Start, int End );
int WordNum( char *txt, int Start, int End );
int NumSum( char *txt, int Start, int End );
double RealNumSum( char *txt, int Start, int End );
double CountWordR( char *txt, double (*F)( char *txt, int Start, int End ));