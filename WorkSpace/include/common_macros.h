/*===========================================================================================
 * Filename   : common_macros.h
 * Author     : Ahmad Haroun
 * Description: header file most common macros
 * Created on : Jun 12, 2023
 *==========================================================================================*/
#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* A More Readable Formula SET a Specific Bit in A REGISTER */
#define SET_BIT(REG,BIT)     (REG |= (1<<BIT))
/* A More Readable Formula CLEAR a Specific Bit in A REGISTER */                             
#define CLEAR_BIT(REG,BIT)   (REG &= ~(1<<BIT))
/* A More Readable Formula TOGGLE a Specific Bit in A REGISTER */                             
#define TOGGLE_BIT(REG,BIT)  (REG ^= (1<<BIT))
/* A More Readable Formula GET a Specific Bit in A REGISTER */                             
#define GET_BIT(REG,BIT)     ((REG & (1 << BIT)) >> BIT)
 /* A More Readable Formula Rotate REGISTER RIGHT By Bits */                            
#define ROR(REG,BITS)       (REG = (REG >> BITS) | (REG << (8 - BITS)) )
/* A More Readable Formula Rotate a REGISTER Left by Bits */                             
#define ROL_BIT(REG,BITS)   (REG = (REG << BITS) | (REG >> (8 - BITS)))
/* A More Readable Formula SET check if a specific bit is set */                                
#define BIT_IS_SET(REG,BIT)  (REG &(1<<BIT))
/* A More Readable Formula to check if a specifc bit is clear*/                                
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))
                            

#endif /*COMMON_MACROS_H_*/

