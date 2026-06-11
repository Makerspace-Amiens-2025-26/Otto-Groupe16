// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>
#include <ESP32Servo.h>
#include "son.h"

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"
#define REMOTEXY_ACCESS_PASSWORD "1234"

#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =   // 80 bytes V19
  { 255,5,0,0,0,73,0,19,0,0,0,77,105,110,105,116,116,111,0,6,
  2,106,200,200,84,1,1,4,0,3,30,7,16,44,37,24,38,7,134,2,
  26,5,32,60,60,60,121,15,57,57,32,2,26,31,1,6,120,24,24,61,
  41,24,24,0,2,31,0,1,48,131,24,24,28,41,24,24,0,2,31,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t selectorSwitch_01; // from 0 to 6
  int8_t joystick_01_x; // from -100 to 100
  int8_t joystick_01_y; // from -100 to 100
  uint8_t button_01; // =1 if button pressed, else =0, from 0 to 1
  uint8_t button_02; // =1 if button pressed, else =0, from 0 to 1

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;  
#pragma pack(pop)
 
#define BUZZER_PIN D0 

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;

const int trig_pin = D2;
const int echo_pin = D1;

bool bouton1_deja_appuye = false;

void Avance() {
  RemoteXY_delay(150);
  Servo4.write(120);
  RemoteXY_delay(150);
  Servo2.write(132);
  RemoteXY_delay(150);
  Servo4.write(90);
  RemoteXY_delay(150);
  Servo2.write(92);
  RemoteXY_delay(150);
  Servo3.write(50);
  RemoteXY_delay(150);
  Servo1.write(52);
  RemoteXY_delay(150);
  Servo3.write(90);
  RemoteXY_delay(50);
  Servo1.write(92);
}

void droite() {
  Servo1.write(92);
  Servo3.write(90);
  Servo2.write(92);
  Servo4.write(90);
  RemoteXY_delay(100);
  Servo3.write(55);
  RemoteXY_delay(100);
  Servo1.write(34);
  RemoteXY_delay(100);
  Servo3.write(90);
  RemoteXY_delay(100);
  Servo1.write(94);
  RemoteXY_delay(100);
}

void gauche() {
  Servo1.write(90);
  Servo3.write(90);
  Servo2.write(90);
  Servo4.write(90);
  RemoteXY_delay(100);
  Servo4.write(125);
  RemoteXY_delay(100);
  Servo2.write(150);
  RemoteXY_delay(100);
  Servo4.write(90);
  RemoteXY_delay(100);
  Servo2.write(90);
  RemoteXY_delay(100);
}

void recul() {
  Servo1.write(90);
  Servo3.write(90);
  Servo2.write(90);
  Servo4.write(90);
  RemoteXY_delay(80);
  Servo4.write(80);
  RemoteXY_delay(80);
  Servo2.write(40);
  RemoteXY_delay(80);
  Servo4.write(90);
  RemoteXY_delay(80);
  Servo3.write(100);
  RemoteXY_delay(80);
  Servo2.write(90);
  RemoteXY_delay(80);
  Servo1.write(146);
  RemoteXY_delay(80);
  Servo3.write(90);
  RemoteXY_delay(80);
  Servo1.write(94);
  RemoteXY_delay(80);
}

void startupSound() {
  tone(BUZZER_PIN, NOTE_G4, 200);  
  delay(400);
  tone(BUZZER_PIN, NOTE_B4, 200);  
  delay(400);
  noTone(BUZZER_PIN);           
}


void marioJingle() {
  tone(BUZZER_PIN, NOTE_E5, 100); delay(150);
  tone(BUZZER_PIN, NOTE_E5, 100); delay(300);
  tone(BUZZER_PIN, NOTE_E5, 100); delay(300);
  tone(BUZZER_PIN, NOTE_C5, 100); delay(100);
  tone(BUZZER_PIN, NOTE_E5, 100); delay(300);
  tone(BUZZER_PIN, NOTE_G5, 100); delay(550);
  noTone(BUZZER_PIN);
}

void setup() 
{
  RemoteXY_Init();
  Servo1.attach(D7); //jambe gauche 
  Servo2.attach(D10); // jambe droite
  Servo3.attach(D9); //pied droit
  Servo4.attach(D8); //pied gauche

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  startupSound();
}

void loop() 
{ 
  RemoteXYEngine.handler();


if (RemoteXY.button_01 == 1) {
    if (bouton1_deja_appuye == false) {
      marioJingle();                
      bouton1_deja_appuye = true;   
    }
  } else {
    bouton1_deja_appuye = false;    
  }

 
  if (RemoteXY.joystick_01_y > 90) {
    Avance();
  } else if (RemoteXY.joystick_01_y < -90) {
    recul();
  } else if (RemoteXY.joystick_01_x > 90) {
    droite();
  } else if (RemoteXY.joystick_01_x < -90) {
    gauche();
  }
}
