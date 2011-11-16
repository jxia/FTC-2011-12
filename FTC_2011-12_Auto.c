void drive (string auto_command) {




	if(auto_command="rpoint") {
	        //Check for right movement
		//Right Point Turn -- Move right tread backwards, left tread forwards
		left_wheelsPower=WHEELSPEED;
		right_wheelsPower=-WHEELSPEED;

	}else if(auto_command="lpoint") {
		//Check for left movement
		//Left Point Turn -- Move right tread forwards, left tread backwards
		left_wheelsPower=-WHEELSPEED;
		right_wheelsPower=WHEELSPEED;

	}else if(auto_command="up") {
		//Check for up movement
		//Forward -- Move both treads forwards
		left_wheelsPower=WHEELSPEED;
		right_wheelsPower=WHEELSPEED;

	}else if(auto_command="down") {
		//Check for down movement
		//Backward -- Move both treads backwards
		left_wheelsPower=-WHEELSPEED;
		right_wheelsPower=-WHEELSPEED;

	}else if(auto_command="rswing") {	//SWING TURN RIGHT
		left_wheelsPower=WHEELSPEED;
		right_wheelsPower=WHEELSPEED/2;

	}else if(auto_command="lswing") {	//SWING TURN LEFT
		left_wheelsPower=WHEELSPEED/2;
		right_wheelsPower=WHEELSPEED;

	}else if(auto_command="lswingback") {	//SWING TURN BACKWARDS LEFT
		left_wheelsPower=-WHEELSPEED/2;
		right_wheelsPower=-WHEELSPEED;	
			}
	}else if(auto_command="rswingback") {	//SWING TURN BACKWARDS RIGHT
		left_wheelsPower=-WHEELSPEED;
		right_wheelsPower=-WHEELSPEED/2;

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


}
