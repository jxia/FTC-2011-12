#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeftWheel, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontRightWheel, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     backRightWheel, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     backLeftWheel, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     leftArm,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     rightArm,      tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    leftClaw,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    rightClaw,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"


void drive (int auto_command, long time) {
  int left_wheelsPower;
  int right_wheelsPower;
  int WHEELSPEED = 100;

  if(auto_command==0) {
    //Check for forward movement
    left_wheelsPower=WHEELSPEED;
    right_wheelsPower=WHEELSPEED;
    }else if(auto_command==4) {
    //Check for backwards movement
    left_wheelsPower=-WHEELSPEED;
    right_wheelsPower=-WHEELSPEED;
    }else if(auto_command==2) {
    //Check for right movement
    left_wheelsPower=WHEELSPEED;
    right_wheelsPower=0;
    }else if(auto_command==6) {
    //Check for left movement
    left_wheelsPower=0;
    right_wheelsPower=WHEELSPEED;
    }else {
    //Do not move
    left_wheelsPower=0;
    right_wheelsPower=0;
  }

  //Drive Code
  motor[frontLeftWheel] = left_wheelsPower;
  motor[backLeftWheel] = left_wheelsPower;
  motor[frontRightWheel] = right_wheelsPower;
  motor[backRightWheel] = right_wheelsPower;
  wait1Msec(time);
  motor[frontLeftWheel] = 0;
  motor[backLeftWheel] = 0;
  motor[frontRightWheel] = 0;
  motor[backRightWheel] = 0;
  return;
}

task main(){
  //Code: drive(auto_command,time);
  //replace auto_command and time with values necessary (if you don't replace them, code won't run)
  //auto_command values are: "rpoint", "lpoint", "up", "down", "rswing", "lswing", "rswingback", "lswingback"
  //time values is the time, in milliseconds, you want the robot to be doing the action specified in auto_command

  //Use the sonar sensor by: SensorValue[sonarSensor].  It can get a distance from 0cm to 80cm
  //drive("up", 10000);      move forward 10000 milliseconds (10sec)
  //drive("lpoint", 1000);   left point turn for 1000 milliseconds (1sec)
  //drive("up", 10000);      move forward again for 10000 milliseconds (10sec)


  waitForStart();

  /*
  int count = 0;

  string BatteryLevel = externalBatteryAvg;
  string selection = "";


  nxtDisplayCenteredBigTextLine (3, BatteryLevel);
  wait1Msec(3000);
  */


//Drive forward off of home blu wall
drive(0,4596);
drive(65535,100);

//Turn right 90 degrees
drive(2,3185);
drive(65535,100);

//Drive forward to bowling ball
drive(0,2908);
drive(65535,100);

//Turn right 90 degrees
drive(2,4037);
drive(65535,100);

//Turn right a bit
drive(2,516);
drive(65535,100);
drive(0,657);//Drive past bowling ball
drive(65535,100);
drive(6,188);//Turn left into bowling ball
drive(65535,100);
drive(6,237);//Turn left into bowling ball
drive(65535,100);
drive(0,425);//Drive forward
drive(65535,100);
drive(6,279);//Turn left into bowling ball
drive(65535,100);
drive(6,424);//Turn left into bowling ball
drive(65535,100);
drive(0,799);//Drive forward a bit
drive(65535,100);
drive(6,468);//Turn left into bowling ball
drive(65535,100);
drive(0,516);//Drive forward a bit
drive(65535,100);
drive(6,2065);//Turn left into bowling ball
drive(65535,100);
drive(0,1409);//Drive forward
drive(65535,100);
drive(6,8299);//Turn left, line up with bowling ball
drive(65535,100);
drive(6,424);//Turn left, line up with bowling ball

//Drive bowling ball into front zone
drive(65535,100);
drive(0,4408);//Drive forward
drive(65535,100);
drive(6,424);//Realign with bowling ball
drive(65535,100);
drive(0,2908);//Drive forward
drive(65535,100);
drive(6,608);//Realign with bowling ball
drive(65535,100);
drive(0,1312);//Drive forward
drive(0,1920);//Drive forward
drive(65535,100);
drive(0,424);//Drive forward
drive(65535,100);

drive(4,9756);//Drive backwards
drive(65535,100);
drive(4,376);//Drive backwards
drive(4,3516);//Drive backwards

}
