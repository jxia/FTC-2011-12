#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  motorA,          frontTread,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          backTread,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeftWheel, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontRightWheel, tmotorNormal, openLoop)
<<<<<<< HEAD
#pragma config(Motor,  mtr_S1_C2_1,     backRightWheel, tmotorNormal, openLoop) 
#pragma config(Motor,  mtr_S1_C2_2,     backLeftWheel, tmotorNormal, openLoop, reversed) 
#pragma config(Motor,  mtr_S1_C3_1,     leftArm,       tmotorNormal, openLoop, reversed) 
#pragma config(Motor,  mtr_S1_C3_2,     rightArm,      tmotorNormal, PIDControl, encoder) 
=======
#pragma config(Motor,  mtr_S1_C2_1,     backRightWheel, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     backLeftWheel, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     leftArm,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     rightArm,      tmotorNormal, PIDControl, encoder)
>>>>>>> f6ff696db5205e7ceb99d207250bdf167af3457d
#pragma config(Servo,  srvo_S1_C4_1,    leftClaw,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    rightClaw,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

//-----------Constants------------------
#define WHEELSPEED 75
#define ARMSPEED 20
#define TREADSPEED 50
#define LCLAWOPEN 127
#define LCLAWCLOSE 255
#define RCLAWOPEN 128
#define RCLAWCLOSE 0
//--------------------------------------
// when give your motors/servos values, use these constants, not numbers
// so that if we need to change them, they're easy to access

void initialize()
{
  motor[frontLeftWheel] = 0;
  motor[frontRightWheel] = 0;
  motor[backLeftWheel] = 0;
  motor[backRightWheel] = 0;
  motor[leftArm] = 0;
  motor[rightArm] = 0;
  nMotorEncoder[rightArm] = 0;
  servo[leftClaw] = LCLAWOPEN;
  servo[rightClaw] = RCLAWOPEN;
  nSyncedMotors = synchAB;
  nSyncedTurnRatio = 100;
  nMotorEncoder[frontTread] = 0;
  motor[frontTread] = 0;
}

bool mode (bool switchMode)
{
  return !switchMode;
}


