/*===========================================================================================
 * Filename   : timer1.h
 * Author     : Ahmad Haroun
 * Description: Header file ATMEGA32 Timer1 Driver
 * Created on : Jun 12, 2023
 *==========================================================================================*/
#ifndef TIMER1_H_
#define TIMER1_H_

#include "gpio.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NORMAL_PORT,
	TOGGLE_OC1A,
	CLEAR_OC1A,
	SET_OC1A,
}CTC_Output_Mode;

typedef enum
{
	Normal_Port,
	Toggle_OC1A ,
	NON_INVERTING,
	INVERTING,
}PWM_Output_Mode;

typedef enum
{
	NO_CLOCK,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_FALLING,
	EXTERNAL_RISING,
}Clock_Pescaler;

typedef enum
{
	DISABLE_INTERRUPT,
	ENABLE_INTERRUPT,
}INTERRUPT_SELECT;


typedef enum
{
	FALLING_ICU,
	RAISING_ICU,
}ICU_EDGE_TYPE;

/*******************************************************************************
 *                               Global_Variables Declaration                  *
 *******************************************************************************/

/********************************************************************************
 * Global Array of 4 pointers to function
 * 1.static to use in this file and hold his value
 * 2.volatile to use in ISRs function and in the function 'TIMER1_Set_CallBack'
 * 3.Initial value with Null or use NULL_Ptr in standard_types
 * TIMER1_OVF_vect    : INDEX 0
 * TIMER1_COMPA_vect  : INDEX 1
 * TIMER1_COMPB_vect  : INDEX 2
 * TIMER1_CAPT_vect   : INDEX 3
 *********************************************************************************/
static volatile void (*TIMER1_CallBack_Array[4])(void) = {NULL_PTR};



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/**************************************************************************
 * Function Name: TIMER1_Init_Normal_Mode
 * Description  : Initialize Timer1 in Normal Mode or Overflow mode
 * INPUTS       : Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_Normal_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);



/**************************************************************************
 * Function Name: TIMER1_Init_CTC_Mode
 * Description  : Initialize TIMER1 in Clear timer on compare match(CTC) mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_CTC_Mode(uint16 Compare_Value,CTC_Output_Mode OutPutPin_Mode
		                 ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);



/**************************************************************************
 * Function Name: TIMER1_Init_PWM_Mode
 * Description  : Initialize TIMER1 in pulse width modulation generation(PWM)mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_PWM_Mode(uint8 Compare_Value,PWM_Output_Mode OutPutPin_Mode
		                  ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);

/**************************************************************************
 * Function Name: TIMER1_Init_ICU_Mode
 * Description  : Initialize TIMER1 in ICU_Mode
 * INPUTS       : Prescaler,Interrupt_Choice,EDGE  (1024,Enable_interrupt,Falling)
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_ICU_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice,ICU_EDGE_TYPE EDGE);


/**********************************************************************************
 * Function Name: TIMER1_Set_CallBack
 * Description  : A Function to set the callBack functions for Timer1 Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void TIMER1_Set_CallBack(void(* ptr_2_fun)(void),uint8 index);



/**************************************************************************
 * Function Name: TIMER1_clearTimerValue
 * Description  : Function to clear the Timer1 Value to start count from ZERO
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_clearTimerValue(void);



/**************************************************************************
 * Function Name: ICU_setEdgeDetectionType
 * Description  : Function to set the required edge detection.
 * INPUTS       : a_edgeType (Required EDGE Type)
 * RETURNS      : void
 **************************************************************************/
void ICU_setEdgeDetectionType(const ICU_EDGE_TYPE a_edgeType);



/**************************************************************************
 * Function Name: TIMER1_getInputCaptureValue
 * Description  : Function to get the Timer1 From ICR1 Register
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
uint16 TIMER1_getInputCaptureValue(void);

#endif /* TIMER1_H_ */
