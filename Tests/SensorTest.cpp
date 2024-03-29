/*
 * -------------------------------------------------------------------------------------------
 *
 *  ███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗     ████████╗███████╗███████╗████████╗
 *  ██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝
 *  ███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝       ██║   █████╗  ███████╗   ██║
 *  ╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗       ██║   ██╔══╝  ╚════██║   ██║
 *  ███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║       ██║   ███████╗███████║   ██║
 *  ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝       ╚═╝   ╚══════╝╚══════╝   ╚═╝
 *
 * -------------------------------------------------------------------------------------------
 *
 * Test Functions:
 *      Test (insert function of test):
 *          Expected behavior:
 *
 *      Test (insert function of test):
 *          Expected behavior:
 */

#include <iostream>
#include "../Frameworks/Sensors/Sensor.h"

class SensorTest{
public:

    SensorTest() { s = Sensor<int, int>(); }

    void RunTests(){
        std::cout<<"Running Sensor Tests"<<std::endl;
        std::cout<<"Test Get Name: "<< ((s.getSensorName() == "UNNAMED") ? "Passed" : "Failed") <<std::endl;
    }

private:
    Sensor<int, int> s; // FIXME: This is a placeholder with int types

};
