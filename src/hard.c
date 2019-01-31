//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F030
// ##
// #### HARD.C ################################
//---------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "hard.h"
#include "tim.h"
#include "stm32f0xx.h"
#include "adc.h"
#include "dsp.h"

#include <stdio.h>
#include "uart.h"

/* Externals variables ---------------------------------------------------------*/
extern volatile unsigned short timer_led;
extern volatile unsigned short adc_ch[];




/* Global variables ------------------------------------------------------------*/
//para el led
led_state_t led_state = START_BLINKING;
unsigned char blink = 0;
unsigned char how_many_blinks = 0;



/* Module Functions ------------------------------------------------------------*/


//cambia configuracion de bips del LED1
void ChangeLed (unsigned char how_many)
{
    how_many_blinks = how_many;
    led_state = START_BLINKING;
}

//mueve el LED1 segun el estado del Pote
void UpdateLed (void)
{
    switch (led_state)
    {
        case START_BLINKING:
            blink = how_many_blinks;
            
            if (blink)
            {
                LED1_ON;
                timer_led = 200;
                led_state++;
                blink--;
            }
            break;

        case WAIT_TO_OFF:
            if (!timer_led)
            {
                LED1_OFF;
                timer_led = 200;
                led_state++;
            }
            break;

        case WAIT_TO_ON:
            if (!timer_led)
            {
                if (blink)
                {
                    blink--;
                    timer_led = 200;
                    led_state = WAIT_TO_OFF;
                    LED1_ON;
                }
                else
                {
                    led_state = WAIT_NEW_CYCLE;
                    timer_led = 2000;
                }
            }
            break;

        case WAIT_NEW_CYCLE:
            if (!timer_led)
                led_state = START_BLINKING;

            break;

        default:
            led_state = START_BLINKING;
            break;
    }
}

void WelcomeCodeFeatures (char * str)
{
#ifdef USE_FORWARD_MODE
    sprintf(str,"[%s] %s\n", __FILE__, str_macro(USE_FORWARD_MODE));
    Usart1Send(str);
    Wait_ms(30);    
#endif

#ifdef USE_PUSH_PULL_MODE
    sprintf(str,"[%s] %s\n", __FILE__, str_macro(USE_PUSH_PULL_MODE));
    Usart1Send(str);
    Wait_ms(30);    
#endif

#ifdef WITH_OVERCURRENT_SHUTDOWN
    sprintf(str,"[%s] %s\n", __FILE__, str_macro(WITH_OVERCURRENT_SHUTDOWN));
    Usart1Send(str);
    Wait_ms(30);    
#endif

#ifdef WITH_TIM14_FB
    sprintf(str,"[%s] %s\n", __FILE__, str_macro(WITH_TIM14_FB));
    Usart1Send(str);
    Wait_ms(30);    
#endif
#ifdef WITH_TIM1_FB
    sprintf(str,"[%s] %s\n", __FILE__, str_macro(WITH_TIM1_FB));
    Usart1Send(str);
    Wait_ms(30);    
#endif

}

//---- end of file ----//
