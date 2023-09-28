/*===========================================================================================
 * Filename   : std_types.h
 * Author     : Ahmad Haroun
 * Description: Header File for the standard data types
 * Created on : Jun 12, 2023
 *==========================================================================================*/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NULL_PTR  ((void *)0)

/* boolean Data Type */
typedef unsigned char boolean;

/* Boolean Values */
#ifndef TRUE 
#define TRUE   (1U)
#endif

#ifndef FALSE 
#define FALSE   (0U)
#endif

#define LOGIC_HIGH  (1U)
#define LOGIC_LOW  (0U)

typedef unsigned char   uint8;               /* Range from 0 To 255 */
typedef signed char     sint8;               /* Range from -128 To 128 */
typedef unsigned short  uint16;              /* Range from 0 To 65635 */
typedef signed short     sint16;             /* Range from -32768 To 32767 */
typedef unsigned long  uint32;               /* Range from  0 To 4294967295 */
typedef signed long  sint32;                 /* Range from -2147483648 To 2147483649 */
typedef unsigned long long  uint64;          /* Range  0 .. 18446744073709551615 */
typedef signed long long  sint64;            /* Range -9223372036854775808 .. 9223372036854775807*/
typedef float float32;                      
typedef double  float64;                     



#endif
