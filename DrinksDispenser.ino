#include <IRremote.hpp>
#include<LiquidCrystal.h>
#include "declarations.h"

void setup() {
  //Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Ultrasonic ouput (this is the trigger pin)
  pinMode(echoPin, INPUT);  // Ultrasonic input (this is the echo pin)
  pinMode(waterPumpPin, OUTPUT);
  lcd.begin(16,2);    //This is the number of characters and rows
  lcd.setCursor(0,0);  //Initial position for the cursors
  irrecv.enableIRIn(); // the IR reception begins
}

void loop() {

// Ultrasonic sensor readings. Edit: this could've been a function a function, but it's only called once again so we left it like that.
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH); //the sensor is active por 10 microses
  delayMicroseconds(10);
  usTime = pulseIn(echoPin,HIGH); //the echo pin reads the sound travel time
  usDistance = int(0.017*usTime); //this scalar give us our distance (considering the dispenser distance)
  //Serial.println(usDistance);

  waterLevel = analogRead(A0);
  //Serial.println(waterLevel);
  if (waterLevel > 370) { // This is our working level.
    lcd.clear();
    counter=0;
    if (usDistance <= 8) {  //if theres a glass
      lcd.setCursor(0,0);
      lcd.print("Glass ready...");
      delay(500);
      if (irrecv.decode(&results) { 
        if (results.value==0x00FF02FD) {  // If start button is pressed
          //Serial.println("Tecla: OK");
          digitalWrite(waterPumpPin,LOW);  //The pump is activated with a low signal
          lcd.setCursor(0,0);
          lcd.print("loading...");
          //Serial.println("usDistance ");
          //Serial.println(usDistance);
          //Serial.println(" cm");
          while(usDistance <= 8 and counter<10) { // while there's still a glass and it's been less than 5 seconds
            counter = counter + 1;  // because of the delay, this counter is aproximately equivalent to 0.5 seconds
            digitalWrite(trigPin,LOW);
            delayMicroseconds(5);
            digitalWrite(trigPin,HIGH);
            delayMicroseconds(10);
            usTime = pulseIn(echoPin,HIGH);
            usDistance = int(0.017*usTime);
            //Serial.println("usDistance ");
            //Serial.println(usDistance);
            //Serial.println(" cm");
            delay(500);
          }
        }
        digitalWrite(waterPumpPin, HIGH);
        delay(500);
      }
      irrecv.resume();
    } else { // Mientras no este presente el vaso
      digitalWrite(waterPumpPin, HIGH);  // waterPumpPin apagada
      lcd.setCursor(0,0);
      lcd.print("Prendido...");
      delay(500);
    }
  } else { // There's not enough waters
    lcd.clear();
    lcd.setCursor(0,0);  
    lcd.print("Insuficient water");
    lcd.setCursor(0,1); //this is the second row
    lcd.print("please charge");
    delay(500);
  }
}
