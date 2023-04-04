#ifndef SENSOR_H
#define SENSOR_H
#include "Arduino.h"
class sensor{
    public:
        //Constructor
        sensor(uint8_t type); //I must load all implictaed libraries
        void read_sensor(uint8_t type);
        void begin_sensor(uint8_t type);
    private:
        
};
#endif