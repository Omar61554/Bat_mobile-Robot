#include "NAV_interface.h"

Car bruceWayne;

void setup()
{ 
  bruceWayne.setup();
  Serial.begin(9600);
}

void loop()
{
    bruceWayne.controller();
}   
