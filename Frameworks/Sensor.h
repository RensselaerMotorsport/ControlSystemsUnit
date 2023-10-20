
/*
 * -----------------------------------------------------------------
 *    _____
 *   / ____|
 *  | (___   ___ _ __  ___  ___  _ __
 *   \___ \ / _ \ '_ \/ __|/ _ \| '__|
 *   ____) |  __/ | | \__ \ (_) | |
 *  |_____/ \___|_| |_|___/\___/|_|
 *
 * ------------------------------------------------------------------
 *
 * Class Function: The function of this class is to act as a high level class for lower level classes to extend
 *                      This class will allow the various sensors to work and communicate with the motor controller class
 *                          This class will dictate how sensors behave and fetch/store data that is received from the physical sensors
 *
 *
 * Member Variables:
 * sensorName - name of the sensor to denote its function
 * sample rate - an integer value representing the sample rate of the sensor in Hz
 *
 * Member functions:
 * clear - clears the data of this sensor
 *
 */

#ifndef RENNSMOTORSPORT_SENSOR_H
#define RENNSMOTORSPORT_SENSOR_H
#include <string>
#include "DataLogger.h"
#include "IO.h"

template<typename T> //The output typename
template<typename I> //The input typename
class Sensor: public IO {
public:
    Sensor(): IO() { sensorName = "UNNAMED"; dataLog = DataLogger<T>(); }
    Sensor(std::string name): IO() { sensorName = name; dataLog = DataLogger<T>(); }
    Sensor(std::string name, DataLogger<T> log, int h): IO() { sensorName = name; dataLog = log;  hz = h; }
    /*
    //clears stored data
    void clear();
    */

   const DataLogger<T>& getDataLog() const { return dataLog; }
   std::string getSensorName() { return sensorName; }
   const int getHZ() const { return hz; }

   //Setter
   // TODO: Make pure virtual
   virtual void update(I var) {} //This will be implemented in each individual sensor

   void writeDataToFile(std::string filename); //This outputs the data stored in datalogger in a csv format
                                              //Implemented by each sensor

protected: //This is protected instead of private so that subclasses can access these
    //member variables:
    //New values should be stored in the dataLog when they are gotten
    DataLogger<T> dataLog;

    //Contains name of the input sensor
    std::string sensorName;

    int hz;
};

inline float timeToFloat(highResTime){
    return 1.0;
}

#endif //RENNSMOTORSPORT_SENSOR_H
