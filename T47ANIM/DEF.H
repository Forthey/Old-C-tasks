/* FILE NAME: DEF.H
 * PROGRAMMER: ND4
 * LAST UPDATE: 07.01.2020
 * PURPOSE: memory leak detect.
 */
#ifndef __DEF_H_
#define __DEF_H_

#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((VOID)0)
#endif /* _DEBUG */
#include <stdlib.h>
#include "mth/mth.h"

#endif /* __DEF_H_ */
/* END OF 'DEF.H' FILE */