/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.

  @Description:
    This source file provides implementations for PIN MANAGER.
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

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>

/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA6, high using LATA6.

  @Description
    Sets the GPIO pin, RA6, high using LATA6.

  @Preconditions
    The RA6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA6 high (1)
    IO_RA6_SetHigh();
    </code>

*/
#define IO_RA6_SetHigh()          (_LATA6 = 1)
/**
  @Summary
    Sets the GPIO pin, RA6, low using LATA6.

  @Description
    Sets the GPIO pin, RA6, low using LATA6.

  @Preconditions
    The RA6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA6 low (0)
    IO_RA6_SetLow();
    </code>

*/
#define IO_RA6_SetLow()           (_LATA6 = 0)
/**
  @Summary
    Toggles the GPIO pin, RA6, using LATA6.

  @Description
    Toggles the GPIO pin, RA6, using LATA6.

  @Preconditions
    The RA6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA6
    IO_RA6_Toggle();
    </code>

*/
#define IO_RA6_Toggle()           (_LATA6 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RA6.

  @Description
    Reads the value of the GPIO pin, RA6.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA6
    postValue = IO_RA6_GetValue();
    </code>

*/
#define IO_RA6_GetValue()         _RA6
/**
  @Summary
    Configures the GPIO pin, RA6, as an input.

  @Description
    Configures the GPIO pin, RA6, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA6 as an input
    IO_RA6_SetDigitalInput();
    </code>

*/
#define IO_RA6_SetDigitalInput()  (_TRISA6 = 1)
/**
  @Summary
    Configures the GPIO pin, RA6, as an output.

  @Description
    Configures the GPIO pin, RA6, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA6 as an output
    IO_RA6_SetDigitalOutput();
    </code>

*/
#define IO_RA6_SetDigitalOutput() (_TRISA6 = 0)
/**
  @Summary
    Sets the GPIO pin, RE0, high using LATE0.

  @Description
    Sets the GPIO pin, RE0, high using LATE0.

  @Preconditions
    The RE0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE0 high (1)
    IO_W_DIR_SetHigh();
    </code>

*/
#define IO_W_DIR_SetHigh()          (_LATE0 = 1)
/**
  @Summary
    Sets the GPIO pin, RE0, low using LATE0.

  @Description
    Sets the GPIO pin, RE0, low using LATE0.

  @Preconditions
    The RE0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE0 low (0)
    IO_W_DIR_SetLow();
    </code>

*/
#define IO_W_DIR_SetLow()           (_LATE0 = 0)
/**
  @Summary
    Toggles the GPIO pin, RE0, using LATE0.

  @Description
    Toggles the GPIO pin, RE0, using LATE0.

  @Preconditions
    The RE0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE0
    IO_W_DIR_Toggle();
    </code>

*/
#define IO_W_DIR_Toggle()           (_LATE0 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RE0.

  @Description
    Reads the value of the GPIO pin, RE0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE0
    postValue = IO_W_DIR_GetValue();
    </code>

*/
#define IO_W_DIR_GetValue()         _RE0
/**
  @Summary
    Configures the GPIO pin, RE0, as an input.

  @Description
    Configures the GPIO pin, RE0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE0 as an input
    IO_W_DIR_SetDigitalInput();
    </code>

*/
#define IO_W_DIR_SetDigitalInput()  (_TRISE0 = 1)
/**
  @Summary
    Configures the GPIO pin, RE0, as an output.

  @Description
    Configures the GPIO pin, RE0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE0 as an output
    IO_W_DIR_SetDigitalOutput();
    </code>

*/
#define IO_W_DIR_SetDigitalOutput() (_TRISE0 = 0)
/**
  @Summary
    Sets the GPIO pin, RE1, high using LATE1.

  @Description
    Sets the GPIO pin, RE1, high using LATE1.

  @Preconditions
    The RE1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE1 high (1)
    IO_W_SLP_SetHigh();
    </code>

*/
#define IO_W_SLP_SetHigh()          (_LATE1 = 1)
/**
  @Summary
    Sets the GPIO pin, RE1, low using LATE1.

  @Description
    Sets the GPIO pin, RE1, low using LATE1.

  @Preconditions
    The RE1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE1 low (0)
    IO_W_SLP_SetLow();
    </code>

*/
#define IO_W_SLP_SetLow()           (_LATE1 = 0)
/**
  @Summary
    Toggles the GPIO pin, RE1, using LATE1.

  @Description
    Toggles the GPIO pin, RE1, using LATE1.

  @Preconditions
    The RE1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE1
    IO_W_SLP_Toggle();
    </code>

*/
#define IO_W_SLP_Toggle()           (_LATE1 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RE1.

  @Description
    Reads the value of the GPIO pin, RE1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE1
    postValue = IO_W_SLP_GetValue();
    </code>

*/
#define IO_W_SLP_GetValue()         _RE1
/**
  @Summary
    Configures the GPIO pin, RE1, as an input.

  @Description
    Configures the GPIO pin, RE1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE1 as an input
    IO_W_SLP_SetDigitalInput();
    </code>

*/
#define IO_W_SLP_SetDigitalInput()  (_TRISE1 = 1)
/**
  @Summary
    Configures the GPIO pin, RE1, as an output.

  @Description
    Configures the GPIO pin, RE1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE1 as an output
    IO_W_SLP_SetDigitalOutput();
    </code>

*/
#define IO_W_SLP_SetDigitalOutput() (_TRISE1 = 0)
/**
  @Summary
    Sets the GPIO pin, RF8, high using LATF8.

  @Description
    Sets the GPIO pin, RF8, high using LATF8.

  @Preconditions
    The RF8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF8 high (1)
    IO_JOEL_PIN_SetHigh();
    </code>

*/
#define IO_JOEL_PIN_SetHigh()          (_LATF8 = 1)
/**
  @Summary
    Sets the GPIO pin, RF8, low using LATF8.

  @Description
    Sets the GPIO pin, RF8, low using LATF8.

  @Preconditions
    The RF8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF8 low (0)
    IO_JOEL_PIN_SetLow();
    </code>

*/
#define IO_JOEL_PIN_SetLow()           (_LATF8 = 0)
/**
  @Summary
    Toggles the GPIO pin, RF8, using LATF8.

  @Description
    Toggles the GPIO pin, RF8, using LATF8.

  @Preconditions
    The RF8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF8
    IO_JOEL_PIN_Toggle();
    </code>

*/
#define IO_JOEL_PIN_Toggle()           (_LATF8 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RF8.

  @Description
    Reads the value of the GPIO pin, RF8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF8
    postValue = IO_JOEL_PIN_GetValue();
    </code>

*/
#define IO_JOEL_PIN_GetValue()         _RF8
/**
  @Summary
    Configures the GPIO pin, RF8, as an input.

  @Description
    Configures the GPIO pin, RF8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF8 as an input
    IO_JOEL_PIN_SetDigitalInput();
    </code>

*/
#define IO_JOEL_PIN_SetDigitalInput()  (_TRISF8 = 1)
/**
  @Summary
    Configures the GPIO pin, RF8, as an output.

  @Description
    Configures the GPIO pin, RF8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF8 as an output
    IO_JOEL_PIN_SetDigitalOutput();
    </code>

*/
#define IO_JOEL_PIN_SetDigitalOutput() (_TRISF8 = 0)

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC24FJ128GA010

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);



#endif
