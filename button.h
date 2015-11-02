/*
 ******************************************************************************
 *
 *
 ******************************************************************************
*/
#ifndef  BUTTON_H
#define  BUTTON_H


#include  "uKernel/types.h"


#define  BUTTON_LONG_PRESSED     0                            /* If to use should to set 1 */
#define  BUTTON_CALLBACK         0
//#define  USE_LONG_RELEASED    0                            /* If to use should to set 1 */   

enum BUTTON_CONDITION {
    RELEASED,  
	PRESSED,
#if  (BUTTON_LONG_PRESSED == 1)
    LONG_PRESSED,
#endif
//#if  (USE_LONG_RELEASED == 1)
//    LONG_RELEASED,
//#endif
};

typedef  enum BUTTON_CONDITION BUTTON_CONDITION_T;


typedef  struct {
    BASE_T Counter_Ms;
    BUTTON_CONDITION_T Condition_Current;
    const BASE_T *Counter_Mark_Ms;    	
#if  (BUTTON_USE_LONG_PRESSED == 1)
    const BASE_T *Counter_Long_Mark_Ms;
#endif
    BUTTON_CONDITION_T Condition_Previous;
	BOOL (* Pin_Chack) (void);
	void (* Pin_Init) (void);
} BUTTON_T;


void ButtonsCreate (BASE_T id, const BASE_T *counter_mark_ms, const BASE_T *counter_long_mark_ms, BOOL (* pin_chack) (void), void (* pin_init) (void));
void ButtonsInit (void);
void ButtonsPolling (BASE_T timer_period_ms);
BUTTON_CONDITION_T ButtonStateGet (BASE_T id);


#endif  /* BUTTON_H */
