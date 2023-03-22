#include <Arduino.h>
#include "ttn.h"
#include "credentials.h"
ttn myttn(16,17);

void setup() {
  Serial.begin(115200);
  //Config LoRaWAN
  myttn.DevEUI(DevEui);
  myttn.AppEui(AppEui);
  myttn.AppKey(AppKey);
  myttn.Join();
  pinMode(2,INPUT);
  pinMode(5,INPUT);
}

void loop() {
  //Leer entradas
  bool IO1=digitalRead(2);
  bool IO2=digitalRead(5);
  if(IO1&&IO2==true){
    myttn.sendboolean(true);
    //Serial.println(IO1&&IO2);
  }else{
    Serial.println("Todo bien");
    myttn.send2ttn(1,23,3);
  }
  }