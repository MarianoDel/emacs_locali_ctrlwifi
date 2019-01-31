//-----------------------------------------------------
// #### PROYECTO LOCALIZART F030 - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F030
// ##
// #### MAIN.C ########################################
//-----------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gpio.h"
#include "tim.h"
#include "uart.h"
#include "hard.h"

#include "core_cm0.h"
#include "adc.h"
#include "dma.h"
#include "flash_program.h"
#include "dsp.h"

#include "it.h"



//--- VARIABLES EXTERNAS ---//


// ------- Externals del Puerto serie  -------
volatile unsigned char tx1buff[SIZEOF_DATA];
volatile unsigned char rx1buff[SIZEOF_DATA];
volatile unsigned char usart1_have_data = 0;

// ------- Externals del o para el ADC -------
volatile unsigned short adc_ch[ADC_CHANNEL_QUANTITY];
volatile unsigned char seq_ready = 0;


// ------- Externals para timers -------
volatile unsigned short timer_led = 0;


// ------- Externals para filtros -------
volatile unsigned short take_temp_sample = 0;

//--- Module Globals ---------------------------------------

// ------- de los timers -------
volatile unsigned short wait_ms_var = 0;
volatile unsigned short timer_standby;
volatile unsigned short secs = 0;
volatile unsigned char hours = 0;
volatile unsigned char minutes = 0;






//--- Private Module Functions ------------------------------
void TimingDelay_Decrement (void);


//--- Private Definitions ---//


//-------------------------------------------//
// @brief  Main program.
// @param  None
// @retval None
//------------------------------------------//
int main(void)
{
    unsigned char i;
    unsigned short ii;

    main_state_t main_state = MAIN_INIT;
    
    char s_lcd [120];		

    //GPIO Configuration.
    GPIO_Config();

    //ACTIVAR SYSTICK TIMER
    if (SysTick_Config(48000))
    {
        while (1)	/* Capture error */
        {
            if (LED1)
                LED1_OFF;
            else
                LED1_ON;

            for (i = 0; i < 255; i++)
            {
                asm (	"nop \n\t"
                        "nop \n\t"
                        "nop \n\t" );
            }
        }
    }

    //--- Leo los parametros de memoria ---//

    // while (1)
    // {
    //  if (STOP_JUMPER)
    //  {
    //  	LED_OFF;
    //  }
    //  else
    //  {
    // 	  if (LED)
    // 	  	LED_OFF;
    // 	  else
    // 	  	LED_ON;
    //
    // 	  Wait_ms (250);
    //  }
    // }


//---------- Pruebas de Hardware --------//
    // EXTIOff ();
    USART1Config();
    
    //---- Welcome Code ------------//
    //---- Defines from hard.h -----//
#ifdef HARD
    Usart1Send((char *) HARD);
    Wait_ms(100);
#else
#error	"No Hardware defined in hard.h file"
#endif

#ifdef SOFT
    Usart1Send((char *) SOFT);
    Wait_ms(100);
#else
#error	"No Soft Version defined in hard.h file"
#endif

#ifdef FEATURES
    WelcomeCodeFeatures(s_lcd);
#endif
    
//---------- Versiones 1_2 y 2_0  --------//    
#if (defined VER_2_0)
    
    TIM_1_Init ();	   //lo utilizo para mosfet Ctrol_M_B y para FB si esta definido en hard.h
    TIM_3_Init ();	   //lo utilizo para mosfet Ctrol_M_A y para synchro ADC

    EnablePreload_MosfetA;
    EnablePreload_MosfetB;

#ifdef WITH_TIM14_FB
    TIM_14_Init ();        //lo uso para FB
#endif
    

    AdcConfig();

    //-- DMA configuration.
    DMAConfig();
    DMA1_Channel1->CCR |= DMA_CCR_EN;

    ADC1->CR |= ADC_CR_ADSTART;

    //--- Prueba HARD pin FB ----------
    // //probar con WITH_TIM14_FB y WITH_TIM1_FB
    // while (1)
    // {
    //     for (ii = 0; ii < DUTY_100_PERCENT; ii++)
    //     {
    //         UpdateFB(ii);
    //         Wait_ms(1);
    //     }
    //     for (ii = DUTY_100_PERCENT; ii > 0; ii--)
    //     {
    //         UpdateFB(ii);
    //         Wait_ms(1);
    //     }
    // }
    //--- Fin Prueba HARD pin FB ----------

    //--- Prueba HARD pines CTRL_MOSFET ----------
    //pruebo seniales gate, el defasaje de las mismas y los flancos de I_Sense
    // UpdateTIMSync (DUTY_FOR_DMAX);
    // UpdateTIMSync (DUTY_10_PERCENT);    
    // while (1);
    //--- Fin Prueba HARD pines CTRL_MOSFET ----------

    //--- Prueba HARD pines ADC ----------
    // while (1)
    // {
    //     if (!timer_standby)
    //     {
    //         timer_standby = 2000;
    //         sprintf (s_lcd, "Vin: %d, Vout: %d, I: %d\n",
    //                  Vin_Sense,
    //                  Vout_Sense,
    //                  I_Sense);
            
    //         Usart1Send(s_lcd);
    //     }
    // }   
    //--- Fin Prueba HARD pines ADC ----------

    //--- Prueba tension de salida con max d fijo ----------
    //este loop trabaja en voltage-mode
    // while (1)
    // {
    //     if (sequence_ready)
    //     {
    //         sequence_ready_reset;
                
    //         if (undersampling < (UNDERSAMPLING_TICKS - 1))
    //         {
    //             undersampling++;
    //         }
    //         else
    //         {
    //             undersampling = 0;
    //             d = PID_roof (VOUT_110V, Vout_Sense, d, &ez1, &ez2);
                    
    //             if (d < 0)
    //             {
    //                 d = 0;
    //                 ez1 = 0;
    //                 ez2 = 0;
    //             }

    //             if (d > DUTY_5_PERCENT)
    //                 d = DUTY_5_PERCENT;

    //             UpdateTIMSync (d);
    //         }
    //     }

    //     if (!timer_standby)
    //     {
    //         timer_standby = 2000;
    //         sprintf (s_lcd, "Vin: %d, Vout: %d, I: %d, d: %d\n",
    //                  Vin_Sense,
    //                  Vout_Sense,
    //                  I_Sense,
    //                  d);
            
    //         Usart1Send(s_lcd);
    //     }

    // }
    //--- Fin Prueba tension de salida con max d fijo ----------
    
#endif    //ver 2.0
//---------- Fin VER_2_0 --------//

    return 0;
}

//--- End of Main ---//


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

    if (timer_led)
        timer_led--;

    // //cuenta de a 1 minuto
    // if (secs > 59999)	//pasaron 1 min
    // {
    // 	minutes++;
    // 	secs = 0;
    // }
    // else
    // 	secs++;
    //
    // if (minutes > 60)
    // {
    // 	hours++;
    // 	minutes = 0;
    // }


}


//--- end of file ---//
