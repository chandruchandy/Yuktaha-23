//
// This example shows one way of using an LED as a light sensor.
// You will need to wire up your components as such:
//
//           + digital2
//           |
//           <
//           > 100 ohm resistor
//           <
//           |
//           |  LED Cathode (LED_N_SIDE, normally (-))
//           |
//         _____
//          / \  LED, maybe a 5mm, clear plastic is good
//         _____
//           |
//           |  LED Anode (LED_P_SIDE, normally (+))
//           |
//           + digital3
//
// What we are going to do is apply a positive voltage at digital2 and
// connect digital3 to GND. This is backwards for the LED, current will
// not flow and light will not come out, but we will charge up the 
// capacitance of the LED junction and the Arduino pin.
//
// Then we are going to disconnect the output HIGH drivers from 
// digital2 (making it now a high-impedance INPUT) and count how
// long it takes the stored charge at digital2 to bleed off through 
// the LED to GND at digital3. The brighter the light, the faster it will 
// bleed away to digital3 (GND), thereby causing the INPUT reading
// at digital2 to change from HIGH to LOW.
//
// Then just to be perverse we will display the brightness back on the 
// same LED by turning it on for a millisecond. This happens more often
// with brighter lighting, so the LED is dim in a dim room and brighter 
// in a bright room. Quite nice.
//
// (Though a nice idea, this implementation is flawed because the refresh
// rate gets too long in the dark and it flickers disturbingly.)
//
#define LED_N_SIDE 2
#define LED_P_SIDE 3

void setup()
{}

void loop()
{
  unsigned int j;

  // Apply reverse voltage, charge up the pin and led capacitance
  pinMode(LED_N_SIDE, OUTPUT);
  pinMode(LED_P_SIDE, OUTPUT);
  digitalWrite(LED_N_SIDE, HIGH);
  digitalWrite(LED_P_SIDE, LOW);

  // Isolate the pin 2 end of the diode by changing it from OUTPUT HIGH to 
  // INPUT LOW (high impedance input with internal pull-up resistor off)
  pinMode(LED_N_SIDE, INPUT);
  digitalWrite(LED_N_SIDE,LOW);  // turn off internal pull-up resistor

  // Count how long it takes the diode to bleed back down to a logic 0 at pin 2
  for ( j = 0; j < 30000; j++) {
    if ( digitalRead(LED_N_SIDE)==0) break;
  }
  // You could use 'j' for something useful, but here we are just using the
  // delay of the counting.  In the dark it counts higher and takes longer, 
  // increasing the portion of the loop where the LED is off compared to 
  // the 1000 microseconds where we turn it on.

  // Turn the light on for 1000 microseconds
  digitalWrite(LED_P_SIDE, HIGH);
  digitalWrite(LED_N_SIDE, LOW);
  pinMode(LED_P_SIDE, OUTPUT);
  pinMode(LED_N_SIDE, OUTPUT);
  delayMicroseconds(1000);
  // we could turn it off, but we know that is about to happen at the loop() start
}