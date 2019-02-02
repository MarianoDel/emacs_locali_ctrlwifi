//---------------------------------------------
// #### PROYECTO LOCALIZART - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### COMM.C ################################
//---------------------------------------------
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _COMM_H_
#define _COMM_H_


//--- Exported types ---//
#define CMD_OPEN    0x01
#define CMD_CLOSE    0x02
#define CMD_LIGHT_ON    0x04
#define CMD_LIGHT_OFF    0x08

//--- Exported constants ---//
typedef enum {
	resp_ok = 0,
	resp_error

} resp_t;

//--- Exported macro ---//

//--- Exported functions ---//
void UpdateCommunications (void);


#endif

//--- END OF FILE ---//
