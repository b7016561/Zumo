#ifndef _ZUMOUSERMODE_H_
#define _ZUMOUSERMODE_H_
#include "ZumoMotor.h"
#include "ZumoMode.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ZumoUserMode : public ZumoMode
{
public:

	ZumoUserMode();
	virtual ~ZumoUserMode();

	virtual void InitialiseMode();
	virtual void UpdateMode();
	virtual void CancelMode();

private:
	//References ZumoMotor
	ZumoMotor zmotor;

	//Used for rotation after mode change
	bool isWaitingD;
  
	//Checks for movement input from user
	void CheckForMovementFromUser();
	//Checks if user has changed the mode
	void CheckForChangedMode();
	//checks for direction change
	void CheckForDirectionChangeFromUser();

	


	
};

#endif
