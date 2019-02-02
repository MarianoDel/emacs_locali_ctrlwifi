//---------------------------------------------
// #### PROYECTO LOCALIZART - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### COMM.C ################################
//---------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "comm.h"
#include "uart.h"
#include "hard.h"

// #include "utils.h"

#include <string.h>
// #include <stdio.h>



// External Variables ------------------------------
//--- del main
extern const char s_ok [];
extern unsigned char receiv_cmd;

//--- Externals del Puerto serie  -------
extern unsigned char usart1_have_data;

// Module Globals ---------------------------------
char buffMessages [100];

//--- Fixed Messages ---
const char s_command [] = {"command:"};
const char s_open [] = {"OPEN"};
const char s_close [] = {"CLOSE"};
const char s_light_on [] = {"LIGHT-ON"};
const char s_light_off [] = {"LIGHT-OFF"};

// Module Private Functions ------------------------------
unsigned char SerialProcess (void);
unsigned char InterpretarMsg (void);


// Module Functions -------------------------------
void UpdateCommunications (void)
{
    if (SerialProcess() > 2)	//si tiene algun dato significativo
        InterpretarMsg();
}

//Procesa consultas desde el puerto serie
//carga el buffer buffMessages y contesta la cantidad de bytes copiados
unsigned char SerialProcess (void)
{
    unsigned char bytes_readed = 0;

    if (usart1_have_data)
    {
        usart1_have_data = 0;
        bytes_readed = ReadUsart1Buffer((unsigned char *) buffMessages, sizeof(buffMessages));
    }
    return bytes_readed;
}

resp_t InterpretarMsg (void)
{
    resp_t resp = resp_ok;
    char * pStr = buffMessages;

    //reviso si son comandos
    // Usart1Send(buffMessages);
    if (strncmp(pStr, s_command, sizeof(s_command) - 1) == 0)
    {
        resp = resp_ok;
        pStr += sizeof(s_command);	//normalizo al mensaje, hay un espacio

        //-- Comandos comunes
        if (strncmp(pStr, s_open, sizeof(s_open) - 1) == 0)
            receiv_cmd |= CMD_OPEN;
            
        else if (strncmp(pStr, s_close, sizeof(s_close) - 1) == 0)
            receiv_cmd |= CMD_CLOSE;

        else if (strncmp(pStr, s_light_on, sizeof(s_light_on) - 1) == 0)
            receiv_cmd |= CMD_LIGHT_ON;

        else if (strncmp(pStr, s_light_off, sizeof(s_light_off) - 1) == 0)
            receiv_cmd |= CMD_LIGHT_OFF;
        
        
        //-- Frequency Setting
        // else if (strncmp(pStr, s_frequency, sizeof(s_frequency) - 1) == 0)
        // {
        //     pStr += sizeof(s_frequency);		//normalizo al payload, hay un espacio

        //     //lo que viene es un byte de 0 a 9 (0 es 10Hz)
        //     decimales = StringIsANumber(pStr, &new_power);
        //     if (decimales == 1)
        //     {
        //         resp = SetFrequency (new_power);
        //         // sprintf(b, "dec: %d, freq: %d\n", decimales, new_power);
        //         // Usart1Send(b);
        //     }
        //     else
        //         resp = resp_error;

        // }

        //-- Status
        // else if (strncmp(pStr, s_status, sizeof(s_status) - 1) == 0)
        // {
        //     switch (GetErrorStatus())
        //     {
        //     case ERROR_OK:
        //         sprintf(b, "Manager status: %d\n", GetTreatmentState());
        //         Usart1Send(b);
        //         break;

        //     case ERROR_OVERCURRENT:
        //         Usart1Send("Error: Overcurrent\n");
        //         break;

        //     case ERROR_NO_CURRENT:
        //         Usart1Send("Error: No current\n");
        //         break;

        //     case ERROR_SOFT_OVERCURRENT:
        //         Usart1Send("Error: Soft Overcurrent\n");
        //         break;

        //     case ERROR_OVERTEMP:
        //         Usart1Send("Error: Overtemp\n");
        //         break;

        //     }
        // }

        //-- Ninguno de los anteriores
        else
            resp = resp_error;

    }	//fin if comandos

    


    return resp;
}

//--- end of file ---//
