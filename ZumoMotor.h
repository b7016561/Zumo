#ifndef _ZUMOMOTOR_H_
#define _ZUMOMOTOR_H_
#include "Settings.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Zumo32U4.h>
extern Zumo32U4Motors motors; 

class ZumoMotor
{

public:

	//Rotatess the Zumo
	void Rotate(const int direction, int delay, bool cont);

	void RotateLR(const int direction, bool cont);

	//Sets both motors speeds
	void SetMS(int ls, int rs);

	//Sets the speed to the left motor
	void SetLMS(int ls);

	//Sets the speed to the right motor
	void SetRMS(int rs);

	//Gets the value of the left motor speed
	static int GetLMS() { return lms; };

	//Gets the value of the right motor speed
	static int GetRMS() { return rms; };

private:

	//Limits the value of the motor speeds
	static void LimitMS(int& speed);

private:

	

	static int lms;
	static int rms;

};

extern class ZumoMotor Motors;


#endif
