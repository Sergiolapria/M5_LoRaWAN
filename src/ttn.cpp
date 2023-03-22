#include "ttn.h"

ttn::ttn(uint8_t rxpin,uint8_t txpin){
  Serial2.begin(115200,SERIAL_8N1,rxpin,txpin);
}
//private
void ttn::ATCommand(char cmd[],char dat[]){
  char buf[256]={0};
  if(dat==NULL){
    sprintf(buf,"AT+%s",cmd);
  }
  else
  {
    sprintf(buf,"AT+%s=%s",cmd,dat);
  }
  Serial.write(buf);
  Serial2.write(buf);
  delay(200);
  ReceiveAT(50);
}
bool ttn::ReceiveAT(uint32_t timeout){
  uint32_t nowtime=millis();
  while(millis()-nowtime<timeout){
    if(Serial2.available()!=0){
      String str=Serial2.readString();
      if(str.indexOf("+OK")!=-1||str.indexOf("+ERROR")!=-1){
        Serial.println(str);
        return true;
      }else{
        Serial.println("[!] Syntax Error");
        break;
    }
  }
}
  Serial.println("[!] Timeout");
}
void ttn::array2string(byte array[],unsigned int len,char buffer[]){
  for(unsigned int i=0;i<len;i++){
    byte nib1=(array[i]>>4)&0x0F;
    byte nib2=(array[i]>>0)&0x0F;
    buffer[i*2+0]=nib1 < 0xA ? '0' + nib1 : 'A' + nib1 - 0xA;
    buffer[i*2+1]=nib2 < 0xA ? '0' + nib2 : 'A' + nib2 - 0xA;
  }
  buffer[len*2]='\0';
}
//PUBLIC
void ttn::sendboolean(bool result){
  //ttn::loraset("1");
  //ATCommand LoraSet,1
  delay(100);
  byte payload[1];
  payload[0]=result;
  Serial.print("payload:");
  Serial.println(payload[0]);
  char str[1]="";
  array2string(payload,1,str);
  Serial.println(str);
  ttn::sendHex("AA");

}
void ttn::send2ttn(int channel, float magnitude,float threshold){
  //activate communication
  //ttn::loraset("?");
  //ATCommand("LoraSet","1");
  delay(300);
  uint16_t magnitude2ttn=100*magnitude;

  byte payload[6];
  payload[0]=channel;
  payload[1]=channel>>8;
  payload[2]=channel>>16;

  payload[3]=magnitude2ttn;
  payload[4]=magnitude2ttn>>8;
  payload[5]=magnitude2ttn>>16;

  //payload[12]=ppm2ttn>>32;
  //DEBUG
  Serial.print(payload[9]);
  Serial.print(payload[10]);
  Serial.println(payload[11]);
  
  Serial.print(F("[X] actual TTN payload is------>"));
  char str[48]="";
  array2string(payload,6,str);
  
  Serial.println(str);
  //Now send all to TTN
  //ATCommand("SendHex",str);
  ttn::sendHex(str);
  
}
void ttn::OTAA(char dat[]){
  ATCommand("OTAA",dat);
  delay(200);
}
void ttn::loraset(char dat[]){
  ATCommand("LoraSet",dat);
  delay(200);
}
void ttn::sendHex(char dat[]){
  ATCommand("SendHex",dat);
  delay(200);
}
void ttn::lorawan(char dat[]){
  ATCommand("LORAWAN",dat);
  delay(500);
}
void ttn::DevEUI(char dat[]){
  ATCommand("DevEui",dat);
  delay(300);
}
void ttn::AppEui(char dat[]){
  ATCommand("AppEui",dat);
  delay(300);
}
void ttn::AppKey(char dat[]){
  ATCommand("AppKey",dat);
  delay(300);
}
void ttn::Join(){
  ATCommand("Join","1");
  delay(200);
}
