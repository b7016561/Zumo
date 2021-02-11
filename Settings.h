#ifndef _SETTINGS_H_
#define _SETTINGS_H_

//Max motor speed (400 max)
const int MAX_SPEED = 200;

//Run speed 
const int RUN_SPEED = MAX_SPEED / 2;

//Rotate speed when scanning
const int SCAN_SPEED = 180;

//Delay time for turning 90
const int NINETY_DEGREE_TIME = 330;

//Number of reflectance sensors
const int NUM_SENSORS = 5;

//Time to print debug data
const int PRINT_FRAME_COUNT = 5;

//Maximum status
const int MAX_MODE = 5;

//Maximum corridors
const int MAX_CORRIDORS = 3;

//Maximum rooms per corridor
const int MAX_ROOMS = 2;


#endif
