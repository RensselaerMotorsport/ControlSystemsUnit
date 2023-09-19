//
// Created by kyle on 6/30/23.
//

#ifndef RENNSMOTORSPORT_CANSENSOR_H
#define RENNSMOTORSPORT_CANSENSOR_H
#include "Sensor.h"

template<typename T>
class CANSensor : private Sensor<T> {
public:
    CANSensor()  : Sensor<T>() { frequency = -1; id = -1; }
    CANSensor(std::string name, DataLogger<T> log, int p, int f, int i): Sensor<T>(name, log, p) { frequency = f; id = i; }

    //Getters:
    int getFrequency() { return frequency; }
    int getID() { return id; }
private:
    int frequency;
    int id;
};


#endif //RENNSMOTORSPORT_CANSENSOR_H
