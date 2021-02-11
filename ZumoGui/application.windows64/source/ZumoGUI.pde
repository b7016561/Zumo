
import processing.serial.*;
import g4p_controls.*;

Serial zumoPort;  // Create object from Serial class
boolean isAbleLeft;
boolean isAbleRight;

String currentValue;

enum ZUMO_MODE
{
  INITIALISE,
  USER,
  CORRIDOR
}

ZUMO_MODE mode;

boolean tog;

void setup() 
{
    createGUI();
    
  ModeChange(ZUMO_MODE.INITIALISE);
  
  size(1024, 768);
 
  String portName = "COM4";
  
  zumoPort = new Serial(this, portName, 9600);
   tog = false;
}

void isKeyPress() 
{
  zumoPort.write(key);
  
  if(key == '1')
  {
    ModeChange(ZUMO_MODE.USER);
  }
  if(key == '2')
  {
    ModeChange(ZUMO_MODE.CORRIDOR);
  }
  if(key == '3')
  {
    tog = !tog;
  }
}

void SerialListener(Serial xBee) 
{
  currentValue = xBee.readStringUntil('/'); 
  
  if(currentValue != null)
  { 
    if(currentValue.charAt(0) == '@')
    {
       String[] split = split(currentValue, ':');
       if(split.length > 1)
       {
         print('\n');
          print(split[2]);
          if(split[1].equals("DATA"))
          { 
              if(split[2].equals("INITIALISE"))
              {
                ModeChange(ZUMO_MODE.INITIALISE);
              }
              else if(split[2].equals("CORRIDOR"))
              {
                ModeChange(ZUMO_MODE.CORRIDOR);
              }
              else if(split[2].equals("USER"))
              {
                ModeChange(ZUMO_MODE.USER);
              }
              
          }
        }
      }
  }
}

void ModeChange(ZUMO_MODE newMode)
{
  switch(newMode)
  {
    case INITIALISE:
      ToggleMoveControl(false);
      ToggleModeControl(false);
      btnStop.setVisible(false);
    break;
    
    case CORRIDOR:
      ToggleMoveControl(false);
      ToggleModeControl(true);
      btnStop.setVisible(true);
      btnUser.setVisible(true);
    break;
    
    case USER:
      ToggleMoveControl(true);
      ToggleModeControl(true);
      btnStop.setVisible(false);
      btnUser.setVisible(false);
    break;
    
  }
  
  mode = newMode;
  
  redraw();
  
}

void ToggleMoveControl(boolean toggle)
{
    btnW.setVisible(toggle);
    btnA.setVisible(toggle);
    btnS.setVisible(toggle);
    btnD.setVisible(toggle);
   
    
    btn90R.setVisible(toggle);
    btn90L.setVisible(toggle);
}

void ToggleModeControl(boolean toggle)
{
    lblStatus.setVisible(toggle);
    btnCorridor.setVisible(toggle);
    btnRoom.setVisible(toggle);
    
    lblDirection.setVisible(toggle);
    btnRightDirection.setVisible(toggle);
    btnLeftDirection.setVisible(toggle);
    btnStraightDirection.setVisible(toggle);
}


void draw() 
{
  
  btnStop.setVisible(tog);
}
