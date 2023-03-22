#ifndef TTN_H
#define TTN_H
#include "Arduino.h"
class ttn{
  public:
    ttn(uint8_t rxpin,uint8_t txpin);
    void send2ttn(int channel,float magnitude,float threshold);
    void sendboolean(bool result);
    void loraset(char dat[]);
    void sendHex(char str[]);
    void lorawan(char dat[]);
    void DevEUI(char dat[]);
    void AppEui(char dat[]);
    void AppKey(char dat[]);
    void OTAA(char dat[]);
    void Join();
  private:
    void ATCommand(char cmd[],char dat[]);
    bool ReceiveAT(uint32_t timeout);
    void array2string(byte array[],unsigned int len,char buffer[]);
};
#endif
