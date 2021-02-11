#include "InputController.h"

static bool queue[ASCII_RANGE];

void InputController::Initialise()
{
	//Clears input
	Clear();
}

void InputController::Controller()
{
	Clear();

	//If there is input
	if (Serial.available() > 0)
	{
		//Takes the queueue
		int input = Serial.read();

#if DISPLAY_UINPUT
		SPRINT(Key : );
		Serial.print("\t");
		Serial.print((char)input);
#endif
		//Minus min range queueue
		input -= 32;
		//Saves input as the index
		queue[input] = true;
	}
}

void InputController::Clear()
{
	//Sets queueues to false in the array
	for (int i = 0; i < ASCII_RANGE; i++)
	{
		queue[i] = false;
	}
}

bool InputController::KeyPress(const char key)
{
	//Gets the character queueue
	int val = (int)key;
	//Checks the character is valid
	if (val < 32 || val > 127)
	{
		SPRINT(Incorrect input);
		Serial.print("\t");
		Serial.print(key);
		return false;
	}

	val -= 32;

	if (queue[val])
	{
		return true;
	}
	else
	{
		return false;
	}
}
