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
  TCCR2B = _BV(CS21);                                                         //making prescaler of 8 to get 4kHz pwm frequency
                                                                              //Note: Want the routine to be entirely interrupt driven to increase frequency,
                                                                              //but cannot figure out why won't work
  //Getting initial states
  In_A=digitalRead(PH_A_IN);  
  In_B=digitalRead(PH_B_IN); 
  In_C=digitalRead(PH_C_IN);
  PWM_State=digitalRead(PWM_Work_Around);
}

void loop() {
  
  speed_read=analogRead(Driver_Input);                                        //Reading value from pot. Should be between 0-250 integer values
  
  analogWrite(PWM_No_Connect, speed_read);                                    //Changing PWM width based on potentiometer value
  Driving_Pins();
  
}

void Driving_Pins(){
  //Reads the states of the pins in the beggining  
  //It will then take the states of each and 
  //apply boolean logic so the pins output correctly
  
  //Reading states of Hall sensors and speed control
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
  In_A=digitalRead(PH_A_IN);
}

void HallB(){
  In_B=digitalRead(PH_B_IN);
}

void HallC(){
  In_C=digitalRead(PH_C_IN);
  
}

