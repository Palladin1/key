#include  "button.h"


extern void ButtonsCallback(BASE_T id, BUTTON_CONDITION_T state);

extern BUTTON_T Buttons[];


void ButtonsCreate (BASE_T id, const BASE_T *counter_mark_ms, const BASE_T *counter_long_mark_ms, BOOL (* pin_chack) (void), void (* pin_init) (void)) 
{
    Buttons[id].Counter_Ms = 0;
	Buttons[id].Condition_Current = RELEASED;
	Buttons[id].Counter_Mark_Ms = counter_mark_ms;

	#if  (BUTTON_USE_LONG_PRESSED == 1)
    Buttons[id].Counter_Long_Mark_Ms = counter_long_mark_ms;
	#endif

    Buttons[id].Pin_Chack = pin_chack;
    Buttons[id].Pin_Init = pin_init; 
}	

/*
void ButtonsInit (void) 
{
    u8 buttons_number;

    for (buttons_number = 0; buttons_number < (sizeof Buttons / sizeof Buttons[0]); buttons_number++) {
        Buttons[buttons_number].Pin_Init();
	}	
}
*/

void ButtonsPolling (BASE_T timer_period_ms)
{
    u8 buttons_number;

    for (buttons_number = 0; buttons_number < sizeof(Buttons[2]) / sizeof(Buttons[0]); buttons_number++) {
	    if (Buttons[buttons_number].Pin_Chack() == 1) {
		    if (Buttons[buttons_number].Counter_Ms >= *(Buttons[buttons_number].Counter_Mark_Ms)) {
			    if (Buttons[buttons_number].Condition_Current != PRESSED) {
				    Buttons[buttons_number].Condition_Current = PRESSED;
					
					#if  (BUTTON_CALLBACK == 1) 
					ButtonsCallback(buttons_number, PRESSED);
					#endif
				}
			} else {
			    Buttons[buttons_number].Counter_Ms += timer_period_ms;
			}
		} else {
		    if (Buttons[buttons_number].Counter_Ms == 0) {
			    if (Buttons[buttons_number].Condition_Current != RELEASED) {
			        Buttons[buttons_number].Condition_Current = RELEASED;
					
					#if  (BUTTON_CALLBACK == 1) 
					ButtonsCallback(buttons_number, RELEASED);
					#endif
				}
			} else {
			    Buttons[buttons_number].Counter_Ms -= timer_period_ms;
			}
		}
	}
	
}


BUTTON_CONDITION_T ButtonStateGet (BASE_T id)
{
    return Buttons[id].Condition_Current;
}


