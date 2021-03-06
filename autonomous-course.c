#pragma config(Sensor, in6,    clawAngle,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  sonarInput,     sensorSONAR_inch)
#pragma config(Motor,  port1,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           claw,          tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorServoContinuousRotation, openLoop)

//+++++++++++++++++++++++++++++++++++++++++++++| Public Integers |++++++++++++++++++++++++++++++++++++++++

int x = 0;
int y = 0;
int z = 0;

//+++++++++++++++++++++++++++++++++++++++++++++| Stop |++++++++++++++++++++++++++++++++++++++++++++++

void pause(int seconds) {
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		wait1Msec(seconds * 1000);
}

//+++++++++++++++++++++++++++++++++++++++++++++| Straight Line |++++++++++++++++++++++++++++++++++++++++

void straightLine(int distance) {
		while(x < distance || y < distance) {

		x = SensorValue[rightEncoder];
		y = SensorValue[leftEncoder];

		motor[leftMotor] = 100;
		motor[rightMotor] = 100;

		if(x > y){
			motor[leftMotor] = 127;
			motor[rightMotor] = 50;
		}

		if(y > x){
			motor[leftMotor] = 50;
			motor[rightMotor] = 127;
		}

	}
	
	x = 0;
	y = 0;
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	
}

//+++++++++++++++++++++++++++++++++++++++++++++| Right Angle Turn |++++++++++++++++++++++++++++++++++++++++

void rightAngleTurn() {
	while(x > -555 && y < 555) {
		
		motor[leftMotor] = 90;
		motor[rightMotor] = -90;
		
		x = SensorValue[rightEncoder];
		y = SensorValue[leftEncoder];

	}
		
	x = 0;
	y = 0;
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	
}

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |++++++++++++++++++++++++++++++++++++++++++++++++++

task main ()
{
	straightLine(4375);
	
	pause(1);

	rightAngleTurn();
	
	pause(1);
	
	//Open the claw
	
	while(z < 3500) {
		
		z = SensorValue[clawAngle];
		
		motor[claw] = - 63;
	
	}
	
	pause(1);
	
	straightLine(1750);
	
	pause(1);
	
	//Close the claw
	
	while(z > 1055) {
		
		z = SensorValue[clawAngle];
		
		motor[claw] = 63;
		
	}
	
	pause(1);
	
	rightAngleTurn();
	
	pause(1);
	
	straightLine(1890);
	
	pause(1);
	
	rightAngleTurn();
	
	pause(1);
	
	straightLine(2150);
	
	pause(1);
	
	//Reopen the claw
	
	//z = 0;
	//SensorValue[clawAngle] = 0;
	
	while(z < 3500) {
		
		z = SensorValue[clawAngle];
		
		motor[claw] = -127;
	
	}
	
	pause(1);
	
	motor[leftMotor] = -127;
	motor[rightMotor] = -127;
	wait1Msec(500);
	
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
