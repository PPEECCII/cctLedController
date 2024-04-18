# cctLedController
program to control an CCT(warm - cold) led strip
This code is used to control a CCT led strip using one of the capacitive touch pins (can be replaced with other button type if desired) of the esp32 device, planned to implement it in mirror lights.
short pushes CYCLES between the modes: OFF - WARM LIGHT - WHITE LIGHT - COLD LIGHT - OFF
long presses alternate between increasing and decreasing light intensity

TOUCH_PIN must be one of the touch capable esp32 pins (TOUCH0-TOUCH9)
COLD_LIGHT must be an output safe esp32 pin
WARM_LIGHT must be an output safe esp32 pin

In order to wire COLD_LIGHT AND WARM_LIGHT you will need a NPN transistor and a 1k resistor for each pin, and must be connected this way:
  -Resistor connected to esp32 pin in one side and transistor base in the other side
  -Transistor emitter to ground
  -Transistor collector to the led strip W(warm) or C(cold) pin

The led power supply ground must be connected to the esp32 ground.
If the led strip is powered with more than 5v you can use the same power supply for the esp32 using a step-down converter.
