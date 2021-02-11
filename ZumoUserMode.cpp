#include "ZumoUserMode.h"

ZumoUserMode::ZumoUserMode()
{
}

ZumoUserMode::~ZumoUserMode()
{
}

void ZumoUserMode::InitialiseMode()
{
#if DISPLAY_CHANGED_MODE
	SPRINT(Starting mode: User);
#endif
	modeEnded = false;
	isWaitingD = false;

	nextMode = ZUMO_MODE::USER;
}


void ZumoUserMode::UpdateMode()
{
	//Checks if waiting
	if (!isWaitingD)
	{
		CheckForMovementFromUser();
		CheckForChangedMode();
	}
	if (isWaitingD)
	{
		CheckForDirectionChangeFromUser();
	}
}


void ZumoUserMode::CancelMode()
{
#if DISPLAY_CHANGED_MODE
	SPRINT(Cancelling mode: User);
#endif
}


void ZumoUserMode::CheckForMovementFromUser()
{
	//If the user wants to go forward
	if (InputController::KeyPress('w'))
	{
		//moves robot forward
		zmotor.SetMS(RUN_SPEED, RUN_SPEED);
	}
	//If the 'a' key is pressed
	if (InputController::KeyPress('a'))
	{
		//Rotate slightly the left
		zmotor.Rotate(-1, 50, false);
	}
	//If user wants to go backwards
	if (InputController::KeyPress('s'))
	{
		if (ZumoMotor::GetLMS() != 0 && ZumoMotor::GetRMS() != 0)
		{
			//Stops robot if not already stationary
			zmotor.SetMS(0, 0);
		}
		//Moves robot backwards
		else
		{
			zmotor.SetMS(-RUN_SPEED, -RUN_SPEED);
		}
	}
	//If user wants to go right
	if (InputController::KeyPress('d'))
	{
		//Rotates robot right
		zmotor.Rotate(1, 50, false);
	}
	//If the user wants to rotate left 90 degrees
	if (InputController::KeyPress('o'))
	{
		//Rotates robot left
		zmotor.RotateLR(-1, false);
   modeEnded = true;
   nextMode = ZUMO_MODE::CORRIDOR;
	}
	//If user wants to rotate right 90 degrees
	if (InputController::KeyPress('p'))
	{
		//Rotate 90 degrees to the right
		zmotor.RotateLR(1, false);
    modeEnded = true;
    nextMode = ZUMO_MODE::CORRIDOR;
	}

	//If user wants to stop the robot with the spacebar
	if (InputController::KeyPress(32))
	{
		//Stop
		zmotor.SetMS(0, 0);
	}
}


void ZumoUserMode::CheckForChangedMode()
{
	//If user wants to move to corridor mode
	if (InputController::KeyPress('C'))
	{
		//Changes next mode to corridor
		
		//now waiting for user input regarding zDirection
		isWaitingD = true;

		SPRINT(Is the Corridor [l]eft[r]ight or [s]traight ahead);
    nextMode = ZUMO_MODE::CORRIDOR;

	}
	//If the user presses right
	if (InputController::KeyPress('R'))
	{
		//Changes next mode to room
		nextMode = ZUMO_MODE::ROOM;
		//now waiting for user input regarding zDirection
		isWaitingD = true;

		SPRINT(Is the Room [l]eft or [r]ight);
	}
}


void ZumoUserMode::CheckForDirectionChangeFromUser()
{
	//If the user wants to rotate right
	if (InputController::KeyPress('r'))
	{
		//Rotates right 90 degrees
		zmotor.RotateLR(1, false);
		//Mode ended
		modeEnded = true;


		//If next mode is corridor
		if (nextMode == ZUMO_MODE::CORRIDOR)
		{
			//Adds the new one to the floorPlanInfo object
			floorPlanInfo->AddCorridor(DIRECTION::RIGHT, floorPlanInfo->GetCurrentCorridor());
		}
		//If next mode is room
		else if (nextMode == ZUMO_MODE::ROOM)
		{
			//updates the object for room
			Corridor* currentCorridor = floorPlanInfo->GetCurrentCorridor();
			currentCorridor->GetCurrentRoom()->zDirection = DIRECTION::RIGHT;
		}		
	}

	//If the user wants to rotate left
	if (InputController::KeyPress('l'))
	{
		//Rotates robot left 90 degrees
		zmotor.RotateLR(-1, false);
		modeEnded = true;

		//If next mode is corridor
		if (nextMode == ZUMO_MODE::CORRIDOR)
		{
			//Adds the new one to the floorPlanInfo object
			floorPlanInfo->AddCorridor(DIRECTION::LEFT, floorPlanInfo->GetCurrentCorridor());
		}
		//If next mode is room
		else if (nextMode == ZUMO_MODE::ROOM)
		{
			//updates the object for the room
			Corridor* currentCorridor = floorPlanInfo->GetCurrentCorridor();
			currentCorridor->GetCurrentRoom()->zDirection = DIRECTION::LEFT;
		}

	}

	//If the user wants to go straight ahead
	if (InputController::KeyPress('s'))
	{
		SPRINT(Continuing..);
		modeEnded = true;
	}


}
