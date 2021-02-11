#ifndef _FLOORPLANINFO_H_
#define _FLOORPLANINFO_H_
#include "Settings.h"
#include "Assist.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//Possible zDirections of rooms/corridors
enum DIRECTION
{
	STRAIGHT,
	RIGHT,
	LEFT,
	INVALID
	
};

//Room Structure to contain relevant variables pertaining to the rooms in the floor plan
struct Room
{
	//Room ID for assignation
	int roomID;
	//Whether an object was detected
	bool objectDetected;
	//Time it took down the corridor to get to the room
  float corridorRoomDistance;
	//Direction of room from corridor
	DIRECTION zDirection;

	Room()
	  : roomID(-1), objectDetected(false), corridorRoomDistance(0)
    ,zDirection(DIRECTION::INVALID)
	{
	}
};


//Structure to contain data to do with Corridors
struct Corridor
{
	//ID of the room
	int corridorID;
	//Time taken to drive down the corridor
	float timeTaken;
	//Previous corridor from current, if its the first then it'll be NULL
	Corridor* previousCorridor;
	//Direction to turn to get down this corridor
	DIRECTION zDirectionFromPrevious;
	//Array of rooms 
	Room roomsArray[MAX_ROOMS];
	//Number of rooms leading off a corridor
	int corridorRoomCount;

	//Constructor
	Corridor(): 
		corridorID(0), timeTaken(0), previousCorridor(nullptr),
		zDirectionFromPrevious(INVALID), corridorRoomCount(0)
	{
	}

	//Adds a room 
	void AddRoom(float timeTaken, DIRECTION zDirection)
	{
		//Get the room that needs to be changed
		Room* room = &roomsArray[corridorRoomCount];
		//Sets ID to the current room count
		room->roomID = corridorRoomCount;
		//Sets the time taken down the corridor to the room
		room->corridorRoomDistance = timeTaken;
		//Sets the zDirection of the room in relation to the corridor
		room->zDirection = zDirection;
		//Increase room count by one
		corridorRoomCount++;
	}

	//Getters 
	Room* GetRoom(int index)
	{
		return &roomsArray[index];
	}

	
	Room* GetCurrentRoom()
	{
		return &roomsArray[corridorRoomCount - 1];
	}
};

class FloorPlanInfo
{
	public:

	FloorPlanInfo();
	~FloorPlanInfo();
	
	//Current corridor
	int currentCorridor = 0;

	//Array of corridors
	Corridor corridorArray[MAX_CORRIDORS];

	//Adds a corridor 
	void AddCorridor(DIRECTION zDirection, Corridor* previousCorridor);

	//Getters
	//Gets current corridor
	Corridor* GetCurrentCorridor() { return &corridorArray[currentCorridor]; };

	//Gets the previous corridor from the current one
	Corridor* GetPreviousCorridorFromCurrent();

	//Get the previous corridor to the selected one
	Corridor* GetPreviousCorridor(Corridor* corridor);	
};
#endif
