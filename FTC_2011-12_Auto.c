#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Motor,  motorA,          frontTread,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          backTread,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeftWheel, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontRightWheel, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backLeftWheel, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     backRightWheel, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     leftArm,       tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     rightArm,      tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    leftClaw,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    rightClaw,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
//Sonar sensor config?
#include "Autonomous.h"

task main(){
	//Code: drive(auto_command,time);
	//replace auto_command and time with values necessary (if you don't replace them, code won't run)
	//auto_command values are: "rpoint", "lpoint", "up", "down", "rswing", "lswing", "rswingback", "lswingback"
	//time values is the time, in milliseconds, you want the robot to be doing the action specified in auto_command

	//Info:
	//Motor at 75% power travels at 2 feet per second = 60.96 cm
	//Lpoint turn takes 1560 ms to turn 90 degrees

	//Use the sonar sensor by: SensorValue[sonarSensor].  It can get a distance from 0cm to 80cm
	//drive("up", 10000);      move forward 10000 milliseconds (10sec)
	//drive("lpoint", 1000);   left point turn for 1000 milliseconds (1sec)
	//drive("up", 10000);      move forward again for 10000 milliseconds (10sec)

	string program_type="Red";
	int offset_back = 0;
	int offset_right = 0;
	int robot_length = 667; //In milliseconds
	int distance = 0;

	if (program_type=="Red") {
		//1) Measure offset from walls
		//!IMPORTANT START ROBOT SIDEWAYS facing left to reduce time it takes to measure
		//!IMPORTANT Ultrasonic measurer should be placed facing the back with the edge lined up with the robot's back
		//Convert offset distance into milliseconds

	  //Measure
		offset_right = SensorValue[sonarSensor];
		// Turn right 90 degreees
		distance = 1560;
		drive("rpoint", distance);
		//Remeasure
		offset_back = SensorValue[sonarSensor];


		//2) Move forward ((Four Feet Seven Inches=139.7 cm)-offset_back)

		distance = 2291.66666 - offset_back;
		drive("up", distance);

		//3) Point turn -90 degrees

		distance = 1560;
		drive("lpoint", distance);

		//4) Move forward ((Four Feet Eight Inches=142.24 cm)-(the robot's length)-offset_right)

		distance = 2333.333333 - robot_length - offset_right;
		drive("up", distance);

		//5) Point turn -33.7 degrees

		distance = 584.13333333;
		drive("lpoint", distance);

		//6) Move forward ((Nine Feet Two Inches=279.4 cm)-(the robot's length))

		distance = 4583.333333 - robot_length;
		drive("up", distance);

		//7) Pause 1 second

		wait1Msec(1000);

		//8) Move backward (Three Inches=7.62 cm)

		distance = 125;
		drive("down", distance);

		//9) Point turn 33.7 degrees

		distance = 584.13333333;
		drive("rpoint", distance);

		//10) Measure offset from RED base wall (should be from 5' - 7' = 152.4-213.36 cm)
		offset_right = SensorValue[sonarSensor]/60.96;

		//11) Move backward until (offset=(Two Feet Six Inches = 76.2 cm))
		//OR Move backward (Two Feet Four Inches = 71.12 cm)
		//Robot will move into RED Low Zone

		//while offset_right > 857 {
		//  drive("down", 500);
		//  offset_right = SensorValue[sonarSensor]/60.96;
		//}
		//OR
		distance = 857;
		drive("down", distance);

		//12) Point Turn 90 degrees

		distance = 1560;
		drive("rpoint", distance);

		//13) Measure offset
		offset_back = SensorValue[sonarSensor]/60.96;

		//14) Move until (offset=(Ten Feet Six Inches = 320.04 cm)-(half the robot's length))
		//OR Move forward (Nine Feet Eight Inches = 294.64 cm)

		//while offset_back > 5250 {
		//  drive("up", 500);
		//  offset_right = SensorValue[sonarSensor]/60.96;
		//}
		//OR
		distance = 4833.33333;
		drive("up", distance);

		//15) Point Turn 90 Degrees

		distance = 1560;
		drive("rpoint", distance);

		//16) Move forward (Five Feet Six Inches = 167.64 cm)

		distance = 2750;
		drive("up", distance);

  }

}
