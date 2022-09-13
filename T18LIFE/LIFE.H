/* Drekalov Nikita, 09-4, 30.10.2019 */
typedef unsigned char byte;

/* Field initialize */
void LifeInit( void );
/* Field common step */
void LifeStep( void );
/* Put pixel on display */
void PutPix( int X, int Y, int R, int G, int B );
/* Random fill */
void RandInjection( void );
/* Create 4 sticks */
void SticksInjection( int x, int y );
/* Clear field */
void FieldClear( void );
/* Create random directed runner */
void RunnersInjection( int x, int y );
/* Create static figue (barrel) */
void BarrelInjection( int x, int y );
/* Global random fill */
void FillRand( void );
/* Create animation. Last - 12 sticks */
void BurstInjection( int x, int y );