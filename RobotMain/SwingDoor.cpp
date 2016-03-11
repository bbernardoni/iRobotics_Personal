#include "SwingDoor.h"

SwingDoor::SwingDoor(int _swingDoorPin)
{
  swingDoorPin = _swingDoorPin;
}

void SwingDoor::startUp()
{
  swingDoor.attach(swingDoorPin);
  swingDoor.write(90);
}

void SwingDoor::periodic(ControllerData ctrl)
{
  if(CTRL_SWING_DOOR_UP){
    swingDoor.write(SWING_DOOR_UP_SPEED);
  }else if(CTRL_SWING_DOOR_DOWN){
    swingDoor.write(SWING_DOOR_DOWN_SPEED);
  }else{
    swingDoor.write(90);
  }
}

