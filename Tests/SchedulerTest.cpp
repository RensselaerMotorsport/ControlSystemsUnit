#include <iostream>
#include <chrono>
#include <thread>
#include "../Frameworks/Scheduler/Scheduler.h"

// Sensors
// #include "../Frameworks/Sensors/AnalogSensors/Accelerometer.h"
// #include "../Frameworks/Sensors/AnalogSensors/BrakePressure.h"
// #include "../Frameworks/Sensors/DigitalSensors/GPS.h"
// #include "../Frameworks/Sensors/AnalogSensors/ShockPot.h"
// #include "../Frameworks/Sensors/AnalogSensors/Temperature.h"
// #include "../Frameworks/Sensors/AnalogSensors/WheelFlux.h"
// #include "../Frameworks/Sensors/CANSensors/Imd.h"
#include "../Frameworks/Sensors/AnalogSensors/App.h"

#ifndef RENNSMOTORSPORT_SCHEDULER_TEST_CPP
#define RENNSMOTORSPORT_SCHEDULER_TEST_CPP

class SchedulerTest {
public:
    void RunTests() {
        std::cout << "Running Scheduler Tests" << std::endl;
        std::cout << "Test Timing Accuracy: " << (TestScheduler() ? "Passed" : "Failed") << std::endl;
    }

private:

    // This test should check if the scheduler runs tasks with accurate timing
    bool TestScheduler() {
        Scheduler scheduler;
        int testTimeSeconds = 10;

        // Callback for printing the delay between task enqueuing and execution
        auto debugDelayCallback = [](std::chrono::high_resolution_clock::duration delay) {
            int millisecondWarningThreshold = 0;
            int millisecondFailThreshold = 1000;
            if (delay > std::chrono::microseconds(millisecondFailThreshold)) {
                std::cout << "\033[31m"  // Set text color to red
                          << "Fail: Execution delay: "
                          << std::chrono::duration_cast<std::chrono::microseconds>(delay).count()
                          << " microseconds"
                          << "\033[0m" << std::endl;  // Reset text color
                std::cerr << "Execution delay exceeded warning threshold" << std::endl;
                DEV_Module_Exit();
                exit(1);
            }
            else if (delay > std::chrono::microseconds(millisecondWarningThreshold)) {
                std::cout << "\033[33m"  // Set text color to yellow
                          << "Warning: Execution delay: "
                          << std::chrono::duration_cast<std::chrono::microseconds>(delay).count()
                          << " microseconds"
                          << "\033[0m" << std::endl;  // Reset text color
            }
            else {
                std::cout << "Execution delay: "
                          << std::chrono::duration_cast<std::chrono::microseconds>(delay).count()
                          << " microseconds"
                          << std::endl;
            }
        };
        scheduler.setDelayCallback(debugDelayCallback);

        // Register Sensors
        int id = 0;
        App app(0, 200, 1);
        scheduler.registerSensor(id++, app);
        // Accelerometer accelerometer(0, 100, -1);
        // scheduler.registerSensor(id++, accelerometer);
        // BrakePressure brakePressure(0, 100, -1);
        // scheduler.registerSensor(id++, brakePressure);
        // GPS gps(0, 0, 10);
        // scheduler.registerAnalogSensor(id++, gps);
        // ShockPot shockPot(0, 1000, -1, front_left);
        // scheduler.registerSensor(id++, shockPot); // Theres gonna be 4 of these
        // Temperature temperature(0, 10, -1);
        // scheduler.registerSensor(id++, temperature); // Might not be 10 HZ
        // WheelFlux wheelFlux(0, 200, -1, 3.4f, front_left);
        // scheduler.registerSensor(id++, wheelFlux); // 4 here too
        // Imd imd(500, 0); // Id 0
        // scheduler.registerSensor(id++, imd);

        std::cout << "\nStarting Scheduler" << std::endl;
        // Start the scheduler in a separate thread
        std::thread schedulerThread([&scheduler]() {
            scheduler.run();
        });
        
        auto startTime = std::chrono::high_resolution_clock::now();
        while (true) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>
                (currentTime - startTime);

            if (elapsed.count() >= testTimeSeconds) { 
                scheduler.stop();
                break; 
            }

            // Sleep a bit to prevent this loop from consuming too much CPU!!!
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Ensure the scheduler thread has finished execution
        // if (schedulerThread.joinable()) {
        //     schedulerThread.join();
        // }

        std::cout << "Timing accuracy test passed" << std::endl;
        return true;
    }
};

int main() {
    SchedulerTest schedulerTest;
    schedulerTest.RunTests();
    return 0;
}

#endif
