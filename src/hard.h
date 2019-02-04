//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F030
// ##
// #### HARD.H ################################
//---------------------------------------------
#ifndef _HARD_H_
#define _HARD_H_

//----------- Defines For Configuration -------------
//----------- Hardware Board Version -------------
#define VER_1_0    //primer version


//---- Configuration for Hardware Versions -------
#ifdef VER_1_0
#define HARDWARE_VERSION_1_0
#define SOFTWARE_VERSION_1_0
#endif


//---- Features Configuration ----------------
//features activated here and annouced in hard.c
#define FEATURES
#define USE_HW_WATCHDOG

//---- End of Features Configuration ----------

//--- Stringtify Utils -----------------------
#define STRING_CONCAT(str1,str2) #str1 " " #str2
#define STRING_CONCAT_NEW_LINE(str1,str2) xstr(str1) #str2 "\n"
#define xstr_macro(s) str_macro(s)
#define str_macro(s) #s

//--- Hardware Welcome Code ------------------//
#ifdef HARDWARE_VERSION_1_0
#define HARD "Hardware V: 1.0\n"
#endif

//--- Software Welcome Code ------------------//
#ifdef SOFTWARE_VERSION_1_0
#define SOFT "Software V: 1.0\n"
#endif

//-------- End Of Defines For Configuration ------


//------- PIN CONFIG ----------------------
#ifdef VER_1_0
//GPIOA pin0	NC

//GPIOA pin1
#define RELAY_MOTOR ((GPIOA->ODR & 0x0002) != 0)
#define RELAY_MOTOR_ON	GPIOA->BSRR = 0x00000002
#define RELAY_MOTOR_OFF GPIOA->BSRR = 0x00020000

//GPIOA pin2	
#define RELAY_LIGHT ((GPIOA->ODR & 0x0004) != 0)
#define RELAY_LIGHT_ON	GPIOA->BSRR = 0x00000004
#define RELAY_LIGHT_OFF GPIOA->BSRR = 0x00040000

//GPIOA pin3
#define JUMPER_DEFAULT    ((GPIOA->IDR & 0x0008) == 0)
#define J2    JUMPER_DEFAULT

//GPIOA pin4
//GPIOA pin5
//GPIOA pin6
//GPIOA pin7

//GPIOB pin0
#define LED1 ((GPIOB->ODR & 0x0001) != 0)
#define LED1_ON	GPIOB->BSRR = 0x00000001
#define LED1_OFF GPIOB->BSRR = 0x00010000

//GPIOB pin1
#define LED2 ((GPIOB->ODR & 0x0002) != 0)
#define LED2_ON	GPIOB->BSRR = 0x00000002
#define LED2_OFF GPIOB->BSRR = 0x00020000

//GPIOA pin8

//GPIOA pin9
//GPIOA pin10	usart1 tx rx

//GPIOA pin11
#define TACT    ((GPIOA->IDR & 0x0800) == 0)

//GPIOA pin12
#define J_PROG_WIFI    ((GPIOA->IDR & 0x1000) == 0)
#define J1    J_PROG_WIFI

//GPIOA pin13	NC
//GPIOA pin14	NC
//GPIOA pin15   NC

//GPIOB pin3	NC
//GPIOB pin4	NC
//GPIOB pin5	NC

//GPIOB pin6    NC
//GPIOB pin7	NC

#endif	//VER_1_0


//------- END OF PIN CONFIG -------------------



//ESTADOS DEL PROGRAMA PRINCIPAL
typedef enum
{
    MAIN_INIT = 0,
    MAIN_WAIT_CONN,
    MAIN_WELCOME_CODE,
    MAIN_DEBUG_WIFI,
    MAINS_FAILURE

} main_state_t;

//ESTADOS DEL LED
typedef enum
{    
    START_BLINKING = 0,
    WAIT_TO_OFF,
    WAIT_TO_ON,
    WAIT_NEW_CYCLE
} led_state_t;


//Estados Externos de LED BLINKING
#define LED_NO_BLINKING               0
#define LED_STANDBY                   1
#define LED_GENERATING                2
#define LED_LOW_VOLTAGE               3
#define LED_PROTECTED                 4
#define LED_DEBUGGING                 5


#define SIZEOF_DATA1	512
#define SIZEOF_DATA		256
#define SIZEOF_DATA512	SIZEOF_DATA1
#define SIZEOF_DATA256	SIZEOF_DATA
#define SIZEOF_BUFFTCP	SIZEOF_DATA





/* Module Functions ------------------------------------------------------------*/
void ChangeLed (unsigned char);
void UpdateLed (void);
void WelcomeCodeFeatures (char *);
    
#endif /* _HARD_H_ */
