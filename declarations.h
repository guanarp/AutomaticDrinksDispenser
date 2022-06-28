#ifndef _DECLARATIONS_H
#define _DECLARATIONS_H


long usDistance; // Ultrasonic distance measurement
long usTime;  // Ultrasonic travel time.
int waterLevel = 0;
int waterPumpPin = 10; // water pump bomb
int receiver = 13;  // Remote control output
int counter = 0;   // a counter for the inner loop
int trigPin = 2;
int echoPin = 3;



LiquidCrystal lcd(8,9,4,5,6,7); //(RS, EN, d0, d1, d2, d3)  these are the LCD output pins


IRrecv irrecv(receiver); //this is for the remote control
decode_results results; //for the results

#endif // _DECLARTIONS_H
