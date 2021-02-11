#ifndef _INPUTCONTROLLER_H_
#define _INPUTCONTROLLER_H_
#include "Assist.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

const int ASCII_RANGE = 95;

class InputController
{
public:

	//Initialisation
	static void Initialise();
	//Clears queued input 
	static void Clear();
	//Controls input
	static void Controller();
	//Key press checker
	static bool KeyPress(const char key);
};

extern InputController InputController;

#endif

