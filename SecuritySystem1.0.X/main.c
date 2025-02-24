#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"
#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/uart2.h"

#define NUM_OF_WINDOW_STEPS     2000
#define NUM_OF_LOCK_STEPS       2000

#define PASS_NUM_1 9
#define PASS_NUM_2 9
#define PASS_NUM_3 9
#define PASS_NUM_4 8

uint16_t timer3Period = 200;  // window motor speed
uint16_t timer2Period = 200;  // lock motor speed

// Stepper Globals
volatile int16_t numOfWStepsLeft = 0;
volatile int16_t numOfLStepsLeft = 0;

// Arming and disarming globals
volatile uint16_t armStatus = 0; //0 is disarmed while 1 is armed
volatile uint16_t armFlag = 0;
volatile uint16_t disarmFlag = 0;

// Keypad Globals
volatile char state = 0;
volatile char passCorrect = 1; 

void stepWMotor(int16_t steps); //window motor
void stepLMotor(int16_t steps); //lock motor

void armSystem(void);
void disarmSystem(void);

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
    
//    i2c_writeNBytes(0x71, &clearMessage, 1);
//    i2c_writeNBytes(0x71, &one , 1);
//    i2c_writeNBytes(0x71, &two, 1);
//    i2c_writeNBytes(0x71, &three, 1);
//    TXData = 5; i2c_writeNBytes(0x71, &TXData, 1);
    UART1_Write(0x76);

    
    stepWMotor(1000);
    stepLMotor(3000);
    
    while (1)
    {
        if(armStatus == 0 && disarmFlag == 1)
            disarmFlag = 0;
        else if(armStatus == 0 && armFlag == 1)
        {
            armSystem();
            armFlag = 0;
            armStatus = 1;
        }
        else if(armStatus == 1 && disarmFlag == 1)
        {
            disarmSystem();
            disarmFlag = 0;
            armStatus = 0;
        }
        else if(armStatus == 1 && armFlag == 1)
            armFlag = 0;
    }

    return 1;
}

void TMR1_CallBack(void)
{
    UART2_Write('Q');
    uint16_t input = 46;
    
    // Test column 1
    IO_COL1_SetHigh();
    IO_COL2_SetLow();
    IO_COL3_SetLow();
    
    for(int i=0; i<100; i++)
        Nop();
    
    if(IO_ROW1_GetValue())
        input = 1;
    else if(IO_ROW2_GetValue())
        input = 4;
    else if(IO_ROW3_GetValue())
        input = 7;
    else if(IO_ROW4_GetValue())
        input = 10;
    
    // Test column 2
    IO_COL1_SetLow();
    IO_COL2_SetHigh();
    IO_COL3_SetLow();
    
    for(int j=0;j<100;j++)
        Nop();
    if(IO_ROW1_GetValue())
        input = 2;
    else if(IO_ROW2_GetValue())
        input = 5;
    else if(IO_ROW3_GetValue())
        input = 8;
    else if(IO_ROW4_GetValue())
        input = 0;
    
    // Test column 3
    IO_COL1_SetLow();
    IO_COL2_SetLow();
    IO_COL3_SetHigh();
    for(int k = 0; k <100; k++)
        Nop();
    
    if(IO_ROW1_GetValue())
        input = 3;
    else if(IO_ROW2_GetValue())
        input = 6;
    else if(IO_ROW3_GetValue())
        input = 9;
    else if(IO_ROW4_GetValue())
        input = 11;
    
    IO_COL1_SetLow();
    IO_COL2_SetLow();
    IO_COL3_SetLow();

    
    if(input == 46)     // If no input then do nothing
        return;
    if(input == 11)
    {
        state = 0;
        passCorrect = 1;
        UART1_Write(0x76); //clear display
        return;
    }
        
    if(input == 10)     // Time to arm
    {
        armFlag = 1;
        UART1_Write(0x76); //clear display
        return;
    }
    else if(state == 0 && input == PASS_NUM_1) // First number correctly entered
        state = 1;
    else if(state == 0 && input != PASS_NUM_1) // First number incorrectly entered
    {
        state = 1;
        passCorrect = 0;
    }
    else if(state == 1 && input == PASS_NUM_2) // Second number correctly entered
    {
        state = 2;
        passCorrect &= 1;
    }
    else if(state == 1 && input != PASS_NUM_2) // Second number incorrectly entered
    {
        state = 2;
        passCorrect = 0;
    }
    else if(state == 2 && input == PASS_NUM_3) // Third number correctly entered
    {
        state = 3;
        passCorrect &= 1;
    }
    else if(state == 2 && input != PASS_NUM_3) // Third number incorrectly entered
    {
        state = 3;
        passCorrect = 0;
    }
    else if(state == 3 && input == PASS_NUM_4) // Fourth number correctly entered
    {
        state = 0;
        UART1_Write(0xA);UART1_Write(0xA);UART1_Write(0xA);UART1_Write(0xA);
        if(passCorrect)
        {
            disarmFlag = 1;
            return;
        }
    }
    else if(state == 3 && input != PASS_NUM_4) // Fourth number incorrectly entered
    {
        UART1_Write(0xF);UART1_Write(0xF);UART1_Write(0xF);UART1_Write(0xF);
        
        state = 0;
        passCorrect = 0;
        return;
    }
    UART1_Write(input);

}

void UART1_Receive_CallBack(void)
{
    uint8_t a = 0;
    a = UART1_Read();
    if(a == 'A')
        armFlag = 1;
    else if(a == 'D')
        disarmFlag = 1;
}

UART2_Receive_CallBack()
{
    uint8_t a = 0;
    a = UART2_Read();
    if(a == 'A')
        armFlag = 1;
    else if(a == 'D')
        disarmFlag = 1;
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

void armSystem(void)
{
    stepWMotor(NUM_OF_WINDOW_STEPS);
    stepLMotor(NUM_OF_LOCK_STEPS);
}

void disarmSystem(void)
{
    stepWMotor(-NUM_OF_WINDOW_STEPS);
    stepLMotor(-NUM_OF_LOCK_STEPS);
}