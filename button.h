#ifndef  BUTTON_H
#define  BUTTON_H

#include  "types.h"


#define  BUTTON_LONG_PRESSED     0                            /* If to use should to set 1 */
#define  BUTTON_CALLBACK         0
//#define  USE_LONG_RELEASED    0                            /* If to use should to set 1 */   


typedef  enun {
    RELEASED,
	PRESSED,
#if  (BUTTON_LONG_PRESSED == 1)
    LONG_PRESSED,
#endif
//#if  (USE_LONG_RELEASED == 1)
//    LONG_RELEASED,
//#endif
} BUTTON_STATE_T;


typedef  struct {
    BASE_T Counter;
    BUTTON_CONDITION_T Condition_Current;
    const BASE_T *Counter_Mark;    	
#if  (BUTTON_USE_LONG_PRESSED == 1)
    const BASE_T *Counter_Long_Mark;
#endif
    BUTTON_CONDITION_T Condition_Previous;
	BOOL (* Pin_Chack) (void);
	void (* Pin_Init) (void);
} BUTTON_T;


#endif  /* BUTTON_H */