#ifndef Motor_Driver_h
#define Motor_Driver_h

#include "Arduino.h" 

//input signals from hall effect sensors
#define PH_A_IN 19//interrupt PCINT0 on pin 19
#define PH_B_IN 20//interrupt PCINT1 on pin 20
#define PH_C_IN 21//interrupt PCINT2 on pin 21

//PWM Pins and opperations
#define PWM_No_Connect 9 //This will be the pin the PWM signal will output. It's only role is to be read
#define PWM_Work_Around 10 //This pin if only reading the state of the PWM signal for ease of programming issues 
int speed_read; //This is the value that the driver will control with the potentiometer. 
				//Based on hardware design, this value should range from ~0-250)


//Driving_Pins() function declarations
bool In_A, In_B, In_C, PWM_State; //These are the pins that will read the state of the hall effect sensor and PWM signal

//output signals to the mosfet driver
#define PH_A_OUT_H 23 
#define PH_B_OUT_H 24 
#define PH_C_OUT_H 25 

#define PH_A_OUT_L 26
#define PH_B_OUT_L 27
#define PH_C_OUT_L 28


// Fault, current and ADC pins
#define FAULT 43 //interrupt 0 on pin 43 to detect mosfet driver faults (highest priority)
//please note this routine does not nessesarily need to be done with an interrupt routine
#define OVR_CRNT 6 //interrupt 4 on pin 6 to detect over current (OCTW detect)
#define CNT_sense_1 97 //ADC0 to read sense resistor 1
#define CNT_sense_2 96 //ADC1 to read sense resistor 2
#define Sense_A 95 //ADC2 to read phase A Back EMF
#define Sense_B 94 //ADC3 to read phase B Back EMF
#define Sense_C 93 //ADC4  to read phase C Back EMF
//#define Motor_Temp 92 //ADC5 to read the temperature of the motor
#define Driver_Input 91 //ADC5 to read the driver input to control the speed of the motor
//Datasheet says this should be ADC6, but practise showed it to be ADC5. 




#endif
