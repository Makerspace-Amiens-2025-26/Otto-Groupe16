#include <Arduino.h>

// ⚠️ GPIO réels de la XIAO ESP32C3
const int trig_pin = 4;
const int echo_pin = 5;

// Mode debug
bool debug = true;


// ----------- Fonction mesure distance -----------
float getDistance() {
  // Reset trig
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  // Impulsion 10µs
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // Lecture avec timeout (30 ms)
  long duration = pulseIn(echo_pin, HIGH, 30000);

  if (duration == 0) {
    return -1; // aucune réponse
  }

  // Conversion en cm
  float distance = (duration * 0.0343) / 2;
  return distance;
}


// ----------- Fonction affichage -----------
void afficherDistance(float distance) {
  if (!debug) return;

  if (distance < 0) {
    Serial.println("Aucune detection");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}


// ----------- Setup -----------
void setup() {
  Serial.begin(115200); // plus rapide que 9600

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  digitalWrite(trig_pin, LOW);
}


// ----------- Loop -----------
void loop() {
  float distance = getDistance();
  afficherDistance(distance);

  delay(500);
}