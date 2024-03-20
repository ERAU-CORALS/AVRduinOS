#include <Arduino.h>

#include "FreeRTOS_Wrapper_Test.hpp"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial && millis() < 5000) continue;
  SDD_005_010();
  SDD_006_010();
  SDD_007_010();
  SDD_008_010();
  SDD_009_010();
  SDD_011();
}

void loop() {
  // put your main code here, to run repeatedly:
}