#include <Arduino.h>
#include "ttn.h"
#include "credentials.h"
#include "M5Stack.h"
#include "config.h"

int WAN_option=0;

ttn myttn(16,17);
void button_Menu(){
  M5.update();
  if(M5.BtnA.wasReleased()||M5.BtnA.pressedFor(1000,200)){
    M5.Lcd.println("You prefer Helium");
    WAN_option=1;
  }
  if(M5.BtnB.wasReleased()||M5.BtnA.pressedFor(1000,200)){
    M5.Lcd.println("You prefer TTN");
    WAN_option=1;
  }
  if(M5.BtnC.wasReleased()||M5.BtnA.pressedFor(1000,200)){
    M5.Lcd.println("RESET");
    WAN_option=3;
  }
}

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
  //INIT MENU
  M5.Lcd.println("If you want use Helium, please pulse A:");
  M5.Lcd.println("If you want use TTN,please pulse B:");
  M5.Lcd.println("If you want clear the screen, please pulse C");
  //CALL A FUNCTION
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