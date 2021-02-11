#ifndef _ZUMOINITIALISEMODE_H_
#define _ZUMOINITIALISEMODE_H_
#include "ZumoMode.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class ZumoInitialiseMode : public ZumoMode
{
public:

	ZumoInitialiseMode();
	virtual ~ZumoInitialiseMode();

	virtual void InitialiseMode();
	virtual void UpdateMode();
	virtual void CancelMode();

};


#endif
