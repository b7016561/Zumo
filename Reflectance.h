#ifndef _REFLECTANCE_H_
#define _REFLECTANCE_H_
#include <Zumo32U4.h>
#include "Settings.h"
#include "Assist.h"
#include "ZumoMotor.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
extern Zumo32U4LineSensors sensors;
//Might have to define the Zumo linesensors in the sketch and use extern reference to them


struct SensorInformation
{
	//Whether the sensor has dectected something
	bool detected;
	//Detection direction
	int zdirection;
	//Sensors detected count
	int sensorCount;

	SensorInformation()
	: detected(false), zdirection(0), sensorCount(0)
	{
	}
};

class Reflectance
{
public:

	~Reflectance();
	SensorInformation ReflectanceController();
	void Initialisation();
	void Calibrate();
	
	//Static function to get a reference to the array instance
	static Reflectance& GetReflect()
	{
		//Creates static reference to the array
		static Reflectance* inst = new Reflectance();

		//Return pointer
		return *inst;
	}

private:

	ZumoMotor motor;
	unsigned int sensorArray[NUM_SENSORS];

	//Used to obtain infromation for the array above
	void GetInfo();

	//Displays the information stored in the array
	void DisplayInfo();

	
	
};

extern Reflectance ReflectArray;

#endif
