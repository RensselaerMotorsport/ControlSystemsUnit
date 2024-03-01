/*
 * -------------------------------------------------------------------------
 *
 *  ███╗   ███╗ █████╗ ██╗███╗   ██╗    ████████╗███████╗███████╗████████╗
 *  ████╗ ████║██╔══██╗██║████╗  ██║    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝
 *  ██╔████╔██║███████║██║██╔██╗ ██║       ██║   █████╗  ███████╗   ██║
 *  ██║╚██╔╝██║██╔══██║██║██║╚██╗██║       ██║   ██╔══╝  ╚════██║   ██║
 *  ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║       ██║   ███████╗███████║   ██║
 *  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝       ╚═╝   ╚══════╝╚══════╝   ╚═╝
 *
 * -------------------------------------------------------------------------
 *
 *
 *
 */

#include <cstring>
#include <iostream>
#include "../Frameworks/Sensors/DataLogger.h"
#include "DataLoggerTest.cpp"
#include "../Frameworks/Sensors/AnalogSensors/Temperature.h"
#include "TemperatureTest.cpp"
#include "MotorControllerTest.cpp"
#include "SensorTest.cpp"

void DataLoggerT(){
    DataLoggerTest dlt = DataLoggerTest();
    dlt.RunTests();
}

void TemperatureT(){
    TemperatureTest tmpTest = TemperatureTest();
    tmpTest.RunTests();
}

void MotorControllerT(){
    MotorControllerTest mct = MotorControllerTest();
    mct.RunTests();
}

void SensorT(){
    SensorTest st = SensorTest();
    st.RunTests();
}

//This will require some way to pass expected values into the test classes at or before runtime
int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "All")) {
            DataLoggerT();
            TemperatureT();
            MotorControllerT();
            SensorT();
        } else if (0 == strcmp(argv[i], "DataLogger")) {
            DataLoggerT();
        } else if (0 == strcmp(argv[i], "Temperature")) {
            TemperatureT();
        } else if (0 == strcmp(argv[i], "MotorController")) {
            MotorControllerT();
        } else if (0 == strcmp(argv[i], "Sensor")) {
            SensorT();
        } else {
            std::cerr << "INCORRECT USAGE:\n" <<
                      "USAGE: ./MainTest.o \"Test\"\n" <<
                      "Available Tests:\n" <<
                      "All\n" <<
                      "DataLogger\n" <<
                      "Temperature\n" <<
                      "MotorController\n" <<
                      "Sensor\n";
        }
    }
}


