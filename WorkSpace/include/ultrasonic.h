/*===========================================================================================
 * Filename   : ultrasonic.h
 * Author     : Ahmad Haroun
 * Description: Header file HC-SR04 Module (Ultrasonic Distance Measurement sensor)
 * Created on : Jun 12, 2023
 *==========================================================================================*/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**************************************************************************
 * Function Name: Ultrasonic_init
 * Description  : ➢ Initialize the ICU driver as required.
 *                ➢ Setup the ICU call back function.
 *                ➢ Setup the direction for the trigger pin as output pin
 *                  through the GPIO driver.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Ultrasonic_init(void);


/**************************************************************************
 * Function Name: Ultrasonic_Trigger
 * Description  : Send the Trigger pulse to the ultrasonic
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Ultrasonic_Trigger(void);


/**************************************************************************
 * Function Name: Ultrasonic_Trigger
 * Description  : ➢ Send the trigger pulse by using Ultrasonic_Trigger function.
 *				  ➢ Start the measurements by the ICU from this moment.
 * INPUTS       : void
 * RETURNS      : uint16(distance measured)
 **************************************************************************/
uint16 Ultrasonic_readDistance(void);


/**********************************************************************************
 * Function Name: Ultrasonic_edgeProcessing
 * Description  : claculate the pulse time and save it in "Time" global variable
 * INPUTS       : void
 * RETURNS      : void
 **********************************************************************************/
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
