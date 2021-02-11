#ifndef _ZUMOCOMPASS_H_
#define _ZUMOCOMPASS_H_
#include "Settings.h"
#include "Assist.h"
#include "ZumoMotor.h"
#include <Wire.h>
#include <LSM303.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
//Can use gyro if compass isnt reliable 

class ZumoCompass
{
public:

	static ZumoCompass& GetCompassInstance()
	{
		static ZumoCompass* instance = new ZumoCompass();

		return *instance;
	}

	ZumoCompass();
	~ZumoCompass();

	void Initialisation();
	void Calibrate();
	float GetAngle();

private:

	// Converts x and y into a heading in degrees.
	float Heading(LSM303::vector<long> v);

	float AverageHeading();
	float RelativeHeading(float mHeadingFrom, float mHeadingTo);

private:

	LSM303 compass;

};

extern ZumoCompass Compass;

#endif
