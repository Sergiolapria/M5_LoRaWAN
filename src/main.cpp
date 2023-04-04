#include <Arduino.h>
#include "ttn.h"
#include "credentials.h"
#include "M5Stack.h"
#include "config.h"
#include <sensors.h>



ttn myttn(16,17);

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.begin();
  M5.Lcd.fillScreen(RED);
  M5.Lcd.fillRect(10,1,150,160,BLACK);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("PAPER FOR BULL_IoT");
  M5.Lcd.println("By SergioPria");
  ///////////////////////
  Serial.begin(115200);
  //////////////////////

  //CALIBRATE THE SENSOR

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
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setCursor(0,35,4);
  M5.Lcd.println("Status:");
  M5.Lcd.println(IO1);
  M5.Lcd.println(IO2);
  if(IO1&&IO2==true){
    //myttn.send2ttn(0,48,0);//IO1=true
    delay(250);
    myttn.send2ttn(1,50,0);//IO2=true
  }else{
    Serial.println("Todo bien");
    //myttn.send2ttn(0,49,0);//IO1=false
    delay(250);
    myttn.send2ttn(1,51,0);//IO2=false
  }

  }