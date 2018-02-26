#include<Motor_Driver.h>


void setup() {

  //setting up the hall effect sensor interrupt pins
  attachInterrupt(digitalPinToInterrupt(PH_A_IN), HallA, CHANGE);              //creating pin change interrupts
  attachInterrupt(digitalPinToInterrupt(PH_B_IN), HallB, CHANGE);              //This will trigger when there is a 
  attachInterrupt(digitalPinToInterrupt(PH_C_IN), HallC, CHANGE);              //change of state on the pins
  pinMode(PH_A_IN, INPUT);
  pinMode(PH_B_IN, INPUT);
  pinMode(PH_C_IN, INPUT);
  //Setting up the motor driver pins 
  pinMode(PH_A_OUT_H, OUTPUT);
  pinMode(PH_B_OUT_H, OUTPUT);
  pinMode(PH_C_OUT_H, OUTPUT);
  pinMode(PH_A_OUT_L, OUTPUT);
  pinMode(PH_B_OUT_L, OUTPUT);
  pinMode(PH_C_OUT_L, OUTPUT);

  //Setting up the PWM pins
  pinMode(PWM_No_Connect, OUTPUT);                                             //pin 9, just connects to a resistor to ground
  pinMode(PWM_Work_Around, INPUT);                                             //pin 10, reads state of pin 9
  TCCR2B &= ~_BV(CS22);                                                        //cancelling pre-scaler of 64
  TCCR2B |= _BV(CS21);                                                         //making prescaler of 1 to get 62.5kHz pwm frequency
}

void loop() {
  
  analogWrite(PWM_No_Connect, 50);                                             //Outputing the analog output to this pin, this will only be used
                                                                               //to check the state of the pin. Change the speed value from interger 
                                                                               //values of 10-250 for speed control
  Driving_Pins();
  
}

void Driving_Pins(){
  //Reading states of Hall sensors and speed control
  In_A=digitalRead(PH_A_IN);                                                   //Reads the states of the pins in the beggining  
  In_B=digitalRead(PH_B_IN);                                                   //It will then take the states of each and 
  In_C=digitalRead(PH_C_IN);                                                   //apply boolean logic so the pins output correctly
  PWM_State=digitalRead(PWM_Work_Around);

  //Setting pins based on boolean logic of pin states
  digitalWrite(PH_A_OUT_H, (In_A && !In_B)&& PWM_State);                       //digital logic representing current state of the hall effect pins
  digitalWrite(PH_B_OUT_H, (In_B && !In_C)&& PWM_State);                       //When PWM signal is high, the system outputs, when it is low, the system does not
  digitalWrite(PH_C_OUT_H, (In_C && !In_A)&& PWM_State);                       //When Fault is created, this can also && to the signal
  //Setting output low pins
  digitalWrite(PH_A_OUT_L, (!In_A && In_B)&& PWM_State); 
  digitalWrite(PH_B_OUT_L, (!In_B && In_C)&& PWM_State);
  digitalWrite(PH_C_OUT_L, (!In_C && In_A)&& PWM_State);
  
}

void HallA(){
  Driving_Pins();
}

void HallB(){
  Driving_Pins();
}

void HallC(){
  Driving_Pins();
  
}

