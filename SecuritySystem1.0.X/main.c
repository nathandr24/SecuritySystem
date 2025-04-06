#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"
#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/uart2.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/tmr1.h"

#define NUM_OF_WINDOW_STEPS     200
#define NUM_OF_LOCK_STEPS       68

#define PASS_NUM_1 9
#define PASS_NUM_2 9
#define PASS_NUM_3 9
#define PASS_NUM_4 8

#define AUTO_TIMER_PERIOD 10000

uint8_t test = 0;

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

//Auto timer globals
volatile uint32_t autoTimerCounter = 0;
volatile uint8_t  autoTimerFlag = 0;

//Motion sensor globals
uint16_t trueDistance;
volatile uint8_t  outerSensorFlag = 0;
volatile uint8_t  innerSensorFlag = 0;

void stepWMotor(int16_t steps); //window motor
void stepLMotor(int16_t steps); //lock motor

void armSystem(void);
void disarmSystem(void);

//motion sensor prototypes
void readOuterDistance(void);
void outerTrip(void);
void readInnerDistance(void);
void innerTrip(void);

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
//    DELAY_milliseconds(2000);
//    Nop();
    
//    IO_LED2_SetHigh();
//    IO_LED3_SetHigh();
//    stepWMotor(1000);
//    stepLMotor(-48);
    
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
        
        if(autoTimerFlag)
        {
            IO_LED5_Toggle();
            autoTimerFlag = 0;
        }
    }

    return 1;
}

void TMR1_CallBack(void)
{
    autoTimerCounter++;
    if(autoTimerCounter >= AUTO_TIMER_PERIOD)
    {
        autoTimerFlag = 1;
        autoTimerCounter = 0;
    }
    
    UART1_Write('Q');
    uint16_t input = 46;
    
    // Test column 1
    IO_COL1_SetHigh();
    IO_COL2_SetLow();
    IO_COL3_SetLow();
    
    DELAY_milliseconds(100);
    
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
    
    DELAY_milliseconds(100);
    
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
    
    DELAY_milliseconds(100);
    
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
    
//    DELAY_milliseconds(50);

    if(input == 46)     // If no input then do nothing
        return;
    if(input == 11)
    {
        state = 0;
        passCorrect = 1;
        UART2_Write(0x76); //clear display
        return;
    }
        
    if(input == 10)     // Time to arm
    {
        armFlag = 1;
        UART2_Write(0x76); //clear display
        return;
    }
    else if(state == 0 && input == PASS_NUM_1) // First number correctly entered
    {
        state = 1;
        IO_LED2_Toggle();
    }
    else if(state == 0 && input != PASS_NUM_1) // First number incorrectly entered
    {
        state = 1;
        passCorrect = 0;
        IO_LED2_Toggle();
    }
    else if(state == 1 && input == PASS_NUM_2) // Second number correctly entered
    {
        state = 2;
        passCorrect &= 1;
        IO_LED2_Toggle();
    }
    else if(state == 1 && input != PASS_NUM_2) // Second number incorrectly entered
    {
        state = 2;
        passCorrect = 0;
        IO_LED2_Toggle();
    }
    else if(state == 2 && input == PASS_NUM_3) // Third number correctly entered
    {
        state = 3;
        passCorrect &= 1;
        IO_LED2_Toggle();
    }
    else if(state == 2 && input != PASS_NUM_3) // Third number incorrectly entered
    {
        state = 3;
        passCorrect = 0;
        IO_LED2_Toggle();
    }
    else if(state == 3 && input == PASS_NUM_4) // Fourth number correctly entered
    {
        state = 0;
        UART2_Write(0xA);UART2_Write(0xA);UART2_Write(0xA);UART2_Write(0xA);
        if(passCorrect)
        {
            disarmFlag = 1;
            return;
        }
    }
    else if(state == 3 && input != PASS_NUM_4) // Fourth number incorrectly entered
    {
        UART2_Write(0xF);UART2_Write(0xF);UART2_Write(0xF);UART2_Write(0xF);
        
        state = 0;
        passCorrect = 0;
        return;
    }
    UART2_Write(input);
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

void UART2_Receive_CallBack(void)
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
    if(numOfWStepsLeft <= 0)
    {
        TMR3_Stop();       //Stop the timer
        IO_W_SLP_SetLow(); //Sleep the stepper so it don't burn
        
        TMR1_Start(); //restart tmr1 so the poll loop can begina again
    }
    
}

void TMR2_CallBack(void)
{
    numOfLStepsLeft--;
    if(numOfLStepsLeft <= 0)
    {
        TMR2_Stop();       //Stop the timer
        IO_L_SLP_SetLow(); //Sleep the stepper so it don't burn
        
        TMR1_Start(); //restart tmr1 so the poll loop can begina again
    }
    
}

void stepWMotor(int16_t steps)
{
    TMR1_Stop(); //stop timer 1 so delays don't harm things
    
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
    TMR1_Stop(); //stop timer 1 so delays don't harm things
    
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
    IO_LED4_SetHigh();
}

void disarmSystem(void)
{
    stepWMotor(-NUM_OF_WINDOW_STEPS);
    stepLMotor(-NUM_OF_LOCK_STEPS);
    IO_LED4_SetLow();
}

void readOuterDistance(void)
{
    IO_OUT_SENSE_SetHigh();
    
    DELAY_milliseconds(10);
    
    i2c_address_t distanceSensor = 0x40;
    uint8_t rawDistance[2] = {0,0};
    rawDistance[1] = i2c_read1ByteRegister(distanceSensor, 0x5E); //bits 11:4
    rawDistance[0] = i2c_read1ByteRegister(distanceSensor, 0x5F); //bits  3:0
    trueDistance = ((uint16_t)rawDistance[1]*16 + rawDistance[0])/16/4;        
        
    if(trueDistance < 50)
    {
        outerTrip();
    }
    
    IO_OUT_SENSE_SetLow();
}

void outerTrip(void)
{
    if(outerSensorFlag == 1)
    {
        return;
    }
    else if(innerSensorFlag == 1)
    {
        DELAY_milliseconds(500);
        armFlag = 1;
        innerSensorFlag = 0;
        return;
    }
    else
    {
        outerSensorFlag = 1;
        return;
    }
}

void readInnerDistance(void)
{
    IO_IN_SENSE_SetHigh();
    
    DELAY_milliseconds(10);
    
    i2c_address_t distanceSensor = 0x40;
    uint8_t rawDistance[2] = {0,0};
    rawDistance[1] = i2c_read1ByteRegister(distanceSensor, 0x5E); //bits 11:4
    rawDistance[0] = i2c_read1ByteRegister(distanceSensor, 0x5F); //bits  3:0
    trueDistance = ((uint16_t)rawDistance[1]*16 + rawDistance[0])/16/4;        
        
    if(trueDistance < 50)
    {
        innerTrip();
    }
    
    IO_IN_SENSE_SetLow();
}

void innerTrip(void)
{
    if(innerSensorFlag == 1)
    {
        return;
    }
    else if(outerSensorFlag == 1)
    {
        DELAY_milliseconds(500);
        outerSensorFlag = 0;
        return;
    }
    else 
    {
        innerSensorFlag = 1;
        return;
    }
}