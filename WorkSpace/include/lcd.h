/*===========================================================================================
 * Filename   : lcd.c
 * Author     : Ahmad Haroun
 * Description: Header File for LCD Driver
 * Created on : Jun 12, 2023
 *==========================================================================================*/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN1_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/***********************************************************************************************
 * Function Name      : LCD_init
 * Description        :
 * Initialize the LCD : 1. Setup the LCD pins directions by use the GPIO driver.
 *                      2. Setup the LCD Data Mode 4-bits or 8-bits.
 * INPUTS             : void
 * RETURNS            : void
 ***********************************************************************************************/
void LCD_init(void);



/***********************************************************************************************
 * Function Name      : LCD_sendCommand
 * Description        : Send the required command to the screen
 * INPUTS             : command (defined in lcd.h)
 * RETURNS            : void
 ***********************************************************************************************/
void LCD_sendCommand(uint8 command);



/***********************************************************************************************
 * Function Name      : LCD_displayCharacter
 * Description        : Display the required character on the screen
 * INPUTS             : uint8 data (character to displayed)
 * RETURNS            : void
 ***********************************************************************************************/
void LCD_displayCharacter(uint8 data);



/***********************************************************************************************
 * Function Name      : LCD_displayString
 * Description        : Display the required string on the screen
 * INPUTS             : char *Str (string to displayed)
 * RETURNS            : void
 ***********************************************************************************************/
void LCD_displayString(const char *Str);



/***********************************************************************************************
 * Function Name      : LCD_moveCursor
 * Description        : Move the cursor to a specified row and column index on the screen
 * INPUTS             : uint8 row ,uint8 col
 * RETURNS            : void
 ***********************************************************************************************/
void LCD_moveCursor(uint8 row,uint8 col);



/***********************************************************************************************
 * Function Name      : LCD_intgerToString
 * Description        : Display the required decimal value on the screen
 * INPUTS             : int data
 * RETURNS            : void
 ***********************************************************************************************/
void LCD_intgerToString(int data);



/***********************************************************************************************
 * Function Name      : LCD_clearScreen
 * Description        : Send the clear screen command
 * INPUTS             : void
 * RETURNS            : void
 ***********************************************************************************************/
void LCD_clearScreen(void);

#endif /* LCD_H_ */
