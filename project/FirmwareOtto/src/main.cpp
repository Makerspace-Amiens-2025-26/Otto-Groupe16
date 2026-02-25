#include "notes.h"
#include <Arduino.h>
#include <ESP32Servo.h>

const int trig_pin = D2;
const int echo_pin = D1;


bool debug = true;


float getDistance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  long duration = pulseIn(echo_pin, HIGH, 30000);

  if (duration == 0) {
    return -1; // aucune lecture
  }

  return (duration * 0.0343) / 2;
}

// distance
void afficherDistance(float distance) {
  if (debug) {
    if (distance < 0) {
      Serial.println("Aucune detection");
    } else {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  float distance = getDistance();
  afficherDistance(distance);

  delay(1000);
}