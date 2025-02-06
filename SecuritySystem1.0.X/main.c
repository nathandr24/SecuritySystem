#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"
#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/tmr2.h"

volatile uint8_t other = 0;
uint16_t timer3Period = 200;  // window motor speed
uint16_t timer2Period = 200;  // lock motor speed
volatile int16_t numOfWStepsLeft = 0;
volatile int16_t numOfLStepsLeft = 0;

void stepWMotor(int16_t steps); //window motor
void stepLMotor(int16_t steps); //lock motor


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    TMR3_Period16BitSet(timer3Period);
    OC4_SecondaryValueSet(TMR3_Period16BitGet() / 2);
    IO_W_SLP_SetLow();
    IO_W_DIR_SetHigh();
    
    TMR2_Period16BitSet(timer2Period);
    OC1_SecondaryValueSet(TMR2_Period16BitGet() / 2);
    IO_L_SLP_SetLow();
    IO_L_DIR_SetHigh();
    
//    
//    i2c_writeNBytes(0x71, &clearMessage, 1);
//    i2c_writeNBytes(0x71, &one , 1);
//    i2c_writeNBytes(0x71, &two, 1);
//    i2c_writeNBytes(0x71, &three, 1);
//    TXData = 5; i2c_writeNBytes(0x71, &TXData, 1);
    

    
    stepWMotor(1000);
    stepLMotor(10000);
    
    while (1)
    {

    }

    return 1;
}

void TMR1_CallBack(void)
{
//    if(other)
//    {
//        UART1_Write(0x1);
//        other = 0;
//    }
//    else
//    {
//        UART1_Write(0x0);
//        other = 1;
//    }
}

void UART1_Receive_CallBack(void)
{
    uint8_t a = 0;
    a = UART1_Read();
    if(a == 0)
        IO_RA6_SetLow();
    else
        IO_RA6_SetHigh();
}

void TMR3_CallBack(void)
{
    numOfWStepsLeft--;
    if(numOfWStepsLeft == 0)
    {
        TMR3_Stop();       //Stop the timer
        IO_W_SLP_SetLow(); //Sleep the stepper so it don't burn
    }
    
}

void TMR2_CallBack(void)
{
    numOfLStepsLeft--;
    if(numOfLStepsLeft == 0)
    {
        TMR2_Stop();       //Stop the timer
        IO_L_SLP_SetLow(); //Sleep the stepper so it don't burn
    }
    
}

void stepWMotor(int16_t steps)
{
    IO_W_SLP_SetHigh();
    
    if(steps > 0)
        IO_W_DIR_SetHigh();
    else
        IO_W_DIR_SetLow();
    numOfWStepsLeft = abs(steps);

    TMR3_Counter16BitSet(0);
    TMR3_Start();
}

void stepLMotor(int16_t steps)
{
    IO_L_SLP_SetHigh();
    
    if(steps > 0)
        IO_L_DIR_SetHigh();
    else
        IO_L_DIR_SetLow();
    numOfLStepsLeft = abs(steps);

    TMR2_Counter16BitSet(0);
    TMR2_Start();
}
