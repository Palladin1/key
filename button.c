#include  "button.h"

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
    BASE_T Counter_Ms;
    BUTTON_CONDITION_T Condition_Current;
    const BASE_T *Counter_Mark_Ms;    	
#if  (BUTTON_USE_LONG_PRESSED == 1)
    const BASE_T *Counter_Long_Mark_Ms;
#endif
//    BUTTON_CONDITION_T Condition_Previous;
	BOOL (* Pin_Chack) (void);
	void (* Pin_Init) (void);
} BUTTON_T;

extern enuum ButtonsId;
BUTTON_T *Buttons[ButtonsId];


ButtonsCallback(ButtonsId id);


#if  (BUTTON_USE_LONG_PRESSED == 1)
    const BASE_T *Counter_Long_Mark_Ms;
void ButtonsCreate (ButtonsId id, const BASE_T *counter_mark_ms, const BASE_T *counter_long_mark_ms, BOOL (* pin_chack) (void), void (* pin_init) (void)) 
{
    Buttons[id].Counter_Ms = 0;
	Buttons[id].Condition_Current = RELEASED;
	Buttons[id].Counter_Mark_Ms = counter_mark_ms;
    Buttons[id].Counter_Long_Mark_Ms = counter_long_mark_ms;
    Buttons[id].Pin_Chack = pin_chack;
	Buttons[id]->Pin_Init = pin_init; 
}	
#else
void ButtonsCreate (ButtonsId id, const BASE_T *counter_mark_ms, BOOL (* pin_chack) (void), void (* pin_init) (void)) 
{
    Buttons[id].Counter_Ms = 0;
	Buttons[id].Condition_Current = RELEASED;
	Buttons[id].Counter_Mark_Ms = counter_mark_ms;
    Buttons[id].Pin_Chack = pin_chack;
	Buttons[id]->Pin_Init = pin_init;  
}
#endif


void ButtonsInit (void) 
{
    u08 buttons_number;

    for (buttons_number = 0; buttons_number < sizeof(Buttons[ButtonsId]) / sizeof(Buttons[0]); buttons_number++) {
	    Buttons[buttons_number]->Pin_Init; 
	}	
}


void ButtonsPolling (BASE_T timer_period_ms)
{
    u08 buttons_number;

    for (buttons_number = 0; buttons_number < sizeof(Buttons[ButtonsId]) / sizeof(Buttons[0]); buttons_number++) {
	    if (Buttons[buttons_number]->Pin_Chack == 1) {
		    if (Buttons[buttons_number].Counter >= Buttons[buttons_number].Counter_Mark) {
			    if (Buttons[buttons_number].Condition_Current != PRESSED) {
				    Buttons[buttons_number].Condition_Current = PRESSED;
					
					#if  (BUTTON_CALLBACK == 1) 
					ButtonsCallback(buttons_number);
					#endif
				}
			} else {
			    Buttons[buttons_number].Counter += timer_period_ms;
			}
		} else {
		    if (Buttons[buttons_number].Counter == 0) {
			    if (Buttons[buttons_number].Condition_Current != RELEASED) {
			        Buttons[buttons_number].Condition_Current = RELEASED;
					
					#if  (BUTTON_CALLBACK == 1) 
					ButtonsCallback(buttons_number);
					#endif
				}
			} else {
			    Buttons[buttons_number].Counter -= timer_period_ms;
			}
		}
	}
}


BUTTON_STATE_T ButtonStateGet (ButtonsId id)
{
    return Buttons[id].Condition_Current;
}


