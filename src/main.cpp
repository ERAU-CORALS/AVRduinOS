#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include "FreeRTOS_Wrapper_Test.hpp"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial && millis() < 5000) continue;

  // SDD_005_010();
  // SDD_006_010();
  // SDD_007_010();
  // SDD_008_010();
  // SDD_009_010();
  // SDD_011();
  // SDD_013_017();
  // SDD_014_017();
  // SDD_015_017();
  // SDD_018();
  // SDD_020();
  // SDD_021();
  // SDD_022();  
  SDD_025();
}

void loop() {
  // put your main code here, to run repeatedly:
}