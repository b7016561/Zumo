#include "ZumoInitialiseMode.h"


ZumoInitialiseMode::ZumoInitialiseMode()
{
}

ZumoInitialiseMode::~ZumoInitialiseMode()
{
}


void ZumoInitialiseMode::InitialiseMode()
{
	//sets mode ended to false
	modeEnded = false;


	//Initialises InputController
	InputController::Initialise();

	//Initialises Reflectance
	Reflectance::GetReflect().Initialisation();

	//Calibration
	Reflectance::GetReflect().Calibrate();
  
	//Prepares robot for corridor
   nextMode = ZUMO_MODE::CORRIDOR;
}


void ZumoInitialiseMode::UpdateMode()
{
	if (InputController::KeyPress('i'))
	{
		modeEnded = true;
   
	}
}


void ZumoInitialiseMode::CancelMode()
{
}
