/*===========================================================================================
 * Filename   : timer1.c
 * Author     : Ahmad Haroun
 * Description: Source file ATMEGA32 Timer1 Driver
 * Created on : Jun 12, 2023
 *==========================================================================================*/

#include "timer1.h"

/*******************************************************************************
 *                               Global_Variables Declaration                  *
 *******************************************************************************/
volatile uint8 Counter_Compare_Mode = 0;
volatile uint8 Counter_Normal_Mode = 0;
volatile uint8 Counter_PWM_Mode = 0;

volatile uint8 SECOND  = 0;
volatile uint8 MINUTE  = 0;
volatile uint8 HOUR    = 0;


/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR TIMER1_OVF_vect)
 * Description  : Call the Function that is required to be Executed when TIMER1_OVF happens
 **************************************************************************/
ISR(TIMER1_OVF_vect)
{

	(*TIMER1_CallBack_Array[0])();
}


/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR TIMER1_COMPA_vect)
 * Description  : Call the Function that is required to be Executed when TIMER1_COMPA happens
 **************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	(*TIMER1_CallBack_Array[1])();
}



/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR TIMER1_COMPB_vect)
 * Description  : Call the Function that is required to be Executed when TIMER1_COMPB happens
 **************************************************************************/
ISR(TIMER1_COMPB_vect)
{

	(*TIMER1_CallBack_Array[2])();
}


/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR TIMER1_CAPT_vect)
 * Description  : Call the Function that is required to be Executed when TIMER1_CAPT happens
 **************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	(*TIMER1_CallBack_Array[3])();

}




/**************************************************************************
 * Function Name: TIMER1_Init_Normal_Mode
 * Description  : Initialize Timer1 in Normal Mode or Overflow mode
 * INPUTS       : Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_Normal_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	TCNT1 = 0;
	TCCR1A |= (1 << FOC1A);
	TCCR1B = (TCCR1B & 0xF8) | (Prescaler);
	if(Interrupt_Choice == DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,TOIE1);
	}
	else if(Interrupt_Choice == ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,TOIE1);
		SREG |= (1 << 7);
	}
	else
	{

	}
}



/**************************************************************************
 * Function Name: TIMER1_Init_CTC_Mode
 * Description  : Initialize TIMER1 in Clear timer on compare match(CTC) mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_CTC_Mode(uint16 Compare_Value, CTC_Output_Mode OutPutPin_Mode ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	TCNT1 = 0;
	OCR1A  = Compare_Value;
	TCCR1A |=(1 << FOC1A) ;
	TCCR1B |= (1 << WGM12);
	TCCR1B = (TCCR1B & 0xF8) | (Prescaler);
	TCCR1A = (TCCR0 & 0x3F) | (OutPutPin_Mode << 6);
	if(Interrupt_Choice == DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,OCIE1A);
	}
	else if(Interrupt_Choice == ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,OCIE1A);
		SREG |= (1 << 7);
	}
	else
	{

	}

}


/**************************************************************************
 * Function Name: TIMER1_Init_PWM_Mode
 * Description  : Initialize TIMER1 in pulse width modulation generation(PWM)mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_PWM_Mode(uint8 Compare_Value,PWM_Output_Mode OutPutPin_Mode
		                  ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	TCNT1 = 0;
	OCR1A  = Compare_Value;
	TCCR1A |= (1<<WGM00)|(1 <<WGM01);
	TCCR1B |= (1<<WGM12)|(1 <<WGM13);
	TCCR1B = (TCCR1B & 0xF8) | (Prescaler);
	TCCR1A = (TCCR1B & 0x3F) | (OutPutPin_Mode << 6);
	if(Interrupt_Choice == DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,OCIE1A);
	}
	else if(Interrupt_Choice == ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,OCIE1A);
		SREG |= (1 << 7);
	}
	else
	{

	}
}

/**************************************************************************
 * Function Name: TIMER1_Init_ICU_Mode
 * Description  : Initialize TIMER1 in ICU_Mode
 * INPUTS       : Prescaler,Interrupt_Choice,EDGE  (1024,Enable_interrupt,Raising)
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_ICU_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice,ICU_EDGE_TYPE EDGE)
{

	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT); /* ICP1 pin as Input Pin */
	TCNT1   = 0;
	ICR1 = 0;
	TCCR1A  = (1 << FOC1A) | (1 << FOC1B);
	TCCR1B &= ~(1 << WGM13) & ~(1 << WGM12);
	if(EDGE == FALLING_ICU)
	{
		CLEAR_BIT(TCCR1B,ICES1);
	}
	else
	{
		SET_BIT(TCCR1B,ICES1);
	}

	TCCR1B = (TCCR1B & 0xF8) | (Prescaler) ;

	if(Interrupt_Choice == ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,TICIE1);
		SET_BIT(SREG,7);
	}
	else
	{
		CLEAR_BIT(TIMSK,TICIE1);
	}

}


/**********************************************************************************
 * Function Name: TIMER1_Set_CallBack
 * Description  : A Function to set the callBack functions for Timer1 Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void TIMER1_Set_CallBack(void(* ptr_2_fun)(void),uint8 index)
{
	TIMER1_CallBack_Array[index] = ptr_2_fun;
}




/**************************************************************************
 * Function Name: TIMER1_clearTimerValue
 * Description  : Function to clear the Timer1 Value to start count from ZERO
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_clearTimerValue(void)
{
	TCNT1 = 0;
}



/**************************************************************************
 * Function Name: ICU_setEdgeDetectionType
 * Description  : Function to set the required edge detection.
 * INPUTS       : a_edgeType (Required EDGE Type)
 * RETURNS      : void
 **************************************************************************/
void ICU_setEdgeDetectionType(const ICU_EDGE_TYPE a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}



/**************************************************************************
 * Function Name: TIMER1_getInputCaptureValue
 * Description  : Function to get the Timer1 From ICR1 Register
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
uint16 TIMER1_getInputCaptureValue(void)
{
	return ICR1;
}
