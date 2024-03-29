//
// Created by harshk on 11/3/2023.
//

#include "Esc.h"

void Esc::update() {
    int var = this->getData();
    highResTime callTime = std::chrono::system_clock::now();
    this->temp = temp_transfer_function(0); // 0 is a placeholder int
    this->motor_revolutions = motor_revolutions_transfer_function(0); // 0 is a placeholder int
    std::vector<float> vec = std::vector<float>(2);
    vec[0] = this->temp;
    vec[1] = this->motor_revolutions;
    this->dataLog.addValue(callTime, vec);
}

float Esc::temp_transfer_function(int x) {
    return x + 0.0;
}
float Esc::motor_revolutions_transfer_function(int x) {
    return x + 0.0;
}

std::string Esc::toString(std::vector<float> vec) {
    std::string os = "";
    for (int i = 0; i < vec.size(); ++i) {
        os += vec[i];
        if (i != vec.size() - 1) os += ",";
    }
    return os;
}
