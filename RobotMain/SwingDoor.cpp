#include "SwingDoor.h"

SwingDoor::SwingDoor(int _swingDoorPin)
{
  swingDoorPin = _swingDoorPin;
}

void SwingDoor::startUp()
{
  pinMode(swingDoorPin, OUTPUT);
  digitalWrite(swingDoorPin, LOW);
}

void SwingDoor::periodic(ControllerData ctrl)
{
  digitalWrite(swingDoorPin, CTRL_SWING_DOOR? HIGH: LOW);
}

