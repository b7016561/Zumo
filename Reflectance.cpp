#include "Reflectance.h"

Reflectance::~Reflectance()
{
}

void Reflectance::Initialisation()
{
	sensors.initFiveSensors();

	//Ensures all values are cleared
	for (int i = 0; i < NUM_SENSORS; i++)
	{
		sensorArray[i] = 0;
	}
}

void Reflectance::Calibrate()
{

	delay(1000);

	//Activate LED
	ledYellow(1);

	ZumoMotor motors;

	SPRINT(Calibrating Sensors...);
	int i;
	for (i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			motors.SetMS(-SCAN_SPEED, SCAN_SPEED);
		else
			motors.SetMS(SCAN_SPEED, -SCAN_SPEED);
		sensors.calibrate();

		delay(25);
	}

	//Deactivtes LED
	ledYellow(0);

	//Resets motors
	motors.SetMS(0, 0);

	SPRINT(Calibration complete...);
}


SensorInformation Reflectance::ReflectanceController()
{
	//Gets sensor info
	GetInfo();
	SensorInformation collisionInfo;
	int collisionCount = 0;

	for (int i = 0; i < NUM_SENSORS; i++)
	{
		//If darkness is detected, increment collisionCount
		if (sensorArray[i] > 200)
		{
			collisionCount++;
		}
	}


	if (collisionCount == NUM_SENSORS / 2)
	{
		//Sets motors to 0 and informs user of collision
		motor.SetMS(0, 0);
#if DISPLAY_COLLISION_INFO
		SPRINT(Collision!);
#endif

		collisionInfo.detected = true;
		collisionInfo.zdirection = 0;
		collisionInfo.sensorCount = collisionCount;

		return collisionInfo;
	}

	//Detects darkness on left side used for turning

	if (sensorArray[0] > 300 || sensorArray[1] > 150)
	{

#if DISPLAY_COLLISION_INFO
		SPRINT(Left side collision!);
#endif

		collisionInfo.detected = true;
		collisionInfo.zdirection = -1;
		collisionInfo.sensorCount = 1;
		
		return collisionInfo;
	}
	//Detects darkness on right side used for turning
	else if (sensorArray[NUM_SENSORS - 1] > 300 || sensorArray[NUM_SENSORS - 2] > 150)
	{

#if DISPLAY_COLLISION_INFO
		SPRINT(Right side collision!);
#endif
		collisionInfo.detected = true;
		collisionInfo.zdirection = 1;
		collisionInfo.sensorCount = 1;
		return collisionInfo;
	}
	return collisionInfo;
}

//Filsl sensorArray with new values
void Reflectance::GetInfo()
{
	//Get new data from reflectance sensors and put in array
	sensors.readLine(sensorArray);

#if DISPLAY_AINFO
	DisplayInfo();
#endif
}

//Displays info obtained by array
void Reflectance::DisplayInfo()
{
	for (int i = 0; i < NUM_SENSORS; i++)
	{
		Serial.print(sensorArray[i]);
		Serial.print("\t");
	}
	Serial.print("\n");
}

Reflectance ReflectArray;
