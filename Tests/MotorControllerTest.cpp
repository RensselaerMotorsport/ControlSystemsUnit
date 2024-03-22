/*
 * --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *
 *  ███╗   ███╗ ██████╗ ████████╗ ██████╗ ██████╗      ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  ██████╗ ██╗     ██╗     ███████╗██████╗     ████████╗███████╗███████╗████████╗
 *  ████╗ ████║██╔═══██╗╚══██╔══╝██╔═══██╗██╔══██╗    ██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔═══██╗██║     ██║     ██╔════╝██╔══██╗    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝
 *  ██╔████╔██║██║   ██║   ██║   ██║   ██║██████╔╝    ██║     ██║   ██║██╔██╗ ██║   ██║   ██████╔╝██║   ██║██║     ██║     █████╗  ██████╔╝       ██║   █████╗  ███████╗   ██║
 *  ██║╚██╔╝██║██║   ██║   ██║   ██║   ██║██╔══██╗    ██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██╗██║   ██║██║     ██║     ██╔══╝  ██╔══██╗       ██║   ██╔══╝  ╚════██║   ██║
 *  ██║ ╚═╝ ██║╚██████╔╝   ██║   ╚██████╔╝██║  ██║    ╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║╚██████╔╝███████╗███████╗███████╗██║  ██║       ██║   ███████╗███████║   ██║
 *  ╚═╝     ╚═╝ ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝       ╚═╝   ╚══════╝╚══════╝   ╚═╝
 *
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *
 * Test Functions:
 *      Test (insert function of test):
 *          Expected behavior:
 *
 *      Test (insert function of test):
 *          Expected behavior:
 *
 */
#include <iostream>
#include "../Frameworks/Sensors/CANSensors/MotorController.cpp"

#ifndef RENNSMOTORSPORT_MOTOR_CONTROLLER_TEST_CPP
#define RENNSMOTORSPORT_MOTOR_CONTROLLER_TEST_CPP

class MotorControllerTest{
public:

    MotorControllerTest() : esc(-1, -1), app(-1, -1, -1), MC(&esc, &app) {}

    void RunTests(float exPos) {
        std::cout<<"Running Motor Controller Tests"<<std::endl;
        std::cout<<"Test Get Value status: "<< ( GetPos(exPos) ? "Passed" : "Failed") <<std::endl;
    }

private:
    bool GetPos(float expectedPos) {
        if((MC.getPedalPosition() - expectedPos) < 0.01)
            return true;
        return false;
    }

    Esc esc;
    App app;
    MotorController MC;
};

#endif