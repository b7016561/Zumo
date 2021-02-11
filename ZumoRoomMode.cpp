#include "ZumoRoomMode.h"

ZumoRoomMode::ZumoRoomMode()
{
}

ZumoRoomMode::~ZumoRoomMode()
{
}

void ZumoRoomMode::InitialiseMode()
{
	//moves the robot into the room
	zmotor.SetMS(RUN_SPEED, RUN_SPEED);
	delay(500);
	zmotor.SetMS(0, 0);

	
	currentScan = false;
	modeEnded = false;
	hasEnded = false;
}

void ZumoRoomMode::UpdateMode()
{
	//If it isnt currently scannning
	if (currentScan == false)
	{
		//Scans
		Scanner();
	}

	//If scan has ended
	if (hasEnded == true)
	{
		//Gives control to the user
		nextMode = ZUMO_MODE::USER;
		modeEnded = true;
	}
}

void ZumoRoomMode::CancelMode()
{
}


void ZumoRoomMode::Scanner()
{
	delay(1000);

	//Activates red led to show its scanning
	ledRed(1);

	SPRINT(Scanning....);
	currentScan = true;

	//Counts number of detections
	int detectedCount = 0;

	//Allows the robot to sweep the room
	for (int i = 0; i < 80; i++)
	{
		if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
			zmotor.SetMS(-SCAN_SPEED, SCAN_SPEED);
		else
			zmotor.SetMS(SCAN_SPEED, -SCAN_SPEED);

		delay(30);


		//If object is detected
		if (Detected())
		{
			detectedCount++;
		}
	}

	//Stops sweeping
	zmotor.SetMS(0, 0);
	SPRINT(Scan completed...);

	//If an object has been detectedd
	if (detectedCount >= 1)
	{
		//Gets current corridor
		Corridor* corridor = floorPlanInfo->GetCurrentCorridor();

		//Gets current room
		Room* room = corridor->GetCurrentRoom();

		//Updates there has been an object found
		room->objectDetected = true;

		SPRINT(Object detected - Room: );
    
		Serial.print(room->roomID);
		Serial.print(" Corridor: ");
		Serial.print(corridor->corridorID);
	}
	else
	{
		SPRINT(No objects detected);
	}

	//Deactives LED
	ledRed(0);

	//Returns robot to corridor
	zmotor.SetMS(-RUN_SPEED, -RUN_SPEED);
	delay(500);
	zmotor.SetMS(0, 0);


	//Scans ended
	hasEnded = true;
}

//Calls upon the proximity checker
bool ZumoRoomMode::Detected()
{
	if (prox->HasDetected() == true)
	{
		SPRINT(Detected:);
		Serial.print("Detected");
		return true;
	}
	else return false;
};