task main()
{
  int position1 = 0;
  int position2 = 0;
  bool fixedSpeed = true;
  bool treadMaxSpeed = false;
  initialize();

  //Used for calculating size of triangle of motion that will define point turning left/right
  float tan_angle_leftright = 1.0 / sqrt(3); // tan(PI / 6), Graph of y=tan(angle_leftright) used for point turn left/right; MUST BE IN RADIANS

  //Used for calculating size of triangle of motion that will define moving forward/back
  float tan_angle_updown = sqrt(3);          // tan(PI / 3), Graph of y=tan(angle_updown) used for forward/back; MUST BE IN RADIANS

  while (true) {

    getJoystickSettings(joystick);


    //------------Driving-----------------

    //Primary Objective:
    //     - Make robot go forward/backward/point-turn when
    //       the left joystick is pushed up/down/left/right.
    //     - Wheel speeds should be set as WHEELSPEED.
    //     - When nothing is pushed, wheels should stop.
    //     - Make sure to create a 5 unit deadzone around the joystick
    //       (the joystick doesn't always center exactly on 0)
    //     - all wheels should be slaved to the front-left wheel
    //
    //Secondary Objective:
    //     - Make robot swing-turn when left joystick is pushed
    //       diagonally (ie. pushed into a corner)

    int wheels_x1;
    int wheels_y1;
    int left_wheelsPower;
    int right_wheelsPower;

    wheels_x1 = joystick.joy1_x1;	//x-value = left-right joystick movement
    wheels_y1 = joystick.joy1_y1;	//y-value = up-down joystick movmeent

    float tan_line_updown = tan_angle_updown * wheels_x1;
    float tan_line_leftright = tan_angle_leftright * wheels_x1;

    /*RANGES OF MOTION
    Take grid of joystick x-values and y-values, split into twelve 30 degree triangles
    Use graphs of y=tan(30)x, y=-tan(30)x, y=tan(60)x, y=-tan(60)x  -
    To alter sizes of triangles, change the degree (e.g. tan(45))
    Test to see which triangle values fall in
    Depending on triangle, move forwards/backwards/point turn/swing turn
    */

    if (joy1Btn(10) == 1) {
      fixedSpeed = mode(fixedSpeed);
    }

    if (fixedSpeed == true){

      if (abs(wheels_x1) > 10 && abs(wheels_y1) > 10) {	//If in deadzone, ignore movement - no need to run useless code
        if (wheels_y1 <= tan_line_leftright) {
          //Must be either Right Point, Right Back Swing, Backwards, or Left Back Swing
          //!IMPORTANT: Code works by order, so code CANNOT be merged unless order is followed
          if (wheels_y1 >= -tan_line_leftright) {
            //Right Point Turn -- Move right tread backwards, left tread forwards
            left_wheelsPower = WHEELSPEED;
            right_wheelsPower = -WHEELSPEED;
          } else if (wheels_y1 >= -tan_line_updown) {
            //Swing Turn Backwards Right
            left_wheelsPower = -WHEELSPEED;
            right_wheelsPower = 0;
          } else if (wheels_y1 <= tan_line_updown) {
            //Backward -- Move both treads backwards
            left_wheelsPower = -WHEELSPEED;
            right_wheelsPower = -WHEELSPEED;
          } else {
            //Swing Turn Backwards Left
            left_wheelsPower = 0;
            right_wheelsPower = -WHEELSPEED;
          }
        } else {
          //Must be either Left Point, Left Swing, Forwards, or Right Swing
          //!IMPORTANT: Code works by order, so code CANNOT be merged unless order is followed
          if (wheels_y1 <= -tan_line_leftright) {
            //Left Point Turn -- Move right tread forwards, left tread backwards
            left_wheelsPower = -WHEELSPEED;
            right_wheelsPower = WHEELSPEED;
          } else if (wheels_y1 <= -tan_line_updown) {
            //Swing Turn Left
            left_wheelsPower = 0;
            right_wheelsPower = WHEELSPEED;
          } else if (wheels_y1 >= tan_line_updown) {
            //Forward -- Move both treads forwards
            left_wheelsPower = WHEELSPEED;
            right_wheelsPower = WHEELSPEED;
          } else {
            //Swing Turn Right
            left_wheelsPower = WHEELSPEED;
            right_wheelsPower = 0;
          }
        }
      } else {		 //Joystick is in dead zone - set powers to zero
        left_wheelsPower = 0;
        right_wheelsPower = 0;
      }

    } else{

      if (abs(wheels_x1) > 10 && abs(wheels_y1) > 10) {	//If in deadzone, ignore movement - no need to run useless code
        if (wheels_y1 <= tan_line_leftright) {
          //Must be either Right Point, Right Back Swing, Backwards, or Left Back Swing
          //!IMPORTANT: Code works by order, so code CANNOT be merged unless order is followed
          if (wheels_y1 >= -tan_line_leftright) {
            //Right Point Turn -- Move right tread backwards, left tread forwards
            left_wheelsPower = (int)(wheels_x1/1.27);
            right_wheelsPower = -(int)(wheels_x1/1.27);
          } else if (wheels_y1 >= -tan_line_updown) {
            //Swing Turn Backwards Right
            left_wheelsPower = (int)(wheels_y1/1.27);
            right_wheelsPower = 0;
          } else if (wheels_y1 <= tan_line_updown) {
            //Backward -- Move both treads backwards
            left_wheelsPower = (int)(wheels_y1/1.27);
            right_wheelsPower = (int)(wheels_y1/1.27);
          } else {
            //Swing Turn Backwards Left
            left_wheelsPower = 0;
            right_wheelsPower = (int)(wheels_y1/1.27);
          }
        } else {
          //Must be either Left Point, Left Swing, Forwards, or Right Swing
          //!IMPORTANT: Code works by order, so code CANNOT be merged unless order is followed
          if (wheels_y1 <= -tan_line_leftright) {
            //Left Point Turn -- Move right tread forwards, left tread backwards
            left_wheelsPower = (int)(wheels_x1/1.27);
            right_wheelsPower = -(int)(wheels_x1/1.27);
          } else if (wheels_y1 <= -tan_line_updown) {
            //Swing Turn Left
            left_wheelsPower = 0;
            right_wheelsPower = (int)(wheels_y1/1.27);
          } else if (wheels_y1 >= tan_line_updown) {
            //Forward -- Move both treads forwards
            left_wheelsPower = (int)(wheels_y1/1.27);
            right_wheelsPower = (int)(wheels_y1/1.27);
          } else {
            //Swing Turn Right
            left_wheelsPower = (int)(wheels_y1/1.27);
            right_wheelsPower = 0;
          }
        }
      } else {		 //Joystick is in dead zone - set powers to zero
        left_wheelsPower = 0;
        right_wheelsPower = 0;
      }

    }

    //Drive Code
    motor[frontLeftWheel] = left_wheelsPower;
    motor[backLeftWheel] = left_wheelsPower;
    motor[frontRightWheel] = right_wheelsPower;
    motor[backRightWheel] = right_wheelsPower;

    //------------------------------------


    //------------Arms--------------------

    //Primary Objective:
    //     - raise arm while btn 5 pressed, lower arm while btn 6 pressed
    //     - when neither btn 5 or 6 is pressed, arm should stop
    //     - arm speed should be set as ARMSPEED
    //     - the right arm should be slaved to the left arm
    //
    //Secondary Objective:
    //     - see if you can find a way to get the arms to rotate to a predetermined position and then stop


    //if (joy1Btn(5) == 1 || joy1Btn(6) == 1) {        //IF ARM IS SUPPOSED TO BE MOVING...
      if (servo[leftClaw] == LCLAWCLOSE) {             //IF HOLDING A BOX...
        if (joy1Btn(5) == 1) {
          //MOVE ARM UP 80% POWER
          motor[leftArm] = -ARMSPEED * 4;
          motor[rightArm] = -ARMSPEED * 4;
        } else if (joy1Btn(6) == 1) {
          //MOVE ARM DOWN 80% POWER
          motor[leftArm] = ARMSPEED;
          motor[rightArm] = ARMSPEED;
        } else {
          //DON'T MOVE ARM
          motor[leftArm] = 0;
          motor[rightArm] = 0;
        }
      } else {                                         //IF NOT HOLDING A BOX...
        if (joy1Btn(5) == 1) {
          //MOVE ARM UP 20% POWER
          motor[leftArm] = -ARMSPEED;
          motor[rightArm] = -ARMSPEED;
        } else if (joy1Btn(6) == 1) {
          //MOVE ARM DOWN 20% POWER
          motor[leftArm] = ARMSPEED;
          motor[rightArm] = ARMSPEED;
        } else {
          //DON'T MOVE ARM
          motor[leftArm] = 0;
          motor[rightArm] = 0;
        }
      }
      //UPDATE ENCODER VALUES (MOTOR POSITION)
      position1 = nMotorEncoder[rightArm];
      position2 = position1;
    /*} else {                                        //IF ARM ISN'T SUPPOSED TO BE MOVING...
      position2 = position1;                        //COMPARE CURRENT MOTOR POSITION WITH PREVIOUS POSITION. ARE THEY THE SAME?
      position1 = nMotorEncoder[rightArm];
      if (position1 < (position2-10)) {                     //NO, CURRENT POSIITON IS LOWER THAN PREVIOUS POSITION, MOVE ARM UP
        motor[leftArm] = -ARMSPEED * 4;
        motor[rightArm] = -ARMSPEED * 4;
      } else if (position1 > (position2+10)) {              //NO, CURRENT POSITION IS HIGHER THAN PREVIOUS POSIITON, MOVE ARM DOWN
        motor[leftArm] = ARMSPEED;
        motor[rightArm] = ARMSPEED;
      } else {                                              //YES, DO NOTHING
        motor[leftArm] = 0;
        motor[rightArm] = 0;
      }
    }*/

    //------------------------------------


    //-----------Claws--------------------

    //Primary Objective:
    //     - close claws when btn 7 pressed, open claws when btn 8 pressed (claws should start open)
    //     - opening positions for left/right claws are LCLAWOPEN and RCLAWOPEN
    //     - closing positions for left/right claws are LCLAWCLOSE and RCLAWCLOSE

    if (joy1Btn(7) == 1) {
      //close left claw
      servo[leftClaw] = LCLAWCLOSE;
      //close right claw
      servo[rightClaw] = RCLAWCLOSE;
    } else if (joy1Btn(8) == 1) {
      //open left claw
      servo[leftClaw] = LCLAWOPEN;
      //open right claw
      servo[rightClaw] = RCLAWOPEN;
    }
    //------------------------------------


    //-----------Tread--------------------

    //Primary Objective:
    //     - if btn 1 is pressed, have tread move forward until btn 2 is pressed.
    //     - tread should move at speed TREADSPEED

    if (joy1Btn(9) == 1) {
      treadMaxSpeed=mode(treadMaxSpeed);
    }

    if (treadMaxSpeed == false){
      if (joystick.joy1_TopHat == 0 && nMotorEncoder[frontTread] <= 300) {
        motor[frontTread] = TREADSPEED;
      } else if (joystick.joy1_TopHat == 4 && nMotorEncoder[frontTread] >= 50) {
        motor[frontTread] = -TREADSPEED;
      } else{
        motor[frontTread] = 0;
      }
    } else{
      if (joystick.joy1_TopHat == 0 && nMotorEncoder[frontTread] <= 215) {
        motor[frontTread] = TREADSPEED*2;
      } else if (joystick.joy1_TopHat == 4 && nMotorEncoder[frontTread] >= 100) {
        motor[frontTread] = -TREADSPEED*2;
      } else{
        motor[frontTread] = 0;
      }
    }

    //------------------------------------
  }
}