#ifndef _ZUMOROOMMODE_H_
#define _ZUMOROOMMODE_H_
#include "ZumoMode.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



class ZumoRoomMode : public ZumoMode
{
public:

	ZumoRoomMode();
	virtual ~ZumoRoomMode();

	virtual void InitialiseMode();
	virtual void UpdateMode();
	virtual void CancelMode();

private:
	//Detects an object
	bool Detected();
	//Scans
	void Scanner();

	//References
	ZumoMotor zmotor;
	Proximity* prox;

	//Bool value for if a scan is taking place
	bool currentScan;
	//Bool value for if scan has ended
	bool hasEnded;
	
	
};


#endif
