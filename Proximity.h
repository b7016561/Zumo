#ifndef _PROXIMITY_H_
#define _PROXIMITY_H_
#include <Zumo32U4.h>
#include <Wire.h>
#include "Assist.h"
#include "Settings.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
extern Zumo32U4ProximitySensors proxSensors;


class Proximity
{
public:

	bool HasDetected();

private:

	const uint8_t sensorThreshold = 1;
	
};

extern Proximity Prox;

#endif
