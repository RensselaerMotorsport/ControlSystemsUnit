/*
 * -----------------------------------------------------------------
 *   _______                                  _
 *  |__   __|                                | |
 *     | | ___ _ __ ___  _ __   ___ _ __ __ _| |_ _   _ _ __ ___
 *     | |/ _ \ '_ ` _ \| '_ \ / _ \ '__/ _` | __| | | | '__/ _ \
 *     | |  __/ | | | | | |_) |  __/ | | (_| | |_| |_| | | |  __/
 *     |_|\___|_| |_| |_| .__/ \___|_|  \__,_|\__|\__,_|_|  \___|
 *                      | |
 *                      |_|
 *
 * ------------------------------------------------------------------
 * Member function implementation
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
 */

#include "Temperature.h"
float Temperature::getCelsius(){
    return temp;
}
float Temperature::getFahrenheit(){
    return temp * (9.0/5.0) + 32;
}

void Temperature::update(float var) {
    highResTime callTime = std::chrono::system_clock::now();
    d = this->transfer_function(var);
    this->temp = d;
    this->dataLog.addValue(callTime, d);
}




