#include "Proximity.h"


//Obtains dproximity data
bool Proximity::HasDetected()
{
	proxSensors.initThreeSensors();
	proxSensors.read();
	uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
	uint8_t rightValue = proxSensors.countsFrontWithRightLeds();

	bool objectDetected = leftValue >= sensorThreshold || rightValue >= sensorThreshold;
	if (objectDetected){
		ledYellow(1); return true;
	}
	else return false;

}

Proximity Prox;
