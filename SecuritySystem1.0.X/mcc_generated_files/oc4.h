/**
  OC4 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    oc4.h

  @Summary
    This is the generated header file for the OC4 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for OC4.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device            :  PIC24FJ128GA010
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _OC4_H
#define _OC4_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Types
*/

/** OC4 Fault Number

  @Summary
    Defines the fault number

  @Description
    This type defines the various faults supported.

  Remarks:
    None
*/

typedef enum
{   
    /* Fault 0 */
    OC4_FAULT0        /*DOM-IGNORE-BEGIN*/  = 0,/*DOM-IGNORE-END*/
} OC4_FAULTS;

/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes OC instance : 4

  @Description
    This routine initializes the OC4 driver instance for : 4
    index, making it ready for clients to open and use it.
    This routine must be called before any other OC4 routine is called.
	
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    uint16_t priVal,secVal;
    bool completeCycle = false;
    priVal = 0x1000;
    secVal = 0x2000;
    OC4_FAULTS faultNum = OC4_FAULT0;

    OC4_Initialize();
    
    OC4_CentreAlignedPWMConfig( priVal, secVal );
  
    OC4_Start();

    while(1)
    {
        faultStat =  OC4_FaultStatusGet( faultNum );

        if(faultStat)
        {
            OC4_FaultStatusClear( faultNum );
        }

        completeCycle = OC4_IsCompareCycleComplete( void );
        if(completeCycle)
        {
            OC4_Stop();
        }
    }
    </code>

*/

void OC4_Initialize (void);

/**
  @Summary
    Callback for OC4.

  @Description
    This routine is callback for OC4

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to OC4_Initialize(); for an example
*/
void OC4_CallBack(void);

/**
  @Summary
    Maintains the driver's state machine and implements its ISR

  @Description
    This routine is used to maintain the driver's internal state
    machine and implement its ISR for interrupt-driven implementations.
  
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    while (true)
    {
        OC4_Tasks();

        // Do other tasks
    }
    </code>
    
*/
void OC4_Tasks( void );

/**
  @Summary
    Enables the OC module with the corresponding operation mode.

  @Description
    This routine enables the OC module with the corresponding operation mode.

  @Preconditions
    OC4_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

  @Example 
    Refer to OC4_Initialize() for an example	
 
*/
void OC4_Start( void );

/**
  @Summary
    Disables the OC module.

  @Description
    This routine disables the OC module.

  @Preconditions
    OC4_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

*/
void OC4_Stop( void );

/**
  @Summary
    Sets the primary compare value of respective OC.
	
  @Description
    This routine sets the primary compare value for respective OC.

  @Preconditions
    OC4_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        OC4_PrimaryValueSet( uint16_t priVal);
    <code> 
 	
*/
void OC4_PrimaryValueSet( uint16_t priVal);

/**
  @Summary
    Sets the secondary compare value of respective OC.
	
  @Description
    This routine sets the Secondary compare value for respective OC.

  @Preconditions
    OC4_Initialize function should have been called 

  @Param
    secVal - 16 bit secondary compare value.
    

  @Returns
    None.

  @Example 
    <code>
        uint16_t secVal = 0x1000;
        OC4_SecondaryValueSet( uint16_t secVal);
    <code> 
 	
*/
void OC4_SecondaryValueSet( uint16_t secVal);


/**
  @Summary
    Gets the status of the compare cycle completion.

  @Description
    This routine gets the status of the compare cycle completion.

  @Preconditions
    OC4_Initialize function should have been called 

  @Param
    None.

  @Returns
    Boolean value describing the current status of the cycle completion. Returns
    true  : When the compare cycle has completed. 
    false : When the compare cycle has not completed. 

  @Example 
    Refer to OC4_Initialize() for an example
	

*/
bool OC4_IsCompareCycleComplete( void );

/**
  @Summary
    Gets the status of the PWM fault condition occurrence.

  @Description
    This routine gets the status of the PWM fault condition occurrence.
  
  @Preconditions
    OC4_Initialize function should have been called 

  @Param
    faultNum - The fault number

  @Returns
    boolean value describing the occurrence of the fault condition.
    true  : When the specified fault has occurred.
    false : When the specified fault has not occurred.
	
  @Example 
    Refer to OC4_Initialize() for an example 
 

*/
bool OC4_FaultStatusGet( OC4_FAULTS faultNum );


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_OC4_H
    
/**
 End of File
*/
