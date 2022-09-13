/* Drekalov Nikita, 09-4, 14.10.2019 */
typedef double DBL;

void FillRand( DBL *A, int N );
void FillIncr( DBL *A, int N );
void FillDecr( DBL *A, int N );
void FillEq( DBL *A, int N );
void FillMostly( DBL *A, int N);
void FillStep( DBL *A, int N );

void OutMas( DBL *A, int N );

void Swap( DBL *A, DBL *B );

int CheckSort( DBL *A, int N );

void BubbleSort1( DBL *A, int N );
void BubbleSort2( DBL *A, int N );
void BubbleSort3( DBL *A, int N );
void BubbleSort4( DBL *A, int N );
void InsertionSort( DBL *A, int N );
void SelectionSort( DBL *A, int N );

void MergeSort( DBL *A, int N );
void QuickSort( DBL *A, int N );
void HeapSort( DBL *A, int N );