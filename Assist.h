#ifndef _ASSIST_H_
#define _ASSIST_H_

//These are used for dissplaying messages
#define SPRINT(txt) { Serial.print("\n"); Serial.print(#txt); Serial.print(" "); };

#define DISPLAY_CHANGED_MODE 1
#define DISPLAY_AINFO 0
#define DISPLAY_UINPUT 0
#define DISPLAY_COLLISION_INFO 0
#define DISPLAY_ZUMO_SPEED 0

//Used for compass
#define CRA_REG_M_220HZ    0x1C 
#define CRB_REG_M_2_5GAUSS 0x60 


#endif

