#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     driveLFront,   tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     driveRFront,   tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     driveLBack,    tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     driveRBack,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     leftArm,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     rightArm,      tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    leftArmServo,         tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    rightArmServo,        tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    magnetBallGate,       tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


void initializeRobot() //Defines robot initiation routine
{

  return;
}


task main()
{

  int forwardLeft, forwardRight, reverse=1;

  initializeRobot();

  waitForStart();   // wait for start of tele-op phase- used for the Samantha Module

  while (true)
  {
	 getJoystickSettings(joystick);
	//joystick handling

	if(joy1Btn(5)==1){
	  //if button 5 is pressed, robot will only drive straight forward/back, ignoring any turns
	  forwardLeft=(reverse*joystick.joy1_y1)/2;
    forwardRight=forwardLeft;
  }else{
    //normal joystick motion
	  forwardLeft=(reverse*joystick.joy1_y1+joystick.joy1_x1)/2;
    forwardRight=(reverse*joystick.joy1_y1-joystick.joy1_x1)/2;
  }

    //cancels out joystick defects
    if(abs(forwardLeft)<10){
      forwardLeft=0;}
    if(abs(forwardRight)<10){
      forwardRight=0;}
    //Drive!
    motor[driveLFront]=forwardLeft;
    motor[driveLBack]=forwardLeft;
    motor[driveRFront]=forwardRight;
    motor[driveRBack]=forwardRight;
  }
}