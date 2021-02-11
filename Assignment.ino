#include <LSM303.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "ZumoInitialiseMode.h"
#include "ZumoCorridorMode.h"
#include "ZumoRoomMode.h"
#include "ZumoUserMode.h"
#include "InputController.h"
#include "ZumoMotor.h"
#include "Reflectance.h"
#include "Assist.h"
#include "Settings.h"
#include "FloorPlanInfo.h"

Zumo32U4ButtonA ButtonA;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Motors motors;
Zumo32U4LineSensors sensors;

bool isRunning = true;
ZumoMode* modeList[MAX_MODE];
ZumoMode* currentMode;
FloorPlanInfo floorPlanInfo;
ZumoUserMode userMode;
ZumoInitialiseMode initialiseMode;
ZumoCorridorMode corridorMode;
ZumoRoomMode roomMode;

void setup()
{
  corridorMode.SetFloorPlanInfoPtr(&floorPlanInfo);
  roomMode.SetFloorPlanInfoPtr(&floorPlanInfo);
  userMode.SetFloorPlanInfoPtr(&floorPlanInfo);

  AddMode(&initialiseMode);
  AddMode(&corridorMode);
  AddMode(&roomMode);
  AddMode(&userMode);


  //Start serial communication
  Serial.begin(9600);
  SPRINT(Please press the A Button to initialise..);
  ButtonA.waitForButton();
  ModeChange((int)ZumoMode::ZUMO_MODE::INITIALISE);
}

//Main Loop
void loop()
{
  InputController::Controller();

  //Stops the program from running
  if (InputController::KeyPress('.'))
  {
    isRunning = !isRunning;
  }

  if (isRunning)
  {
    //Check state pointer isn't null
    if (currentMode != nullptr)
    {
      //Check if the state is finished
      if (currentMode->ModeEnded())
      {
        //Go to the next mode
        ModeChange((int)currentMode->GetNextMode());
      }

      currentMode->UpdateMode();
    }
  }
}


//Mode changes
void AddMode(ZumoMode* _mode)
{
  static int i = 0;
  modeList[i] = _mode;
  _mode->SetMode(i);
  i++;
}

void ModeChange(int modeID)
{
#if DISPLAY_CHANGED_MODE
  Serial.print("\nSwitching mode : ");
  Serial.println(modeID);
#endif
  if (currentMode == nullptr)
  {
    currentMode = modeList[modeID];
    currentMode->InitialiseMode();
  }
  else
  {
    currentMode->CancelMode();
    currentMode = modeList[modeID];
    currentMode->InitialiseMode();
  }
}
