#ifndef _ZUMOMODE_H_
#define _ZUMOMODE_H_
#include "Settings.h"	
#include "Assist.h"
#include "InputController.h"	
#include "ZumoMotor.h"
#include "Reflectance.h"
#include "Proximity.h"
#include "FloorPlanInfo.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif




class ZumoMode
{
public:

	//Holds the various states
	enum ZUMO_MODE
	{
		INITIALISE,
    CORRIDOR,
		ROOM,
		USER
	};

	ZumoMode();
	virtual ~ZumoMode();

	virtual void InitialiseMode() = 0;
	virtual void UpdateMode() = 0;
	virtual void CancelMode() = 0;

	//Setters
	//Set the mode number
	void SetMode(int mode) { modeID = mode; };
	//Sets a pointer for mode access to FloorPlan information
	void SetFloorPlanInfoPtr(FloorPlanInfo* info) { floorPlanInfo = info; };

	//Getter
	//Get the number of the mode
	int GetMode() const { return modeID; };
	//Get the mode that is connected to this one i.e. corridor -> room
	ZUMO_MODE GetNextMode() { return nextMode; };

	//Checker
	//Check whether mode has ended
	bool ModeEnded() const { return modeEnded; };

protected:

	//ModeID
	unsigned int modeID = -1;
	bool modeEnded = false;

	//Following Mode after the current one
	ZUMO_MODE nextMode;
	FloorPlanInfo* floorPlanInfo;

};
#endif
