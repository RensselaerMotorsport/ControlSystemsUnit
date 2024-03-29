/*
 * -----------------------------------------------------------------------
 *                         _                               _
 *       /\               | |                             | |
 *      /  \   ___ ___ ___| | ___ _ __ ___  _ __ ___   ___| |_ ___ _ __
 *     / /\ \ / __/ __/ _ \ |/ _ \ '__/ _ \| '_ ` _ \ / _ \ __/ _ \ '__|
 *    / ____ \ (_| (_|  __/ |  __/ | | (_) | | | | | |  __/ ||  __/ |
 *   /_/    \_\___\___\___|_|\___|_|  \___/|_| |_| |_|\___|\__\___|_|
 *
 * -----------------------------------------------------------------------
 *
 * The accelereometer consists of three separate sensors, thus each will need to be individually
 * constructed. The difference lies in the channel number, and from that, we should be able to
 * tell what axis each corresponds to.
 *
 * Currently, all transfer functions operate identically, but if this changes, we will need to
 * implement each axis as a separate class.
 *
 */


#ifndef RENNSMOTORSPORT_ACCELEROMETER_H
#define RENNSMOTORSPORT_ACCELEROMETER_H

#include "../AnalogSensor.h"
#include <vector>

class Accelerometer : public AnalogSensor<float>{
public:
    //Constructors
    Accelerometer() : AnalogSensor<float>("Accelerometer",
        DataLogger<float>(), -1, -1, -1)
        { value = -1; }
    Accelerometer(int channel, int hZ, int muxChannel) :
        AnalogSensor<float>("Accelerometer",
        DataLogger<float>(), channel, hZ, muxChannel)
        { value = -1; }

    //Member Functions
    float get_value(){ return value; }

    void update() override;

    #ifdef TEST_MODE
    void update(UDOUBLE rawVal) override;
    #endif
private:
    //Member Variables
    float value;

    //Helper functions:

    float transfer_function(UDOUBLE rawVal);
    std::string toString(float v) override { return std::to_string(v); }
};

#endif //RENNSMOTORSPORT_ACCELEROMETER_H
