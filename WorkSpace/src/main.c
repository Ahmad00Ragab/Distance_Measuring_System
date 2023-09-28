/*===========================================================================================
 * Filename   : Main.c
 * Author     : Ahmad Haroun
 * Description: Fan Controller system
 * Created on : Jul 12, 2023
 *==========================================================================================*/

 /*===========================================================================================
 * SUMMARY:
 *  The aim of this project is to  Implement a system to measure the distance using
 *  Ultrasonic sensor HC-SR04
 *==========================================================================================*/

/*===========================================================================================
 * Specification
 * MicroController    : ATMega32
 * CPU Frequency      : 8Mhz
 * Ultrasonic sensor  : HC-SR04
 * Display            : LCD (LM016L)
 * TIMER1             : USE TIMER1 in ICU MODE
 *==========================================================================================*/
#include "ultrasonic.h"
#include "lcd.h"
#include "timer1.h"



/*******************************************************************************
 *                               Main                                          *
 *******************************************************************************/
int main(void)
{
	uint32 distance = 0;
	LCD_init();
	LCD_displayString("Distance =");
	Ultrasonic_init();
	while(1)
	{
		distance = (uint32)Ultrasonic_readDistance();

		if(distance >= 100 )
		{
			LCD_moveCursor(0, 10);
			LCD_intgerToString(distance);
			LCD_displayString("cm");
		}
		else
		{
			LCD_moveCursor(0,10);
			LCD_intgerToString(distance);
			LCD_displayString(" cm ");
		}

	}
}
