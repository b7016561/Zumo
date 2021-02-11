#include "ZumoCorridorMode.h"

ZumoCorridorMode::ZumoCorridorMode()
{
}

ZumoCorridorMode::~ZumoCorridorMode()
{
}


void ZumoCorridorMode::InitialiseMode()
{
	//Checks if mode has ended
	modeEnded = false;

	//Ensures mode isnt suspended
	suspendMode = false;

	//Gets reflective reference
	reflectArray = Reflectance::GetReflect();

	//Zumo set to travel forward
	zm.SetMS(RUN_SPEED, RUN_SPEED);

	//Get start time
	start = millis();
}

//Updates mode
void ZumoCorridorMode::UpdateMode()
{
	if (!suspendMode)
	{
		//Line detection
		CheckLineDetected();

		CheckUserModeChange();
	}
	else
	{
		CheckUserModeChange();
	}

}

//Cancels mode
void ZumoCorridorMode::CancelMode()
{
}

//Checks for line detection and will then move
void ZumoCorridorMode::CheckLineDetected()
{
	SensorInformation collisionInfo = reflectArray.ReflectanceController();

	if (collisionInfo.detected == true)
	{
		//If a wall is detected ahead
		if (collisionInfo.sensorCount > 1 && collisionInfo.zdirection == 0)
		{
			//Stops motors
			zm.SetMS(0, 0);

			// Gives control to user
			modeEnded = true;
     SPRINT(rotate left[o] or right[p]?);
			nextMode = ZUMO_MODE::USER;



			//Get finishing time
			finish = millis();
			CalculateDistance();

		}
		//Used to keep zumo within corridor lines
		else if (collisionInfo.sensorCount == 1)
		{
			//Left side detection
			if (collisionInfo.zdirection == -1)
			{
				zm.Rotate(1, 30, true);
			}
			//Right side detection
			else if (collisionInfo.zdirection == 1)
			{
				zm.Rotate(-1, 30, true);
			}
		}

	}
}

//Checks user inputs
void ZumoCorridorMode::CheckKeyInput()
{
	//If spacebar key is pressed or 's'
	if (InputController::KeyPress(32) || InputController::KeyPress('s'))
	{
		//Stops motors
		zm.SetMS(0, 0);

		//Gets end time
		finish = millis();

		suspendMode = true;

		SPRINT(Cancelling corridor mode);
		SPRINT(new[C]orridor or new[R]oom?);
	}
}

//Checks whether use has changed states
void ZumoCorridorMode::CheckUserModeChange()
{
	if (InputController::KeyPress('C'))
	{
		//Calculate corridor length for storage
		CalculateDistance();
    zm.SetMS(0, 0);
		//sets next mode to user mode
		nextMode = ZUMO_MODE::USER;
   
		modeEnded = true;
   
	}
	if (InputController::KeyPress('R'))
	{
		float timeTotal = finish - start;
		//Adds room to relevant corridor
		floorPlanInfo->GetCurrentCorridor()->AddRoom(timeTotal, DIRECTION::INVALID);
    zm.SetMS(0, 0);
		SPRINT(enter [R] again to start room mode)
		nextMode = ZUMO_MODE::USER;
		modeEnded = true;
	}
	if (InputController::KeyPress('U'))
	{
		zm.SetMS(0, 0);
		nextMode = ZUMO_MODE::USER;
		modeEnded = true;
	}
}

//Calculates corridor distance time
void ZumoCorridorMode::CalculateDistance()
{
	float currentCorridorTime = finish - start;

	float overallCorridorTime = currentCorridorTime;

	Corridor* corridor = floorPlanInfo->GetCurrentCorridor();

	//Loop through all rooms
	for (int i = 0; i < corridor->corridorRoomCount; i++)
	{
		//Add the room time onto the overall time
		overallCorridorTime += corridor->GetRoom(i)->corridorRoomDistance;
	}


	//adds the time taken to floorplaninfo
	floorPlanInfo->GetCurrentCorridor()->timeTaken = overallCorridorTime;

	SPRINT(Rough corridor time : );
	Serial.print(overallCorridorTime / 1000);
	Serial.print(" for corridor : ");
	Serial.print(floorPlanInfo->currentCorridor);
}
