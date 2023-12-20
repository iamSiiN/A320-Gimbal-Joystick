#include <Arduino.h>

#include <Joystick.h>  //get the library here: https://github.com/MHeironimus/ArduinoJoystickLibrary


//In this project i need, total of 3 buttons: ptt trigger, side stick priority button, pedal disconnect button.
// X and Y axis for Gimbal, and Steering Axis for NWS Tiller

//define buttons digital pins, analog pins for gimbal x/y and steering axis for NWS 
#define button_input1 7
#define button_input2 8 
#define button_input3 9
#define joyX A0
#define joyY A1
#define steering_input A2 

//this line below this comment block describes the following order after JOYSTICK_TYPE_JOYSTICK, 
//Buttons (default: 32)
//Hat Switches (up to 2)
//X, Y, and/or Z Axis (up to 16-bit precision)
//X, Y, and/or Z Axis Rotation (up to 16-bit precision)
//Rudder (up to 16-bit precision)
//Throttle (up to 16-bit precision)
//Accelerator (up to 16-bit precision)
//Brake (up to 16-bit precision)
//Steering (up to 16-bit precision)


Joystick_ Joystick(0x03, JOYSTICK_TYPE_JOYSTICK, 3, 0, true, true, false, false, false, false, false, false, false, false, true);

const bool initAutoSendState = true;

int steering_before = 0;
int steering_now = 0;
int xAxis_ = 0;
int yAxis_ = 0;

//Set button Default States
  int lastButton1State = 0;
  int lastButton2State = 0;
  int lastButton3State = 0;


void setup() {
  pinMode(button_input1, INPUT_PULLUP);
  pinMode(button_input2, INPUT_PULLUP);
  pinMode(button_input3, INPUT_PULLUP);

  Joystick.begin();
}

void loop() {
//main code to run repeatedly:
//Axis Runtime
//Gimbal xAxis
  xAxis_ = analogRead(joyX);
  xAxis_ = map(xAxis_,0,1023,0,255);
  Joystick.setXAxis (xAxis_);

//Gimbal yAxis
  yAxis_ = analogRead(joyY);
  yAxis_ = map(yAxis_,0,1023,0,255);
  Joystick.setYAxis (yAxis_);

//NWS Tiller
  steering_now = analogRead(steering_input);
  if (steering_now != steering_before) {
    Joystick.setSteering(steering_now);
    steering_before = steering_now;
  }

//Read button pin values
//button1 - PTT trigger
  int currentButton1State = !digitalRead(button_input1);
	if (currentButton1State != lastButton1State) {
    Joystick.setButton (0, currentButton1State);
    lastButton1State = currentButton1State;
  }
//button2 - Priority/AP Button
  int currentButton2State = !digitalRead(button_input2);
  if (currentButton2State != lastButton2State) {
    Joystick.setButton (1, currentButton2State);
    lastButton2State = currentButton2State;
  }
//button3 NWS Tiller Pedal Disc
  int currentButton3State = !digitalRead(button_input3);
  if (currentButton3State != lastButton3State) {
    Joystick.setButton (2, currentButton3State);
    lastButton3State = currentButton3State;
  }


  delay(20);  //for debouncing
}
