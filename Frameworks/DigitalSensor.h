/*  *///
// Created by kyle on 6/30/23.
//

#ifndef RENNSMOTORSPORT_DIGITALSENSOR_H
#define RENNSMOTORSPORT_DIGITALSENSOR_H
#include "Sensor.h"

template<typename T>
class DigitalSensor: public Sensor<T> {
public:
    DigitalSensor() : Sensor<T>() {}
    DigitalSensor(std::string name, DataLogger<T> log, int hz, int p) : Sensor<T>(name, log, hz) { port = p; }
private:
    int port;
};


#endif //RENNSMOTORSPORT_DIGITALSENSOR_H
