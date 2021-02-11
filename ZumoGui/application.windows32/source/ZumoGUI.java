import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 
import g4p_controls.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class ZumoGUI extends PApplet {





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

public void setup() 
{
    createGUI();
    
  ModeChange(ZUMO_MODE.INITIALISE);
  
  
 
  String portName = "COM4";
  
  zumoPort = new Serial(this, portName, 9600);
   tog = false;
}

public void isKeyPress() 
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

public void SerialListener(Serial xBee) 
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

public void ModeChange(ZUMO_MODE newMode)
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

public void ToggleMoveControl(boolean toggle)
{
    btnW.setVisible(toggle);
    btnA.setVisible(toggle);
    btnS.setVisible(toggle);
    btnD.setVisible(toggle);
   
    
    btn90R.setVisible(toggle);
    btn90L.setVisible(toggle);
}

public void ToggleModeControl(boolean toggle)
{
    lblStatus.setVisible(toggle);
    btnCorridor.setVisible(toggle);
    btnRoom.setVisible(toggle);
    
    lblDirection.setVisible(toggle);
    btnRightDirection.setVisible(toggle);
    btnLeftDirection.setVisible(toggle);
    btnStraightDirection.setVisible(toggle);
}


public void draw() 
{
  
  btnStop.setVisible(tog);
}
/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void txtConsole_change(GTextArea source, GEvent event) { //_CODE_:txtConsole:713900:
} //_CODE_:txtConsole:713900:

public void btnW_click(GImageButton source, GEvent event) { //_CODE_:btnW:692093:
  zumoPort.write('w');
} //_CODE_:btnW:692093:

public void btnA_click(GImageButton source, GEvent event) { //_CODE_:btnA:409134:
  zumoPort.write('a');
} //_CODE_:btnA:409134:

public void btnS_click(GImageButton source, GEvent event) { //_CODE_:btnS:724152:
  zumoPort.write('s');
} //_CODE_:btnS:724152:

public void btnD_click(GImageButton source, GEvent event) { //_CODE_:btnD:257327:
  zumoPort.write('d');
} //_CODE_:btnD:257327:

public void btn90R_click(GImageButton source, GEvent event) { //_CODE_:btn90R:605883:
   zumoPort.write('p');
} //_CODE_:btn90R:605883:

public void btn90L_click(GImageButton source, GEvent event) { //_CODE_:btn90L:834581:
  zumoPort.write('o');
} //_CODE_:btn90L:834581:

public void btnCorridor_click(GButton source, GEvent event) { //_CODE_:btnCorridor:943118:
  zumoPort.write('c');
} //_CODE_:btnCorridor:943118:

public void btnRoom_click(GButton source, GEvent event) { //_CODE_:btnRoom:430992:
  zumoPort.write('r');
} //_CODE_:btnRoom:430992:

public void btnRightDirection_click(GButton source, GEvent event) { //_CODE_:btnRightDirection:339509:
  zumoPort.write('r');
} //_CODE_:btnRightDirection:339509:

public void btnLeftDirection_click(GButton source, GEvent event) { //_CODE_:btnLeftDirection:774340:
  zumoPort.write('l');
} //_CODE_:btnLeftDirection:774340:

public void btnStraightDirection_click(GButton source, GEvent event) { //_CODE_:btnStraightDirection:292887:
  zumoPort.write('s');
} //_CODE_:btnStraightDirection:292887:

public void btnStop_click(GButton source, GEvent event) { //_CODE_:btnStop:949533:
  zumoPort.write(32);
} //_CODE_:btnStop:949533:

public void btnUser_click(GButton source, GEvent event) { //_CODE_:btnUser:808232:
  zumoPort.write('U');
} //_CODE_:btnUser:808232:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  txtConsole = new GTextArea(this, 200, 32, 600, 368, G4P.SCROLLBARS_VERTICAL_ONLY | G4P.SCROLLBARS_AUTOHIDE);
  txtConsole.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  txtConsole.setOpaque(true);
  txtConsole.addEventHandler(this, "txtConsole_change");
  btnW = new GImageButton(this, 460, 410, 100, 60, new String[] { "upArrow.png", "upArrow.png", "upArrow.png" } );
  btnW.addEventHandler(this, "btnW_click");
  btnA = new GImageButton(this, 336, 488, 100, 60, new String[] { "leftArrow.png", "leftArrow.png", "leftArrow.png" } );
  btnA.addEventHandler(this, "btnA_click");
  btnS = new GImageButton(this, 456, 488, 100, 60, new String[] { "downArrow.png", "downArrow.png", "downArrow.png" } );
  btnS.addEventHandler(this, "btnS_click");
  btnD = new GImageButton(this, 576, 488, 100, 60, new String[] { "RightArrow.png", "RightArrow.png", "RightArrow.png" } );
  btnD.addEventHandler(this, "btnD_click");
  btn90R = new GImageButton(this, 576, 408, 100, 60, new String[] { "rotateRight.png", "rotateRight.png", "rotateRight.png" } );
  btn90R.addEventHandler(this, "btn90R_click");
  btn90L = new GImageButton(this, 336, 408, 100, 60, new String[] { "rotateLeft.png", "rotateLeft.png", "rotateLeft.png" } );
  btn90L.addEventHandler(this, "btn90L_click");
  btnCorridor = new GButton(this, 336, 624, 100, 50);
  btnCorridor.setText("CORRIDOR");
  btnCorridor.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnCorridor.addEventHandler(this, "btnCorridor_click");
  btnRoom = new GButton(this, 576, 624, 100, 50);
  btnRoom.setText("ROOM");
  btnRoom.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnRoom.addEventHandler(this, "btnRoom_click");
  btnRightDirection = new GButton(this, 576, 696, 100, 50);
  btnRightDirection.setText("RIGHT");
  btnRightDirection.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnRightDirection.addEventHandler(this, "btnRightDirection_click");
  btnLeftDirection = new GButton(this, 336, 696, 100, 50);
  btnLeftDirection.setText("LEFT");
  btnLeftDirection.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnLeftDirection.addEventHandler(this, "btnLeftDirection_click");
  btnStraightDirection = new GButton(this, 456, 696, 100, 50);
  btnStraightDirection.setText("STRAIGHT");
  btnStraightDirection.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnStraightDirection.addEventHandler(this, "btnStraightDirection_click");
  lblStatus = new GLabel(this, 230, 630, 80, 30);
  lblStatus.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  lblStatus.setText("Select Next Mode");
  lblStatus.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  lblStatus.setOpaque(true);
  lblDirection = new GLabel(this, 220, 700, 100, 50);
  lblDirection.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  lblDirection.setText("Select direction of next room/corridor");
  lblDirection.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  lblDirection.setOpaque(true);
  btnStop = new GButton(this, 330, 560, 350, 50);
  btnStop.setText("STOP");
  btnStop.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnStop.addEventHandler(this, "btnStop_click");
  btnUser = new GButton(this, 456, 624, 100, 50);
  btnUser.setText("USER");
  btnUser.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnUser.addEventHandler(this, "btnUser_click");
}

// Variable declarations 
// autogenerated do not edit
GTextArea txtConsole; 
GImageButton btnW; 
GImageButton btnA; 
GImageButton btnS; 
GImageButton btnD; 
GImageButton btn90R; 
GImageButton btn90L; 
GButton btnCorridor; 
GButton btnRoom; 
GButton btnRightDirection; 
GButton btnLeftDirection; 
GButton btnStraightDirection; 
GLabel lblStatus; 
GLabel lblDirection; 
GButton btnStop; 
GButton btnUser; 

  public void settings() {  size(1024, 768); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "ZumoGUI" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
