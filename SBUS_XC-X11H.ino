#include <sbus.h>
#include <Arduino.h>


// used pins
#define SBUS_PIN 3   // D3

SBUS sbus;

#define SPD1 6
#define DIR1 7
#define SPD2 8
#define DIR2 9

int PWM1 = 0;
int PWM2 = 0;


void setup() {
  Serial.begin(115200);

  pinMode(SPD1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  digitalWrite(SPD1, LOW);
  digitalWrite(DIR1, HIGH);

  pinMode(SPD2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  digitalWrite(SPD2, LOW);
  digitalWrite(DIR2, HIGH);


  sbus.begin(SBUS_PIN, sbusNonBlocking);
  Serial.println("STARTUP");
}


void loop() {

  if (!sbus.waitFrame()) {

    Serial.println("Timeout!");

  } else {

    if (sbus.getChannel(0) > 1520) {
      PWM1 = map(sbus.getChannel(0), 1520, 2000, 0 , 255);
      digitalWrite(DIR1, HIGH);
      analogWrite(SPD1, PWM1); 
    }
    if (sbus.getChannel(0) < 1480) {
      PWM1 = map(sbus.getChannel(0), 1480, 1000, 0 , 255);
      digitalWrite(DIR1, LOW);
      analogWrite(SPD1, PWM1); 
    }
      else{
        digitalWrite(SPD1, LOW);
    }

     
      if (sbus.getChannel(1) > 1520) {
        PWM2 = map(sbus.getChannel(1), 1520, 2000, 0 , 255);
        digitalWrite(DIR2, HIGH);
        analogWrite(SPD1, PWM2); 
      }

      if (sbus.getChannel(1) < 1480) {
        PWM2 = map(sbus.getChannel(1), 1480, 1000, 0 , 255);
        digitalWrite(DIR2, LOW);
        analogWrite(SPD1, PWM2);}
        
        else{
          digitalWrite(SPD2, LOW);
      }    

      if (sbus.signalLossActive())
        Serial.print("SIGNAL_LOSS ");

      if (sbus.failsafeActive())
        Serial.print("FAILSAFE");

      Serial.println();
    }
}
