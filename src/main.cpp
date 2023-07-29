#include <Arduino.h>
#include "ttn.h"
#include "credentials.h"
#include "M5Stack.h"
#include "config.h"
#include "Wire.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme;//i2c
int WAN_option=0;
int distance=0;
ttn myttn(16,17);
void sensor_init(){
  if(!bme.begin()){
    Serial.println(F("No se encuentra el sensor"));
    while(1);
  }
  //setup
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}
void WAN_connection(){
  if(WAN_option==1){
    myttn.DevEUI(DevEuiHELIUM);
    myttn.AppEui(AppEuiHELIUM);
    myttn.AppKey(AppKeyHELIUM);
    myttn.Join();
  }
  else if(WAN_option==2){
    myttn.DevEUI(DevEuiTTN);
    myttn.AppEui(AppEuiTTN);
    myttn.AppKey(AppKeyTTN);
    myttn.Join();
  }
  else{
    M5.Lcd.clear(BLACK);
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
  sensor_init();
  //INIT MENU

  //CALL A FUNCTION
  ///////////////////////
  Serial.begin(115200);

  pinMode(2,INPUT);
  pinMode(5,INPUT);
  myttn.DevEUI(DevEuiTTN);
  myttn.AppEui(AppEuiTTN);
  myttn.AppKey(AppKeyTTN);
  myttn.Join();
}
void loop() {
  //READ SENSOR
   unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }
  Serial.print(F("Reading started at "));
  Serial.print(millis());
  Serial.print(F(" and will finish at "));
  Serial.println(endTime);
    if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  int temperature=100*bme.temperature;
  Serial.println(bme.temperature);
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setCursor(0,35,4);
  M5.Lcd.print("Temp: ");
  M5.Lcd.println(bme.temperature);
  delay(250);
  myttn.send2ttn(1,temperature,1);
}