//
// Created by harshk on 11/3/2023.
//

#include "App.h"

float App::transfer_function(UDOUBLE rawVal) {
    //TODO: needs implementation
    return rawVal;
}

void App::update() {
    UDOUBLE var = this->getData();
    highResTime callTime = std::chrono::system_clock::now();
    this->position = transfer_function(var);
    this->dataLog.addValue(callTime, this->position);
}

#ifdef TEST_MODE
void App::update(UDOUBLE rawVal) {
    highResTime callTime = std::chrono::system_clock::now();
    this->position = transfer_function(rawVal);
    this->dataLog.addValue(callTime, this->position);
}
#endif
