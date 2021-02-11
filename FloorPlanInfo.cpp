#include "FloorPlanInfo.h"

FloorPlanInfo::FloorPlanInfo()
{
}

FloorPlanInfo::~FloorPlanInfo()
{
}

//Gets the previous corridor from the array
Corridor* FloorPlanInfo::GetPreviousCorridorFromCurrent()
{
	//Checks current corridor isnt the first
	if (currentCorridor < 0)
	{
		//Returns previous corridor
		return &corridorArray[currentCorridor - 1];
	}
	//Otherwise it returns a nullptr
	return nullptr;
}

//Gets the previous corridor to the selected one
Corridor* FloorPlanInfo::GetPreviousCorridor(Corridor* _corridor)
{
	//Check if selected corridor has a previous
	if (_corridor->previousCorridor == nullptr)
	{
		//If there isn't one return nullptr
		return nullptr;
	}
	else
	{
		//Else get the relevant corridor using it's ID
		return &corridorArray[_corridor->previousCorridor->corridorID];
	}
}

//Adds a new corridor
void FloorPlanInfo::AddCorridor(DIRECTION direction, Corridor* previousCorridor)
{
	//Increment the current corridor for the push
	currentCorridor++;

	//Creates a new corridor object
	Corridor corridor;
	//Sets the direction
	corridor.zDirectionFromPrevious = direction;
	//Sets the previous corridor to the new one
	corridor.previousCorridor = previousCorridor;

	static int corridorID = 1;
	corridor.corridorID = corridorID;

	//Pushes the new corridor into the array
	corridorArray[currentCorridor] = corridor;
	corridorID++;
}
