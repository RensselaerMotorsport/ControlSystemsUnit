//
// Created by kyle on 6/30/23.
//

#ifndef RENNSMOTORSPORT_ANALOGSENSOR_H
#define RENNSMOTORSPORT_ANALOGSENSOR_H
#include "Sensor.h"
extern "C" {
#include "../../High-Precision_AD_HAT/c/lib/Driver/ADS1263.h" // For Analog Sensor Read
}

template<typename T>
class AnalogSensor: public Sensor<T, UDOUBLE> {
public:
    AnalogSensor() : Sensor<T, UDOUBLE>() { channel = -1; }
    AnalogSensor(std::string name, DataLogger<T> log, int c, int h, int m)
        : Sensor<T, UDOUBLE>(name, log, h) { channel = c; muxChannel = m; }

    //Getters:
    int getChannel() { return channel; }
    int getMuxChannel() { return muxChannel; }
    
protected:
    //TODO: may end up needing this function to accept a parameter when TEST_MODE is on
    //TODO: that will require update to accept a parameter when TEST_MODE is on
    UDOUBLE getData();

    UBYTE channel;
    int muxChannel;
};

// This is in the header file because it is a template
template<typename T>
UDOUBLE AnalogSensor<T>::getData() {
    UDOUBLE data = 0; // XXX: Feel cute, might delete later
    // UDOUBLE data = ADS1263_GetChannalValue(channel);
    // Perhaps this to get data
    // UDOUBLE rawData = ADS1263_GetChannalValue(channel);
    // if((rawData>>31) == 1)
    //     return (REF*2 - rawData/2147483648.0 * REF);      //7fffffff + 1
    // else
    //     return (rawData/2147483647.0 * REF);       //7fffffff

    return data;
}


#endif //RENNSMOTORSPORT_ANALOGSENSOR_H
