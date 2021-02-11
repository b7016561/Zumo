#ifndef _ZUMOCORRIDORMODE_H_
#define _ZUMOCORRIDORMODE_H_
#include "ZumoMode.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ZumoCorridorMode : public ZumoMode
{
public:
	ZumoCorridorMode();
	virtual ~ZumoCorridorMode();

	//Initialises Mode
	virtual void InitialiseMode();
	//Updates Mode
	virtual void UpdateMode();
	//Cancels mode
	virtual void CancelMode();


private:

	//Reference to reflectance
	Reflectance reflectArray;

	//Reference to motors
	ZumoMotor zm;

	//Corridor distance times
	float start, finish;

	//Suspends mode until input recieved
	bool suspendMode;

	//Checkers
	//Checks for collision with lines
	void CheckLineDetected();

	//Checks inputs
	void CheckKeyInput();

	//Checks for user forced mode change
	void CheckUserModeChange();

	//Calculates corridor distance
	void CalculateDistance();
};
#endif
