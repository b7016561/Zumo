#include "ZumoMotor.h"

int ZumoMotor::lms;
int ZumoMotor::rms;

//Rotates the Zumo
void ZumoMotor::Rotate(const int direction, int zdelay, bool cont)
{

	switch (direction)
	{
	case -1:
		SetMS(-MAX_SPEED, MAX_SPEED);
		break;

	case 1:
		SetMS(MAX_SPEED, -MAX_SPEED);
		break;
	}

	delay(zdelay);

	if (cont)
	{
		SetMS(RUN_SPEED, RUN_SPEED);
	}
	else
	{
		SetMS(0, 0);
	}
}

//Rotates the Zumo left or right a quarter turn
void  ZumoMotor::RotateLR(const int direction, bool cont)
{
	switch (direction)
	{
	case -1:
		SetMS(-MAX_SPEED, MAX_SPEED);
		break;

	case 1:
		SetMS(MAX_SPEED, -MAX_SPEED);
		break;
	}

	delay(NINETY_DEGREE_TIME);

	if (cont)
	{
		SetMS(RUN_SPEED, RUN_SPEED);
	}
	else
	{
		SetMS(0, 0);
	}
}

//Sets speed of the motors
void  ZumoMotor::SetMS(int ls, int rs)
{
	LimitMS(ls);
	LimitMS(rs);

#if DISPLAY_ZUMO_SPEED
	SPRINT(Changing Zumo motor speed L/R: );
	Serial.print(ls);
	Serial.print("\t");
	Serial.print(rs);
#endif

	motors.setSpeeds(ls, rs);
	lms = ls;
	rms = rs;
}

//Sets the speed to the left motor
void ZumoMotor::SetLMS(int ls)
{
	LimitMS(ls);

	motors.setSpeeds(ls, rms);
	lms = ls;
}

//Sets the speed to the right motor
void  ZumoMotor::SetRMS(int rs)
{
	LimitMS(rs);

	motors.setSpeeds(lms, rs);
	rms = rs;
}

//Limits the speed of the motors
void  ZumoMotor::LimitMS(int& pSpeed)
{
	if (pSpeed > MAX_SPEED)
	{
		pSpeed = MAX_SPEED;
	}
	else if (pSpeed < -MAX_SPEED)
	{
		pSpeed = -MAX_SPEED;
	}
}

ZumoMotor Motors;
