/*===========================================================================================
 * Filename   : ultrasonic.c
 * Author     : Ahmad Haroun
 * Description: Source file HC-SR04 Module (Ultrasonic Distance Measurement sensor)
 * Created on : Jun 12, 2023
 *==========================================================================================*/
#include "timer1.h"
#include "gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                               Global_Variables Declaration                  *
 *******************************************************************************/

uint16 Time = 0;   /* a variable to save the pulse time in */
uint16 Edge_count = 0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/**********************************************************************************
 * Function Name: Ultrasonic_edgeProcessing
 * Description  : claculate the pulse time and save it in "Time" global variable
 * INPUTS       : void
 * RETURNS      : void
 **********************************************************************************/
void Ultrasonic_edgeProcessing(void)
{
	Edge_count++;
	if(Edge_count == 1)
	{
		TIMER1_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING_ICU);
	}
	else if(Edge_count == 2)
	{
		Time = TIMER1_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING_ICU);
		Edge_count = 0;
	}

}

/**************************************************************************
 * Function Name: Ultrasonic_init
 * Description  : ➢ Initialize the ICU driver as required.
 *                ➢ Setup the ICU call back function.
 *                ➢ Setup the direction for the trigger pin as output pin
 *                  through the GPIO driver.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Ultrasonic_init(void)
{
	TIMER1_Init_ICU_Mode(PRESCALER_8, ENABLE_INTERRUPT, RAISING_ICU);
	TIMER1_Set_CallBack(Ultrasonic_edgeProcessing,3);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT); /* Trigger pin */
}

/**************************************************************************
 * Function Name: Ultrasonic_Trigger
 * Description  : Send the Trigger pulse to the ultrasonic
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(11);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}


/**************************************************************************
 * Function Name: Ultrasonic_Trigger
 * Description  : ➢ Send the trigger pulse by using Ultrasonic_Trigger function.
 *				  ➢ Start the measurements by the ICU from this moment.
 * INPUTS       : void
 * RETURNS      : uint16(distance measured)
 **************************************************************************/
uint16 Ultrasonic_readDistance(void)
{
	uint16 d = 0;
	Ultrasonic_Trigger();
	d = (uint16)(Time/58.5);
	return d;
}
